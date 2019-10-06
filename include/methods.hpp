// Copyright 2109 Andreev Semen semen.andreev00@mail.ru

#ifndef INCLUDE_METHODS_HPP
#define INCLUDE_METHODS_HPP

#include <stdexcept>
#include <iostream>
#include <vector>

struct SearchResult {};

struct PassiveSearchResult : public SearchResult {
    double Minimum;
    double Epsilon;

    template < class Logger >
    void Log(Logger& logger) const {
        logger << "Minimum: " << Minimum
               << " Epsilon: " << Epsilon << std::endl;
    }
};

struct DichotomySearchResult : public SearchResult {
    double IntervalBegin;
    double IntervalEnd;
    std::pair<double, double> Points;

    template < class Logger >
    void Log(Logger& logger) const {
        logger << "a: " << IntervalBegin
               << " b: " << IntervalEnd
               << " ak: " << Points.first
               << " bk: " << Points.second << std::endl;
    }
};

void IfInvalidBoundsThrow(double a, double b);

template < typename Func>
PassiveSearchResult PassiveSearch(Func func, double a, double b,
                                  size_t pointsNum) {
    IfInvalidBoundsThrow(a, b);

    PassiveSearchResult result{};
    result.Epsilon = (b - a)/(pointsNum + 1.);

    double leftPoint = a + result.Epsilon;
    double rightPoint = b - result.Epsilon;

    for (size_t counter = 0; counter < pointsNum; ++counter) {
        double leftResult = func(leftPoint);
        double rightResult = func(rightPoint);

        if (leftResult < rightResult) {
            result.Minimum = leftResult;
            rightPoint -= result.Epsilon;
        } else {
            result.Minimum = rightResult;
            leftPoint += result.Epsilon;
        }
    }

    return result;
}

template < typename Func >
std::vector<DichotomySearchResult> DichotomySearch(Func func, double a, double b,
                                                   double epsilon, double delta) {
    IfInvalidBoundsThrow(a, b);

    if (2*delta >= epsilon)
        throw std::invalid_argument{
            "2*delta must be less than epsilon"
        };

    std::vector<DichotomySearchResult> results{};

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

        DichotomySearchResult result;
        result.IntervalBegin = a;
        result.IntervalEnd = b;
        result.Points = {akResult, bkResult};
        results.push_back(std::move(result));

        if (b - a < epsilon) {
            return results;
        }
    }
}

#endif // INCLUDE_METHODS_HPP
