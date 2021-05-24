#include "huc/Modules/Polynomial.hh"
#include "huc/misc/utility.hh"
#include "gtest/gtest.h"

using namespace huc;

TEST(PolynomialUnivariateUnitTest, BasicConstructor){
    PolynomialUnivariateDense<int> f;
    EXPECT_EQ(0, f.degree());
}

TEST(PolynomialUnivariateUnitTest, InitializerListConstructor){
    // 66 + 11x + 7x^2 + 53x^3 + 34x^4 + 98x^5 + 4x^6 + 70x^7 + 64x^8 + 5x^9 + 23x^10 + 52x^11 + 87x^12
    std::vector<int> f_b = { 66, 11, 7, 53, 34, 98, 4, 70, 64, 5, 23, 52, 87 };

    PolynomialUnivariateDense<int> f{ 66, 11, 7, 53, 34, 98, 4, 70, 64, 5, 23, 52, 87 };
    EXPECT_EQ(12, f.degree());
    EXPECT_TRUE(huc::utility::container_equal(f_b.begin(), f_b.end(), f.begin(), f.end()));
}

TEST(PolynomialUnivariateUnitTest, VectorConstructor){
    std::vector<int> f_b = { 66, 11, 7, 53, 34, 98, 4, 70, 64, 5, 23, 52, 87 };

    PolynomialUnivariateDense<int> f(f_b);
    EXPECT_EQ(12, f.degree());
    EXPECT_TRUE(huc::utility::container_equal(f_b.begin(), f_b.end(), f.begin(), f.end()));
}

TEST(PolynomialUnivariateUnitTest, SimpleAddition){
    std::vector<int> f_b = {1, 1, 2, 3, 5, 8, 13};
    std::vector<int> g_b = {13, 8, 5, 3, 2, 1, 1};
    std::vector<int> out;
    auto addIt = [](int a, int b) { return a + b; };
    huc::utility::for_each_binary(f_b.begin(), f_b.end(), g_b.begin(), std::back_inserter(out), addIt);

    PolynomialUnivariateDense<int> f(f_b);
    PolynomialUnivariateDense<int> g(g_b);
    PolynomialUnivariateDense<int> h = f + g;
    EXPECT_EQ(6, h.degree());
    EXPECT_TRUE(huc::utility::container_equal(h.begin(), h.end(), out.begin(), out.end()));

    f += g;
    EXPECT_EQ(6, f.degree());
    EXPECT_TRUE(huc::utility::container_equal(f.begin(), f.end(), out.begin(), out.end()));
}

TEST(PolynomialUnivariateUnitTest, SimpleAdditionWithLeadingZero){

}

TEST(PolynomialUnivariateUnitTest, ComplexAddition){
    PolynomialUnivariateDense<int> f {59, -26, 71, 84, 20, -54, -57, 47, -62, 21, 8 , 88, 95, 19, -60};
    PolynomialUnivariateDense<int> g {29, 3 , -38, 17, -2 , 33, 48, 14, 0, -27, 16};
    PolynomialUnivariateDense<int> h = f + g;
    EXPECT_EQ(14, h.degree());

}

TEST(PolynomialUnivariateUnitTest, ComplexAdditionWithZero){

}

TEST(PolynomialUnivariateUnitTest, SimpleSubtraction){
    std::vector<int> f_b = {1, 1, 2, 3, 5, 8, 13};
    std::vector<int> g_b = {13, 8, 5, 3, 2, 1, 1};
    std::vector<int> out;
    auto addIt = [](int a, int b) { return a - b; };
    huc::utility::for_each_binary(f_b.begin(), f_b.end(), g_b.begin(), std::back_inserter(out), addIt);

    PolynomialUnivariateDense<int> f(f_b);
    PolynomialUnivariateDense<int> g(g_b);
    PolynomialUnivariateDense<int> h = f - g;
    EXPECT_EQ(6, h.degree());
    EXPECT_TRUE(huc::utility::container_equal(h.begin(), h.end(), out.begin(), out.end()));

    f -= g;
    EXPECT_EQ(6, f.degree());
    EXPECT_TRUE(huc::utility::container_equal(f.begin(), f.end(), out.begin(), out.end()));
}

TEST(PolynomialUnivariateUnitTest, SimpleSubtractionWithZero){

}

TEST(PolynomialUnivariateUnitTest, ComplexSubtraction){

}

TEST(PolynomialUnivariateUnitTest, ComplexSubtractionWithZero){

}

TEST(PolynomialUnivariateUnitTest, PolynomialEvaluation){

}
