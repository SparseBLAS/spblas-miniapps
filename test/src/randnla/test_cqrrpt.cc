#include <blas.hh>
#include <miniapps.hh>
#include <gtest/gtest.h>
#include <math.h>

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

    }
};


TEST_F(TestCQRRPT, Trivial)
{
    run(1);
}
