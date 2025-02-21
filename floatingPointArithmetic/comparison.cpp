#include "comparison.h"

float abso(float number) {
    return toFloat(toBytes(number) & 0x7FFFFFFF);
}

double abso(double number) {
    return toDouble(toBytes(number) & 0x7FFFFFFFFFFFFFFF);
}

template <typename T>
// the function assumes that the input isFinite
bool lessThan(T left, T right) {
	if (isZero(left) && isZero(right)) return false;

    bool signedLeft = isSigned(left);
    auto leftBitsShifted = toBytes(left) << 1;
    auto rightBitsShifted = toBytes(right) << 1;

    if (signedLeft != isSigned(right)) {
        if (signedLeft) return true;
        else return false;
    }
    if (leftBitsShifted < rightBitsShifted) {
        if (signedLeft) return false;
        else return true;
    }
    if (signedLeft && (rightBitsShifted < leftBitsShifted)) return true;
    else return false;
}

template <typename T>
// the function assumes that the input isFinite
T min(T left, T right) {
    if (lessThan(left, right)) return left;
    return right;
}

template <typename T>
// the function assumes that the input isFinite
T max(T left, T right) {
    if (lessThan(left, right)) return right;
    return left;
}

template <typename T>
// the function assumes that the input isFinite
T clamp(T value, T lower, T higher) {
    if (min(value, lower) == value) return lower;
    if (min(value, higher) == higher) return higher;
    return value;
}

template <typename T>
bool equalWithPrecision(T left, T right, T precision) {
    return lessThan(abso(left - right), precision * max(left, right));
}

template <typename T>
bool equalWithULPs(T left, T right, int ULPs) {
	auto leftBit = toBytes(left);
	auto rightBit = toBytes(right);
	if (leftBit < rightBit) std::swap(leftBit, rightBit);
    return (leftBit - rightBit) <= ULPs;
}

template <typename T>
// I assume that "with precision" means that the difference between the two numbers is greater than the precision
bool lessThanWithPrecision(T left, T right, T precision) {
    return lessThan(left + precision, right);
}
template <typename T>
bool lessThanWithULPs(T left, T right, int ULPs) {
    return lessThan(left, right) && !equalWithULPs(left, right);
}

template <typename T>
bool greaterThanWithPrecision(T left, T right, T precision) {
    return lessThan(right + precision, left);
}

template <typename T>
bool greaterThanWithULPs(T left, T right, int ULPs) {
    return lessThan(right, left) && !equalWithULPs(left, right);
}

template bool lessThan<float>(float, float);
template bool lessThan<double>(double, double);
template float min<float>(float, float);
template double min<double>(double, double);
template float max<float>(float, float);
template double max<double>(double, double);
template float clamp<float>(float, float, float);
template double clamp<double>(double, double, double);
template bool equalWithPrecision<float>(float, float, float);
template bool equalWithPrecision<double>(double, double, double);
template bool equalWithULPs<float>(float, float, int);
template bool equalWithULPs<double>(double, double, int);
template bool lessThanWithPrecision<float>(float, float, float);
template bool lessThanWithPrecision<double>(double, double, double);
template bool lessThanWithULPs<float>(float, float, int);
template bool lessThanWithULPs<double>(double, double, int);
template bool greaterThanWithPrecision<float>(float, float, float);
template bool greaterThanWithPrecision<double>(double, double, double);
template bool greaterThanWithULPs<float>(float, float, int);
template bool greaterThanWithULPs<double>(double, double, int);