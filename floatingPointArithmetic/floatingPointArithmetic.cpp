#include <iostream>
#include <bit>
#include <algorithm> // for bruteforce check

// Stage 1: to and fro

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

// Stage 2

bool isFinite(float number) {
    // 0111 1111 1000 0000 ... (+4)
    uint32_t mask = 0x7F800000;
    return (toBytes(number) & mask) != mask;
}

bool isFinite(double number) {
    // 0111 1111 1111 0000 ... (+12)
    uint32_t mask = 0x7FF0000000000000;
    return (toBytes(number) & mask) != mask;
}

bool isInfinity(float number) {
    return ((toBytes(number) << 1) ^ 0xFF000000) == 0;
}

bool isInfinity(double number) {
    return ((toBytes(number) << 1) ^ 0xFFE0000000000000) == 0;
}

bool isPositive(float number) {
    return (0x80000000 & toBytes(number)) == 0;
}

bool isPositive(double number) {
    return (0x8000000000000000 & toBytes(number)) == 0;
}

template <typename T>
bool isPositiveInfinity(T number) {
    return isPositive(number) && isInfinity(number);
}

template <typename T>
bool isNegativeInfinity(T number) {
    return !isPositive(number) && isInfinity(number);
}

template <typename T>
bool isZero(T number) {
    return (toBytes(number) << 1) == 0;
}

template <typename T>
bool isPositiveZero(T number) {
    return isPositive(number) && isZero(number);
}

template <typename T>
bool isNegativeZero(T number) {
    return !isPositive(number) && isZero(number);
}

bool isNaN(float number) {
    uint32_t nu = (toBytes(number) << 1);
    uint32_t expMask = 0xFF000000;
    bool fullExp = (nu & expMask) == expMask;
    bool non0Man = (nu & ~expMask) != 0;
    return fullExp && non0Man;
}

bool isNaN(double number) {
    uint64_t nu = (toBytes(number) << 1);
    uint64_t expMask = 0xFFE0000000000000;
    bool fullExp = (nu & expMask) == expMask;
    bool non0Man = (nu & ~expMask) != 0;
    return fullExp && non0Man;
}

bool isNormal(float number) {
    uint32_t exponent = (toBytes(number) << 1) & 0xFF000000;
    return exponent != 0xFF000000 && exponent != 0;
}

bool isNormal(double number) {
    uint64_t exponent = (toBytes(number) << 1) & 0xFFE0000000000000;
    return exponent != 0xFFE0000000000000 && exponent != 0;
}

bool isSubnormal(float number) {
    uint32_t nu = (toBytes(number) << 1);
    uint32_t expMask = 0xFF000000;
    bool zeroExp = (nu & expMask) == 0;
    bool non0Man = (nu & ~expMask) != 0;
    return zeroExp && non0Man;
}

bool isSubnormal(double number) {
    uint64_t nu = (toBytes(number) << 1);
    uint64_t expMask = 0xFFE0000000000000;
    bool zeroExp = (nu & expMask) == 0;
    bool non0Man = (nu & ~expMask) != 0;
    return zeroExp && non0Man;
}

template <typename T>
bool isSigned(T number) {
    return !isPositive(number);
}

template <typename T>
int fpclassify(T number) {
    if (isInfinity(number)) return FP_INFINITE;
    if (isNaN(number)) return FP_NAN;
    if (isNormal(number)) return FP_NORMAL;
    if (isSubnormal(number)) return FP_SUBNORMAL;
    if (isZero(number)) return FP_ZERO;
	else throw std::runtime_error("Unknown floating point type");
}

// Stage 3

float abso(float number) {
    return toBytes(number) & 0x7FFFFFFF;
}

double abso(double number) {
    return toBytes(number) & 0x7FFFFFFFFFFFFFFF;
}

template <typename T>
// the dunction assumes that the input isFinite
T min(T left, T right) {
    bool signedLeft = isSigned(left);

    if (signedLeft != isSigned(right)) {
        if (signedLeft) return left;
        else return right;
    }
    if ((toBytes(left) << 1) < (toBytes(right) << 1)) {
        if (signedLeft) return right;
        else return left;
    }
    if (signedLeft) return left;
    else return right;
}

template <typename T>
// the dunction assumes that the input isFinite
T max(T left, T right) {
    if (min(left, right) == right) return left;
    return right;
}

template <typename T>
// the dunction assumes that the input isFinite
T clamp(T value, T lower, T higher) {
    if (min(value, lower) == value) return lower;
    if (min(value, higher) == higher) return higher;
    return value;
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

void bruteforceCheck() {
    uint32_t nu = 1;
    //uint64_t nu = 1;
    float nuf;
    while (nu != 0) {
        nuf = toFloat(nu);
        //if (isFinite(nuf) != std::isfinite(nuf)) std::cout << nuf << std::endl;
        //if (isInfinity(nuf) != std::isinf(nuf)) std::cout << nuf << std::endl;
        //if (fpclassify(nuf) != std::fpclassify(nuf)) std::cout << nuf << std::endl;
        if (clamp(nuf, 23.23f, 2343.23423f) != std::clamp(nuf, 23.23f, 2343.23423f)) std::cout << nuf << std::endl;
        nu++;
    }
}

int main()
{
    bruteforceCheck();
    return 0;
}
