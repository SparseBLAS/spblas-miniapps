//#include <vector>

#ifndef LINALG_HH
#include <blas.hh>
#include <lapack.hh>
#define LINALG_HH
#endif


//#include <spblas/spblas.hpp>
//#include <fmt/core.h>
//#include <fmt/ranges.h>

#include <cstdint>
#include <vector>
#include <numeric>

namespace miniapps::randnla::cqrrpt {

template <typename T>
int CQRRPT(
    int64_t m,
    int64_t n,
    T* A,
    int64_t lda,
    T* R,
    int64_t ldr,
    int64_t* J,
    int64_t nnz,
    int64_t& final_rank,
    T alg_tol,
    T d_factor
);

} 
