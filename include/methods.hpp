// Copyright 2109 Andreev Semen semen.andreev00@mail.ru

#ifndef INCLUDE_METHODS_HPP
#define INCLUDE_METHODS_HPP

#include <stdexcept>

struct PassiveSearchResult {
    double Minimum;
    double Delta;
};

struct DichotomySearchResult {

};

void IfInvalidBoundsThrow(double a, double b);

template < typename Func >
PassiveSearchResult PassiveSearch(Func func, double a, double b, size_t pointsNum) {
    IfInvalidBoundsThrow(a, b);

    PassiveSearchResult result{};
    result.Delta = (b - a)/(pointsNum + 1.);

    double leftPoint = a + result.Delta;
    double rightPoint = b - result.Delta;

    for (size_t counter = 0; counter < pointsNum; ++counter) {
        double leftResult = func(leftPoint);
        double rightResult = func(rightPoint);

        if (leftResult < rightResult) {
            result.Minimum = leftResult;
            rightPoint -= result.Delta;
        } else {
            result.Minimum = rightResult;
            leftPoint += result.Delta;
        }
    }

    return result;
}

template <typename Func >
double DichotomySearch(Func func, double a, double b, double epsilon, double delta) {
    IfInvalidBoundsThrow(a, b);

    if (2*delta >= epsilon)
        throw std::invalid_argument{
            "2*delta must be less than epsilon"
        };

    while (true) {
        double ak = (a + b)/2. - delta;
        double bk = (a + b)/2. + delta;

        double akResult = func(ak);
        double bkResult = func(bk);

        if (akResult < bkResult) {
            b = bk;
        } else {
            a = ak;
        }

        if (b - a < epsilon)
            return (akResult + bkResult)/2.;
    }
}

#endif // INCLUDE_METHODS_HPP
