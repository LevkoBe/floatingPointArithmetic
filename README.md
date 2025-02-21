# Homework 1: Floating Point Arithmetic

## Repository Structure

### 1. **Main Project: floatingPointArithmetic**

This project contains implementations for the following tasks:

- **Task 1**: Floating-point conversion (`conversion.h`, `conversion.cpp`)
- **Task 2**: Classification of floating-point numbers (`classification.h`, `classification.cpp`)
- **Tasks 3 & 4**: Floating-point comparison operations (`comparison.h`, `comparison.cpp`)
- **Task 6**: Little-endian to decimal conversion (`littleEndianToDecimal.cpp`)

### 2. **Unit Tests: Testing the Implementation (Task 5)**

A separate project containing **unit tests** to verify the correctness of the implemented functions.

### 3. **Theoretical Questions: Task 7**

This section contains answers to theoretical questions related to floating-point arithmetic:

#### d) Can `(X != X)` be `true` for a floating-point variable `X`?

I believe so, and the reason is that not all types are comparable. So whilst normal, infinite, and subnormal numbers may be smaller, greater, or equal, floats representing NaN, for instance, are not comparable, therefore they're not equal to themselves.

#### e) Is `Y = X * 0` always `0` for a floating-point variable `X`?

Again, not all types behave the same. After checking in the code, I can say that even infinities give some NaNs when multiplying by zero.

#### f) Can `((X + Y) == X)` be `true` for floating-point variables `X` and `Y`?

This is by far the easiest question. The issue with any operations with floats is that they never yield exact results, instead rounding to the closest representable one. This is particularly problematic when performing operations with operands differing significantly, which results in a very rough rounding even such that adding a number may not change the initial value.

#### g) Is `((X + Y) + Z) == (X + (Y + Z))` always `true` for floating-point variables `X`, `Y`, and `Z`?

The answer here largely resembles the previous: rounding error has a profound effect on the result, especially if numbers differ significantly, and also with each operation performed (accumulation of error). So in the case provided, adding X and Y might have rounding down, their result plus Z too, and we would get something smaller than the actual sum, and if the other case is opposite, `(X + (Y + Z))` will result in a number greater than actual. The point is, we never know what rounding will take place unless we calculate it precisely.
