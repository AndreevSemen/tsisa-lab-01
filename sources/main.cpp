// Copyright 2019 Andreev Semen semen.andreev00@mail.ru

#include <cmath>
#include <iostream>
#include <fstream>

#include <methods.hpp>

struct Function {
    double operator()(double x) {
        return cos(x)*tanh(x);
    }
};

int main() {
    const double epsilon = 0.1;

    std::ofstream file("./passive_result.txt", std::ios::trunc);
    PassiveSearchResult::LogHeader(file);
    for (size_t i = 1; ; ++i) {
        auto result = PassiveSearch(Function {}, 1, 4, i);
        result.LogResult(file);
        if (result.Epsilon() < epsilon) break;
    }
    PassiveSearchResult::LogFooter(file);
    file.close();

    file = std::ofstream{"./dichotomy_result.txt", std::ios::trunc};
    auto results = DichotomySearch(Function{}, 1, 4, 0.1, 0.04);

    DichotomySearchResult::LogHeader(file);
    for (const auto& result : results) {
        result.LogResult(file, epsilon);
    }
    DichotomySearchResult::LogFooter(file);

    file.close();

    return 0;
}
