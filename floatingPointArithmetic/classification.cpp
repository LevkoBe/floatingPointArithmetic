#include "classification.h"

// Stage 2: Finite, Infinity, NaN, etc.
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

template bool isPositiveInfinity<float>(float);
template bool isPositiveInfinity<double>(double);
template bool isNegativeInfinity<float>(float);
template bool isNegativeInfinity<double>(double);
template bool isZero<float>(float);
template bool isZero<double>(double);
template bool isPositiveZero<float>(float);
template bool isPositiveZero<double>(double);
template bool isNegativeZero<float>(float);
template bool isNegativeZero<double>(double);
template bool isSigned<float>(float);
template bool isSigned<double>(double);
template int fpclassify<float>(float);
template int fpclassify<double>(double);
