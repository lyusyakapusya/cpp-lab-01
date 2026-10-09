#include <iostream>

// Прочитать n, затем n целых чисел.
// Напечатать сумму, минимум, максимум и число строго положительных.
// Формат вывода уже собран ниже, менять его не нужно.
// n в тестах всегда >= 0. При n == 0 чисел дальше нет.

int main() {
    int n = 0;
    if (!(std::cin >> n)) {
        return 0;
    }

    long long sum = 0;
    int positive = 0;
    bool has_value = false;
    int min_value = 0;
    int max_value = 0;

    for (int i = 0; i < n; ++i) {
        int value = 0;
        std::cin >> value;
        sum+=value;
        if (!has_value) {
            min_value = value;
            max_value = value;
            has_value = true;
        }
        max_value = std::max(value,max_value);
        min_value = std::min(value,min_value);
        if (value > 0) positive++;

        // TODO: обновите sum, positive, min_value, max_value и has_value.
        // positive считает числа строго больше нуля.
        // Ноль и отрицательные в positive не входят.
        // min и max существуют только после первого числа: смотрите на has_value.
        // sum копите в long long: три числа 1000000000 в int не влезают.
        (void)value;
    }

    std::cout << "sum: " << sum << '\n';
    if (!has_value) {
        std::cout << "min: none\n";
        std::cout << "max: none\n";
    } else {
        std::cout << "min: " << min_value << '\n';
        std::cout << "max: " << max_value << '\n';
    }
    std::cout << "positive: " << positive << '\n';
    return 0;
}