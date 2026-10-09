#include "types.hpp"

// Этот файл нужно реализовать.
// Сигнатуры в types.hpp менять нельзя.

int DivideInts(int a, int b) {
    return a/b;
}

double DivideAsDouble(int a, int b) {
    return (double)a/b;
}

bool FitsInInt(long long value) {
    return ((int)value==value);
}

long long SumAsLongLong(int a, int b) {
    return (long long)a+b;
}
