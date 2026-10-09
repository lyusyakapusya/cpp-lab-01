#include "journal.hpp"

#include <iomanip>
#include <iostream>
#include <string>

// Каркас уже читает имя и число баллов и печатает отчёт.
// Нужно дописать две проверки и тело цикла.
// Функции лежат в journal.cpp.
//
// Вход:
//   <имя из одного слова>
//   <n>
//   затем n целых баллов
//
// При n < 0 программа печатает ровно одну строку `invalid count` и возвращает 1.
// При балле вне 0..100 печатает ровно `invalid score` и возвращает 1.
// Отчёт в этих двух случаях печатать нельзя.

int main() {
    std::string name;
    int n = 0;
    if (!(std::cin >> name >> n)) {
        return 0;
    }

    if (n < 0) {
        std::cout<< "invalid count"<<std::endl;
        return 1;
        // TODO: напечатать invalid count и завершить программу с кодом 1.
    }

    long long sum = 0;
    int min_score = 0;
    int max_score = 0;
    int passed = 0;
    bool has_score = false;

    for (int i = 0; i < n; ++i) {
        int score = 0;
        std::cin >> score;
        if (!IsValidScore(score)) {
            std::cout<<"invalid score"<<std::endl;
            return 1;
        }
        sum = AddToSum(sum, score);
        min_score = NextMin(has_score, min_score, score);
        max_score = NextMax(has_score, max_score, score);
        passed = NextPassed(passed, score);
        has_score = true;
        // TODO:
        // 1. Если !IsValidScore(score), напечатать invalid score и вернуть 1.
        // 2. sum = AddToSum(...)
        // 3. min_score = NextMin(has_score, ...)
        //    max_score = NextMax(has_score, ...)
        //    Эти две функции вызывайте, пока has_score ещё false для первого балла.
        // 4. passed = NextPassed(...)
        // 5. has_score = true
        (void)score;
    }

    const int count = n;
    const int failed = count - passed;

    std::cout << "name: " << name << '\n';
    std::cout << "count: " << count << '\n';
    std::cout << "sum: " << sum << '\n';
    if (count == 0) {
        std::cout << "average: n/a\n";
        std::cout << "min: n/a\n";
        std::cout << "max: n/a\n";
    } else {
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "average: " << Average(sum, count) << '\n';
        std::cout << "min: " << min_score << '\n';
        std::cout << "max: " << max_score << '\n';
    }
    std::cout << "passed: " << passed << '\n';
    std::cout << "failed: " << failed << '\n';
    std::cout << "verdict: " << Verdict(count, passed, min_score) << '\n';
    return 0;
}

