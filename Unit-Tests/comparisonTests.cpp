#include "pch.h"
#include "../floatingPointArithmetic/comparison.h"
#include <limits>
#include <array>

static const std::array<float, 10> FLOAT_TEST_VALUES = {
    56733.3f, -3245.67f, 0.0f, -0.0f, std::numeric_limits<float>::infinity(),
    -std::numeric_limits<float>::infinity(), std::numeric_limits<float>::max(),
    std::numeric_limits<float>::min(), std::numeric_limits<float>::denorm_min(),
    std::nanf("")
};

static const std::array<double, 10> DOUBLE_TEST_VALUES = {
    72433.3, -6.8765, 0.0, -0.0, std::numeric_limits<double>::infinity(),
    -std::numeric_limits<double>::infinity(), std::numeric_limits<double>::max(),
    std::numeric_limits<double>::min(), std::numeric_limits<double>::denorm_min(),
    std::nan("")
};

TEST(ComparisonTests, LessThanFloat) {
    for (float left : FLOAT_TEST_VALUES) {
        for (float right : FLOAT_TEST_VALUES) {
            if (isFinite(left) && isFinite(right)) {
                EXPECT_EQ(lessThan(left, right), left < right);
            }
        }
    }
}

TEST(ComparisonTests, LessThanDouble) {
    for (double left : DOUBLE_TEST_VALUES) {
        for (double right : DOUBLE_TEST_VALUES) {
            if (isFinite(left) && isFinite(right)) {
                EXPECT_EQ(lessThan(left, right), left < right);
            }
        }
    }
}

TEST(ComparisonTests, MinFunctionFloat) {
    for (float left : FLOAT_TEST_VALUES) {
        for (float right : FLOAT_TEST_VALUES) {
            if (isFinite(left) && isFinite(right)) {
                EXPECT_EQ(min(left, right), std::min(left, right));
            }
        }
    }
}

TEST(ComparisonTests, MinFunctionDouble) {
    for (double left : DOUBLE_TEST_VALUES) {
        for (double right : DOUBLE_TEST_VALUES) {
            if (isFinite(left) && isFinite(right)) {
                EXPECT_EQ(min(left, right), std::min(left, right));
            }
        }
    }
}

TEST(ComparisonTests, MaxFunctionFloat) {
    for (float left : FLOAT_TEST_VALUES) {
        for (float right : FLOAT_TEST_VALUES) {
            if (isFinite(left) && isFinite(right)) {
                EXPECT_EQ(max(left, right), std::max(left, right));
            }
        }
    }
}

TEST(ComparisonTests, MaxFunctionDouble) {
    for (double left : DOUBLE_TEST_VALUES) {
        for (double right : DOUBLE_TEST_VALUES) {
            if (isFinite(left) && isFinite(right)) {
                EXPECT_EQ(max(left, right), std::max(left, right));
            }
        }
    }
}

TEST(ComparisonTests, ClampFunctionFloat) {
    for (float value : FLOAT_TEST_VALUES) {
        if (isFinite(value)) {
            float lower = -100.0f, higher = 100.0f;
            EXPECT_EQ(clamp(value, lower, higher), std::clamp(value, lower, higher));
        }
    }
}

TEST(ComparisonTests, ClampFunctionDouble) {
    for (double value : DOUBLE_TEST_VALUES) {
        if (isFinite(value)) {
            double lower = -100.0, higher = 100.0;
            EXPECT_EQ(clamp(value, lower, higher), std::clamp(value, lower, higher));
        }
    }
}

TEST(ComparisonTests, EqualWithPrecisionFloat) {
    float precision = 0.0001f;
    for (float left : FLOAT_TEST_VALUES) {
        for (float right : FLOAT_TEST_VALUES) {
            if (isFinite(left) && isFinite(right)) {
                EXPECT_EQ(equalWithPrecision(left, right, precision), std::fabs(left - right) < precision * std::max(left, right));
            }
        }
    }
}

TEST(ComparisonTests, EqualWithPrecisionDouble) {
    double precision = 0.0001;
    for (double left : DOUBLE_TEST_VALUES) {
        for (double right : DOUBLE_TEST_VALUES) {
            if (isFinite(left) && isFinite(right)) {
                EXPECT_EQ(equalWithPrecision(left, right, precision), std::fabs(left - right) < precision * std::max(left, right));
            }
        }
    }
}
