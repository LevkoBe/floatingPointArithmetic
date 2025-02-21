#include "pch.h"
#include "../floatingPointArithmetic/classification.h"
#include <limits>
#include <array>

static const std::array<float, 10> FLOAT_TEST_VALUES = {
    56733.3f, 0.0f, -0.0f, std::numeric_limits<float>::infinity(),
    -std::numeric_limits<float>::infinity(), std::numeric_limits<float>::max(),
    std::numeric_limits<float>::min(), std::numeric_limits<float>::denorm_min(),
    std::nanf(""), -std::nanf("")
};

static const std::array<double, 10> DOUBLE_TEST_VALUES = {
    72433.3, -6.8765, 0.0, -0.0, std::numeric_limits<double>::infinity(),
    -std::numeric_limits<double>::infinity(), std::numeric_limits<double>::max(),
    std::numeric_limits<double>::min(), std::numeric_limits<double>::denorm_min(),
    std::nan("")
};

TEST(ClassificationTests, IsFiniteFloat) {
    for (float value : FLOAT_TEST_VALUES) {
        EXPECT_EQ(isFinite(value), std::isfinite(value));
    }
}

TEST(ClassificationTests, IsFiniteDouble) {
    for (double value : DOUBLE_TEST_VALUES) {
        EXPECT_EQ(isFinite(value), std::isfinite(value));
    }
}

TEST(ClassificationTests, IsInfinityFloat) {
    for (float value : FLOAT_TEST_VALUES) {
        EXPECT_EQ(isInfinity(value), std::isinf(value));
    }
}

TEST(ClassificationTests, IsInfinityDouble) {
    for (double value : DOUBLE_TEST_VALUES) {
        EXPECT_EQ(isInfinity(value), std::isinf(value));
    }
}

TEST(ClassificationTests, isSignedFloat) {
    for (float value : FLOAT_TEST_VALUES) {
        EXPECT_EQ(isSigned(value), std::signbit(value));
    }
}

TEST(ClassificationTests, isSignedDouble) {
    for (double value : DOUBLE_TEST_VALUES) {
        EXPECT_EQ(isSigned(value), std::signbit(value));
    }
}

TEST(ClassificationTests, IsNaNFloat) {
    for (float value : FLOAT_TEST_VALUES) {
        EXPECT_EQ(isNaN(value), std::isnan(value));
    }
}

TEST(ClassificationTests, IsNaNDouble) {
    for (double value : DOUBLE_TEST_VALUES) {
        EXPECT_EQ(isNaN(value), std::isnan(value));
    }
}

TEST(ClassificationTests, IsZeroFloat) {
    for (float value : FLOAT_TEST_VALUES) {
        EXPECT_EQ(isZero(value), value == 0.0f || value == -0.0f);
    }
}

TEST(ClassificationTests, IsZeroDouble) {
    for (double value : DOUBLE_TEST_VALUES) {
        EXPECT_EQ(isZero(value), value == 0.0 || value == -0.0);
    }
}

TEST(ClassificationTests, FpclassifyFloat) {
    for (float value : FLOAT_TEST_VALUES) {
        EXPECT_EQ(fpclassify(value), std::fpclassify(value));
    }
}

TEST(ClassificationTests, FpclassifyDouble) {
    for (double value : DOUBLE_TEST_VALUES) {
        EXPECT_EQ(fpclassify(value), std::fpclassify(value));
    }
}

// ~2.5 minutes to run
//TEST(ConversionTests, BruteForceCheck) {
//    uint32_t nu = 1;
//    do {
//        float floated = toFloat(nu);
//        EXPECT_EQ(fpclassify(floated), std::fpclassify(floated));
//    } while (++nu != 0);
//}
