#include "pch.h"
#include "../floatingPointArithmetic/conversion.h"
#include <limits>
#include <array>

static const std::array<float, 7> FLOAT_TEST_VALUES = {
    56733.3f, 0.0f, -0.0f, std::numeric_limits<float>::infinity(),
    -std::numeric_limits<float>::infinity(), std::numeric_limits<float>::max(),
    std::numeric_limits<float>::min()
};

static const std::array<double, 8> DOUBLE_TEST_VALUES = {
    72433.3, -6.8765, 0.0, -0.0, std::numeric_limits<double>::infinity(),
    -std::numeric_limits<double>::infinity(), std::numeric_limits<double>::max(),
    std::numeric_limits<double>::min()
};

TEST(ConversionTests, FloatToBytes) {
    for (float value : FLOAT_TEST_VALUES) {
        uint32_t bit = toBytes(value);
        float unbit = toFloat(bit);
        EXPECT_EQ(value, unbit);
    }
}

TEST(ConversionTests, FloatToBytesNaN) {
    float nanValue = std::nanf("");
    uint32_t bit = toBytes(nanValue);
    float unbit = toFloat(bit);
    EXPECT_TRUE(std::isnan(unbit));
}

TEST(ConversionTests, DoubleToBytes) {
    for (double value : DOUBLE_TEST_VALUES) {
        uint64_t bit = toBytes(value);
        double unbit = toDouble(bit);
        EXPECT_EQ(value, unbit);
    }
}

TEST(ConversionTests, DoubleToBytesNaN) {
    double nanValue = std::nan("");
    uint64_t bit = toBytes(nanValue);
    double unbit = toDouble(bit);
    EXPECT_TRUE(std::isnan(unbit));
}

TEST(ConversionTests, BruteForceCheck) {
    uint32_t nu = 1;
    do {
        float floated = toFloat(nu);
        EXPECT_EQ(toBytes(floated), nu);
    } while (++nu != 0);
}
