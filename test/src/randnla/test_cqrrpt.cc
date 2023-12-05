#ifndef LINALG_HH
#include <blas.hh>
#include <lapack.hh>
#define LINALG_HH
#endif

#include <miniapps.hh>
#include <gtest/gtest.h>
#include <math.h>
#include <miniapps/randnla/cqrrpt.hh>
#include <miniapps/misc/util.hh>

#define RELDTOL 1e-10;
#define ABSDTOL 1e-12;


class TestCQRRPT : public ::testing::Test
{
    protected:
        int64_t m = 201;
        int64_t n = 12;
        std::vector<uint64_t> keys = {42, 0, 1};
    
    virtual void SetUp() {};

    virtual void TearDown() {};

    virtual void run(uint64_t a)
    {   
        int64_t m = 1000;
        int64_t n = 200;
        int64_t k = 200;
        double d_factor = 1.25;
        double norm_A = 0;
        double tol = std::pow(std::numeric_limits<double>::epsilon(), 0.85);
        int64_t nnz = 4;
        int64_t final_rank = 0;

        std::vector<double>  A;
        //auto [A, a_shape] = spblas::generate_dense<double>(m, n);
        std::vector<double>  R     (n * n, 0.0);
        std::vector<double>  A_cpy (m * n, 0.0);
        std::vector<int64_t> J     (n    , 0.0);
        std::vector<double>  I_ref (k * k, 0.0);

        norm_A = lapack::lange(lapack::Norm::Fro, m, n, A.data(), m);
        lapack::lacpy(lapack::MatrixType::General, m, n, A.data(), m, A_cpy.data(), m);

        // Call CQRRPT
        miniapps::randnla::cqrrpt::CQRRPT(m, n, A.data(), m, R.data(), n, J.data(), nnz, final_rank, tol, 1.25);
        k = final_rank;

        miniapps::misc::util::col_swap(m, n, n, A_cpy.data(), m, J);
        double* Q = A.data();

        // Test1: Q'Q  - I 
        blas::syrk(blas::Layout::ColMajor, blas::Uplo::Upper, blas::Op::Trans, k, m, 1.0, Q, m, -1.0, I_ref.data(), k);
        double norm_1 = lapack::lansy(lapack::Norm::Fro, lapack::Uplo::Upper, k, I_ref.data(), k);

        // Test2: A - QR
        blas::gemm(blas::Layout::ColMajor, blas::Op::NoTrans, blas::Op::NoTrans, m, n, k, 1.0, Q, m, R.data(), n, -1.0, A_cpy.data(), m);
        double norm_2 = lapack::lange(lapack::Norm::Fro, m, n, A_cpy.data(), m);

        printf("REL NORM OF AP - QR:    %15e\n", norm_2 / norm_A);
        printf("FRO NORM OF (Q'Q - I)/sqrt(n): %2e\n\n", norm_1 / std::sqrt((double) n));
    }
};


TEST_F(TestCQRRPT, Trivial)
{
    run(1);
}
