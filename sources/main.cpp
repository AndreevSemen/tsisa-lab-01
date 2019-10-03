// Copyright 2019 Andreev Semen semen.andreev00@mail.ru

#include <cmath>
#include <iostream>

#include <methods.hpp>

struct Function {
    double operator()(double x) {
        return cos(x)*tanh(x);
    }
};

int main() {
    auto result = PassiveSearch(Function{}, 1, 4,100);
    std::cout << result.Minimum << std::endl;

    double res = DichotomySearch(Function{}, 1, 4, 0.1, 0.04);
    std::cout << res << std::endl;

    return 0;
}
