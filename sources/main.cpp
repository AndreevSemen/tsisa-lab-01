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
    std::ofstream file("./passive_result.txt", std::ios::trunc);
    for (size_t i = 0; ; ++i) {
        auto result = PassiveSearch(Function {}, 1, 4, i);
        result.Log(file);
        if (result.Epsilon < 0.1) break;
    }
    file.close();

    file = std::ofstream{"./dichotomy_result.txt", std::ios::trunc};
    auto results = DichotomySearch(Function{}, 1, 4, 0.1, 0.04);
    for (const auto& result : results) {
        result.Log(file);
    }

    return 0;
}
