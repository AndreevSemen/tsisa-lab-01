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

    auto results = PassiveSearch(Function{}, -2, 0, epsilon);

    std::ofstream file("./passive_result.txt", std::ios::trunc);

    PassiveSearchResult::LogHeader(file);
    for (const auto& result : results) {
        result.LogResult(file);
    }
    PassiveSearchResult::LogFooter(file);
    file << "Minimum : " << results.back().GetMinimum() << " +/- " << results.back().GetEpsilon();

    file.close();



    file = std::ofstream{"./dichotomy_result.txt", std::ios::trunc};
    auto dResults = DichotomySearch(Function{}, -2, 0, 0.1, 0.001);

    DichotomySearchResult::LogHeader(file);
    for (const auto& result : dResults) {
        result.LogResult(file, epsilon);
    }
    DichotomySearchResult::LogFooter(file);
    file << "Minimum : " << dResults.back().CalculateMinimum();

    file.close();

    return 0;
}
