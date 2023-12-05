//#include <vector>

#ifndef LINALG_HH
#include <blas.hh>
#include <lapack.hh>
#define LINALG_HH
#endif

#include <cstdint>
#include <vector>
#include <numeric>

namespace miniapps::misc::util {

template <typename T>
void col_swap(
    int64_t m,
    int64_t n,
    int64_t k,
    T* A,
    int64_t lda,
    std::vector<int64_t> idx);

} 