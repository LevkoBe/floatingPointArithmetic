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

template <typename T>
void checkConversion(T number) {
    auto bit = toBytes(number);
    T unbit = ((std::is_same_v<T, float>) ? toFloat(bit) : toDouble(bit));
    std::cout << number << " " << ((number == unbit) ? "==" : "!=") << " " << unbit << "\n";
}

void checkStage1() {
    checkConversion(13.3f);
    checkConversion(1234124.23f);
    checkConversion(-1234.43);
    checkConversion(-54534.345345f);
    checkConversion(23423.3);
    checkConversion(-2.34234243234);
    checkConversion(-0.0);
}

template void checkConversion<float>(float);
template void checkConversion<double>(double);
