#include "huc/Modules/Polynomial.hh"
#include "huc/misc/utility.hh"
#include "gtest/gtest.h"

using namespace huc;

namespace HucUnitTesting::PolynomialInt{

TEST(PolynomialUnivariateDenseUnitTest, BasicConstructor){
    PolynomialUnivariateDense<int> f;
    EXPECT_EQ(0, f.degree());
}

TEST(PolynomialUnivariateDenseUnitTest, InitializerListConstructor){
    // 66 + 11x + 7x^2 + 53x^3 + 34x^4 + 98x^5 + 4x^6 + 70x^7 + 64x^8 + 5x^9 + 23x^10 + 52x^11 + 87x^12
    std::vector<int> f_b = { 66, 11, 7, 53, 34, 98, 4, 70, 64, 5, 23, 52, 87 };

    PolynomialUnivariateDense<int> f{ 66, 11, 7, 53, 34, 98, 4, 70, 64, 5, 23, 52, 87 };
    EXPECT_EQ(12, f.degree());
    EXPECT_TRUE(utility::ranges::container_equal(f_b, f));
}

TEST(PolynomialUnivariateDenseUnitTest, VectorConstructor){
    std::vector<int> f_b = { 66, 11, 7, 53, 34, 98, 4, 70, 64, 5, 23, 52, 87 };

    PolynomialUnivariateDense<int> f(f_b);
    EXPECT_EQ(12, f.degree());
    EXPECT_TRUE(utility::ranges::container_equal(f_b, f));
}

TEST(PolynomialUnivariateDenseUnitTest, SimpleAddition){
    std::vector<int> f_b = {1, 1, 2, 3, 5, 8, 13};
    std::vector<int> g_b = {13, 8, 5, 3, 2, 1, 1};
    std::vector<int> out;
    auto addIt = [](int a, int b) { return a + b; };
    utility::ranges::for_each_binary(f_b, g_b, std::back_inserter(out), addIt);

    PolynomialUnivariateDense<int> f(f_b);
    PolynomialUnivariateDense<int> g(g_b);
    PolynomialUnivariateDense<int> h = f + g;
    EXPECT_EQ(6, h.degree());
    EXPECT_TRUE(utility::ranges::container_equal(h, out));

    f += g;
    EXPECT_EQ(6, f.degree());
    EXPECT_TRUE(utility::ranges::container_equal(f, out));
}

TEST(PolynomialUnivariateDenseUnitTest, SimpleAdditionWithLeadingZero){

}

TEST(PolynomialUnivariateDenseUnitTest, ComplexAddition){
    PolynomialUnivariateDense<int> f {59, -26, 71, 84, 20, -54, -57, 47, -62, 21, 8 , 88, 95, 19, -60};
    PolynomialUnivariateDense<int> g {29, 3 , -38, 17, -2 , 33, 48, 14, 0, -27, 16};
    PolynomialUnivariateDense<int> h = f + g;
    EXPECT_EQ(14, h.degree());

}

TEST(PolynomialUnivariateDenseUnitTest, ComplexAdditionWithZero){

}

TEST(PolynomialUnivariateDenseUnitTest, SimpleSubtraction){
    std::vector<int> f_b {1, 1, 2, 3, 5, 8, 13};
    std::vector<int> g_b {13, 8, 5, 3, 2, 1, 1};
    std::vector<int> out;
    auto subIt = [](int a, int b) { return a - b; };
    utility::ranges::for_each_binary(f_b, g_b, std::back_inserter(out), subIt);

    PolynomialUnivariateDense<int> f(f_b);
    PolynomialUnivariateDense<int> g(g_b);
    PolynomialUnivariateDense<int> h = f - g;
    EXPECT_EQ(6, h.degree());
    EXPECT_TRUE(utility::ranges::container_equal(h, out));

    f -= g;
    EXPECT_EQ(6, f.degree());
    EXPECT_TRUE(utility::ranges::container_equal(f, out));
}

TEST(PolynomialUnivariateDenseUnitTest, SimpleSubtractionWithZero){

}

TEST(PolynomialUnivariateDenseUnitTest, ComplexSubtraction){

}

TEST(PolynomialUnivariateDenseUnitTest, ComplexSubtractionWithZero){

}

// Euler's prime generating polynomial
TEST(PolynomialUnivariateDenseUnitTest, SimplePolynomialEvaluation){
    std::vector<int> primes{41, 43, 47, 53, 61, 71, 83, 97, 113, 131, 151, 173, 197, 223, 251, 281, 313,
                            347, 383, 421, 461, 503, 547, 593, 641, 691, 743, 797, 853, 911, 971, 1033,
                            1097, 1163, 1231, 1301, 1373, 1447, 1523, 1601, 1681, 1763};
    
    PolynomialUnivariateDense<int> euler_poly{41, 1, 1};
    for(int n = 0; auto p : primes){
        EXPECT_EQ(p, euler_poly(n++));
    }
}

TEST(PolynomialUnivariateDenseUnitTest, ComplexPolynomialEvaluation){
    // what to do here?
}

TEST(PolynomialUnivariateDenseUnitTest, ScalarMultiplication){
    std::vector<int> f_b {29, 3 , -38, 17, -2 , 33, 48, 14, 0, -27, 16};
    PolynomialUnivariateDense<int> f(f_b);
    
    for(int i = 0; i < 100; ++i){
        auto tmp(f_b);
        std::ranges::for_each(tmp, [i](auto &c) {c*=i;});
        // Binary mult with scalar
        PolynomialUnivariateDense<int> f_1 = f * i;
        PolynomialUnivariateDense<int> f_2 = i * f;
        // times equal operator
        PolynomialUnivariateDense<int> f_3(f);
        f_3 *= i;
        EXPECT_TRUE(utility::ranges::container_equal(tmp, f_1));
        EXPECT_TRUE(utility::ranges::container_equal(tmp, f_2));
        EXPECT_TRUE(utility::ranges::container_equal(tmp, f_3));
    }
}

TEST(PolynomialUnivariateDenseUnitTest, LeadingZeroes){
    std::vector<int> f_b {0,1,2,3,4,5,6,0,0,0};
    PolynomialUnivariateDense<int> f(f_b);

    EXPECT_EQ(6, f.degree());
    EXPECT_FALSE(utility::ranges::container_equal(f, f_b));
    f_b.erase(f_b.begin()+7, f_b.end());
    EXPECT_TRUE(utility::ranges::container_equal(f, f_b));
}

TEST(PolynomialUnivariateDenseUnitTest, FalseComparison){
    PolynomialUnivariateDense<int> f {29, 3 , -38, 17, -2 , 33, 48, 14, 0, -27, 16, 1, 3, 4, 0};
    PolynomialUnivariateDense<int> g {29, 3 , -38, 17, -2 , 33, 48, 14, 0, -27, 16};
    EXPECT_FALSE(utility::ranges::container_equal(f, g));
}

TEST(PolynomialUnivariateDenseUnitTest, TrueComparison){
    PolynomialUnivariateDense<int> f {29, 3 , -38, 17, -2 , 33, 48, 14, 0, -27, 16};
    PolynomialUnivariateDense<int> g {29, 3 , -38, 17, -2 , 33, 48, 14, 0, -27, 16};
    EXPECT_TRUE(utility::ranges::container_equal(f, g));
}

TEST(PolynomialUnivariateDenseUnitTest, Negation){
    PolynomialUnivariateDense<int> f {29, 3 , -38, 17, -2 , 33, 48, 14, 0, -27, 16, 1, 3, 4, 0};
    auto g = -f;
    auto negated = [](auto c1, auto c2){ return c1 == -c2; };
    EXPECT_TRUE(utility::ranges::container_equal(f, g, negated));
}

}
