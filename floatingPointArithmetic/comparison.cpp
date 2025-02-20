#include "comparison.h"

float abso(float number) {
    return toBytes(number) & 0x7FFFFFFF;
}

double abso(double number) {
    return toBytes(number) & 0x7FFFFFFFFFFFFFFF;
}

template <typename T>
// the function assumes that the input isFinite
bool lessThan(T left, T right) {
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
    return abso(toBytes(left) - toBytes(right)) <= ULPs;
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
