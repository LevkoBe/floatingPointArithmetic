#pragma once
#include <bit>

// Stage 1: to and fro
uint32_t toBytes(float const value);
uint64_t toBytes(double const value);
float toFloat(uint32_t const value);
double toDouble(uint64_t const value);

template <typename T>
void checkConversion(T number);

void checkStage1();
