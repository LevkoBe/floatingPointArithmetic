#pragma once
#include "conversion.h"
#include <iostream>

bool isFinite(float number);
bool isFinite(double number);
bool isInfinity(float number);
bool isInfinity(double number);
bool isSigned(float number);
bool isSigned(double number);
template <typename T> bool isPositiveInfinity(T number);
template <typename T> bool isNegativeInfinity(T number);
template <typename T> bool isZero(T number);
template <typename T> bool isPositiveZero(T number);
template <typename T> bool isNegativeZero(T number);
bool isNaN(float number);
bool isNaN(double number);
bool isNormal(float number);
bool isNormal(double number);
bool isSubnormal(float number);
bool isSubnormal(double number);
template <typename T> int fpclassify(T number);
