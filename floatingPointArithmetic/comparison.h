#pragma once

#include "classification.h"

// Stage 3 & 4: min, max, less, abs (& precision)
// inspired by: https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/?utm_source=chatgpt.com

float abso(float number);
double abso(double number);
template <typename T> bool lessThan(T left, T right);
template <typename T> T min(T left, T right);
template <typename T> T max(T left, T right);
template <typename T> T clamp(T value, T lower, T higher);
template <typename T> bool equalWithPrecision(T left, T right, T precision = FLT_EPSILON);
template <typename T> bool equalWithULPs(T left, T right, int ULPs = 4);
template <typename T> bool lessThanWithPrecision(T left, T right, T precision = FLT_EPSILON);
template <typename T> bool lessThanWithULPs(T left, T right, int ULPs = 4);
template <typename T> bool greaterThanWithPrecision(T left, T right, T precision = FLT_EPSILON);
template <typename T> bool greaterThanWithULPs(T left, T right, int ULPs = 4);
