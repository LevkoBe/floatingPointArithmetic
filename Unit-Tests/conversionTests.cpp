#include "pch.h"
#include "../floatingPointArithmetic/conversion.h"
#include <limits>

TEST(ConversionTests, FloatToBytes)
{
    float values[] = { 56733.3f, 0.0f, -0.0f, std::numeric_limits<float>::infinity(),
                      -std::numeric_limits<float>::infinity(), std::numeric_limits<float>::max(),
                      std::numeric_limits<float>::min() };

    for (float value : values)
    {
        uint32_t bit = toBytes(value);
        float unbit = toFloat(bit);
        EXPECT_EQ(value, unbit);
    }
}

TEST(ConversionTests, FloatToBytesNaN)
{
    uint32_t bit = toBytes(std::nanf(""));
    float unbit = toFloat(bit);
    EXPECT_TRUE(std::isnan(unbit));
}

TEST(ConversionTests, DoubleToBytes)
{
    double values[] = { 72433.3, -6.8765, 0.0, -0.0, std::numeric_limits<double>::infinity(),
                       -std::numeric_limits<double>::infinity(), std::numeric_limits<double>::max(),
                       std::numeric_limits<double>::min() };

    for (double value : values)
    {
        uint64_t bit = toBytes(value);
        double unbit = toDouble(bit);
        EXPECT_EQ(value, unbit);
    }
}

TEST(ConversionTests, DoubleToBytesNaN)
{
    uint64_t bit = toBytes(std::nan(""));
    double unbit = toDouble(bit);
    EXPECT_TRUE(std::isnan(unbit));
}

// for me it took 4 minutes to run this test
TEST(ConversionTests, BruteForceCheck)
{
    uint32_t nu = 1;
    float floated;
    while (nu++ != 0) {
        floated = toFloat(nu);
		EXPECT_EQ(toBytes(floated), nu);
    }
}
