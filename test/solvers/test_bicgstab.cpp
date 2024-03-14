#include "miniapps.hh"
#include <spblas/spblas.hpp>

#include <algorithm>
#include <exception>
#include <vector>

#include <gtest/gtest.h>

template <typename T> class TestBiCGSTAB : public testing::Test {
public:
  using ValueType = T;
};

using BiCGSTABTestTypes = ::testing::Types<double, float>;
TYPED_TEST_SUITE(TestBiCGSTAB, BiCGSTABTestTypes);

TYPED_TEST(TestBiCGSTAB, ConvergesForSmallSystem) {
  using T = TypeParam;
  constexpr double tol = std::is_same<T, double>::value ? 1e-14 : 1e-7;
  constexpr int max_iters = 100;
  std::vector<T> b(10, 1.0);
  std::vector<T> x(10, 0.0);

  auto &&[values, rowptr, colind, shape, nnz] =
      spblas::generate_csr<T>(10, 10, 42);
  spblas::csr_view<T> a(values, rowptr, colind, shape, nnz);
  std::tuple<double, int> res;

  miniapps::BiCGSTAB<T> BiCGSTAB(tol, max_iters);
  res = BiCGSTAB.apply(a, b, x);

  ASSERT_LE(get<0>(res), tol);
  ASSERT_LE(get<1>(res), max_iters);
}

TYPED_TEST(TestBiCGSTAB, ConvergesForLargeSystem) {
  using T = TypeParam;
  constexpr double tol = std::is_same<T, double>::value ? 1e-14 : 1e-7;
  constexpr int max_iters = 100;
  std::vector<T> b(1000, 1.0);
  std::vector<T> x(1000, 0.0);

  auto &&[values, rowptr, colind, shape, nnz] =
      spblas::generate_csr<T>(1000, 1000, 12345);
  spblas::csr_view<T> a(values, rowptr, colind, shape, nnz);
  std::tuple<double, int> res;

  miniapps::BiCGSTAB<T> BiCGSTAB(tol, max_iters);
  res = BiCGSTAB.apply(a, b, x);

  ASSERT_LE(get<0>(res), tol);
  ASSERT_LE(get<1>(res), max_iters);
}
