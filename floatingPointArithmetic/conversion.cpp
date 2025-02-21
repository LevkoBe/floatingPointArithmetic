#include <iostream>
#include "conversion.h"

uint32_t toBytes(float const value) {
    return std::bit_cast<uint32_t>(value);
}

uint64_t toBytes(double const value) {
    return std::bit_cast<uint64_t>(value);
}

float toFloat(uint32_t const value) {
    return std::bit_cast<float>(value);
}

double toDouble(uint64_t const value) {
    return std::bit_cast<double>(value);
}
