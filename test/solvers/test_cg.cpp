#include "miniapps.hh"
#include <spblas/spblas.hpp>

#include <algorithm>
#include <exception>
#include <vector>

#include <gtest/gtest.h>

// TODO: Rather than this, generate a COO, apply these algorithms (make spd, sum
// duplicates), then implement and apply conversion to csr.

template <typename T> struct matrix_data_entry {
  std::size_t row;
  std::size_t col;
  T value;
};

template <typename T> struct matrix_data {
  using nonzero_type = matrix_data_entry<T>;

  std::size_t num_rows;
  std::size_t num_cols;
  std::vector<nonzero_type> nonzeros;

  matrix_data(std::vector<std::size_t> rowind, std::vector<std::size_t> colind,
              std::vector<T> values, spblas::index<std::size_t> shape)
      : num_rows{shape.template get<0>()}, num_cols{shape.template get<1>()} {
    assert(rowind.size() == colind.size() && rowind.size() == values.size());
    for (std::size_t i = 0; i < values.size(); i++) {
      nonzeros.emplace_back(rowind[i], colind[i], values[i]);
    }
  }

  auto convert_to_coo() {
    auto nnz = nonzeros.size();
    std::vector<T> values(nnz);
    std::vector<std::size_t> rowind(nnz);
    std::vector<std::size_t> colind(nnz);

    for (std::size_t i = 0; i < nnz; i++) {
      values[i] = nonzeros[i].value;
      rowind[i] = nonzeros[i].row;
      colind[i] = nonzeros[i].col;
    }
    return std::tuple(values, rowind, colind, nnz);
  }

  void sort_row_major() {
    std::sort(begin(nonzeros), end(nonzeros),
              [](nonzero_type x, nonzero_type y) {
                return std::tie(x.row, x.col) < std::tie(y.row, y.col);
              });
  }

  void sum_duplicates() {
    this->sort_row_major();
    std::vector<nonzero_type> new_nonzeros;
    if (!nonzeros.empty()) {
      new_nonzeros.emplace_back(nonzeros.front().row, nonzeros.front().col,
                                0.0);
      for (auto entry : nonzeros) {
        if (entry.row != new_nonzeros.back().row ||
            entry.col != new_nonzeros.back().col) {
          new_nonzeros.emplace_back(entry.row, entry.col, 0.0);
        }
        new_nonzeros.back().value += entry.value;
      }
      nonzeros = std::move(new_nonzeros);
    }
  }

  void make_symmetric() {
    const auto nnz = nonzeros.size();
    // compute (A + op(A^T)) / 2
    for (std::size_t i = 0; i < nnz; i++) {
      nonzeros[i].value /= 2.0;
      auto entry = nonzeros[i];
      nonzeros.emplace_back(entry.col, entry.row, entry.value);
    }
    // combine duplicates
    this->sum_duplicates();
  }

  void make_diag_dominant(T ratio = 1.0) {
    std::vector<T> norms(num_rows);
    std::vector<std::int64_t> diag_positions(num_rows, -1);
    std::int64_t i{};
    for (auto entry : nonzeros) {
      if (entry.row == entry.col) {
        diag_positions[entry.row] = i;
      } else {
        norms[entry.row] += std::abs(entry.value);
      }
      i++;
    }
    for (i = 0; i < num_rows; i++) {
      if (norms[i] == 0.0) {
        // make sure empty rows don't make the matrix singular
        norms[i] = 1.0;
      }
      if (diag_positions[i] < 0) {
        nonzeros.emplace_back(i, i, norms[i] * ratio);
      } else {
        auto &diag_value = nonzeros[diag_positions[i]].value;
        const auto diag_magnitude = std::abs(diag_value);
        const auto offdiag_magnitude = norms[i];
        if (diag_magnitude < offdiag_magnitude * ratio) {
          const auto scaled_value =
              diag_value * (offdiag_magnitude * ratio / diag_magnitude);
          if (std::isfinite(scaled_value)) {
            diag_value = scaled_value;
          } else {
            diag_value = offdiag_magnitude * ratio;
          }
        }
      }
    }
    this->sort_row_major();
  }
};

template <typename T> class TestCG : public testing::Test {
public:
  using ValueType = T;

  auto convert_rowind_to_rowptr(std::vector<std::size_t> rowind,
                                std::size_t nnz,
                                spblas::index<std::size_t> shape) {
    auto num_rows = shape.template get<0>();
    std::vector<std::size_t> rowptr(num_rows + 1, 0);
    assert(rowind.size() == nnz);

    for (std::size_t i = 0; i < nnz; i++) {
      rowptr[rowind[i]]++;
    }
    constexpr auto max = std::numeric_limits<std::size_t>::max();
    std::size_t partial_sum{};
    for (std::size_t i = 0; i < num_rows + 1; ++i) {
      auto this_nnz = i < num_rows ? rowptr[i] : 0;
      rowptr[i] = partial_sum;
      if (max - partial_sum < this_nnz) {
        throw std::exception();
      }
      partial_sum += this_nnz;
    }

    return rowptr;
  }
};

using CGTestTypes = ::testing::Types<double, float>;
TYPED_TEST_SUITE(TestCG, CGTestTypes);

TYPED_TEST(TestCG, ConvergesForSmallSystem) {
  using T = TypeParam;
  constexpr double tol = std::is_same<T, double>::value ? 1e-14 : 1e-7;
  constexpr int max_iters = 100;
  std::vector<T> b(10, 1.0);
  std::vector<T> x(10, 0.0);

  auto &&[values_orig, rowind_orig, colind_orig, shape, nnz_orig] =
      spblas::generate_coo<T>(10, 10, 42);
  matrix_data<T> data(rowind_orig, colind_orig, values_orig, shape);
  data.sort_row_major();
  data.make_symmetric();
  data.make_diag_dominant();
  auto &&[values, rowind, colind, nnz] = data.convert_to_coo();
  auto rowptr = this->convert_rowind_to_rowptr(colind, nnz, shape);
  spblas::csr_view<T> a(values, rowptr, colind, shape, nnz);
  std::tuple<double, int> res;

  miniapps::CG<T> CG(tol, max_iters);
  res = CG.apply(a, b, x);

  ASSERT_LE(get<0>(res), tol);
  ASSERT_LE(get<1>(res), max_iters);
}

TYPED_TEST(TestCG, ConvergesForLargeSystem) {
  using T = TypeParam;
  constexpr double tol = std::is_same<T, double>::value ? 1e-14 : 1e-7;
  constexpr int max_iters = 100;
  std::vector<T> b(1000, 1.0);
  std::vector<T> x(1000, 0.0);

  auto &&[values_orig, rowind_orig, colind_orig, shape, nnz_orig] =
      spblas::generate_coo<T>(1000, 1000, 12345);
  matrix_data<T> data(rowind_orig, colind_orig, values_orig, shape);
  data.sort_row_major();
  data.make_symmetric();
  data.make_diag_dominant();
  auto &&[values, rowind, colind, nnz] = data.convert_to_coo();

  auto rowptr = this->convert_rowind_to_rowptr(colind, nnz, shape);

  spblas::csr_view<T> a(values, rowptr, colind, shape, nnz);
  std::tuple<double, int> res;

  miniapps::CG<T> CG(tol, max_iters);
  res = CG.apply(a, b, x);

  ASSERT_LE(get<0>(res), tol);
  ASSERT_LE(get<1>(res), max_iters);
}
