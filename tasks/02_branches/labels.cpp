#include "labels.hpp"

std::string SignLabel(int value) {
    if (value < 0) return "negative";
    if (value > 0) return "positive";
    if (value == 0) return "zero";
}

std::string ParityLabel(int value) {
    if (value%2==0) return "even";
    if (value%2!=0) return "odd";
}

std::string GradeLabel(int score) {
    if (score < 0 || score > 100) return "invalid";
    if (score  >= 0 && score <= 59) return "fail";
    if (score >=60 && score <= 74) return "pass";
    if (score >=75 && score <= 89) return "good";
    if (score >=90 && score <=100) return "excellent";

}
