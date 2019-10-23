// Copyright 2109 Andreev Semen semen.andreev00@mail.ru

#ifndef INCLUDE_METHODS_HPP
#define INCLUDE_METHODS_HPP

#include <stdexcept>
#include <iostream>
#include <vector>
#include <iomanip>

struct SearchResult {};

class PassiveSearchResult : public SearchResult {
private:
    size_t _N;
    double _minimum;
    double _delta;

public:
    PassiveSearchResult(double a, double b, size_t N);

    size_t GetN() const;
    double GetMinimum() const;
    double GetDelta() const;
    double Epsilon() const;

    void SetMinimum(double minimum);

    template < class Logger >
    static void LogHeader(Logger& logger) {
        logger << "____________________" << std::endl;
        logger << "|   N   |     x*   |" << std::endl;
    }

    template < class Logger >
    void LogResult(Logger& logger) const {
        LogFooter(logger);
        logger << "|" << std::setw(7) << GetN()
               << "|" << std::setw(10) << GetMinimum()
               << "|" << std::endl;
    }

    template < class Logger >
    static void LogFooter(Logger& logger) {
        logger << "|_______|__________|" << std::endl;
    }
};

class DichotomySearchResult : public SearchResult {
private:
    double _ak;
    double _bk;
    double _f_ak;
    double _f_bk;

public:
    DichotomySearchResult(double ak, double bk, double f_ak, double f_bk);

    bool IsValidInterval(double epsilon) const;

    template < class Logger >
    static void LogHeader(Logger& logger) {
        logger << "___________________________________________________" << std::endl;
        logger << "|    ak   |    bk   | bk - ak |  f(ak)  |  f(bk)  |" << std::endl;
    }

    template < class Logger >
    void LogResult(Logger& logger, double epsilon) const {
        LogFooter(logger);
        logger << "|" << std::setw(9) << _ak;
        logger << "|" << std::setw(9) << _bk;
        logger << "|" << std::setw(9) << IntervalLength();

        if (IsValidInterval(epsilon)) {
            logger << "|" << std::setw(9) << _f_ak;
            logger << "|" << std::setw(9) << _f_bk;
        } else {
            logger << "|" << std::setw(19) << "b - a < epsilon";
        }

        logger << "|" << std::endl;
    }

    template < class Logger >
    static void LogFooter(Logger& logger) {
        logger << "|_________|_________|_________|_________|_________|" << std::endl;
    }

private:
    double IntervalLength() const;
};

void IfInvalidBoundsThrow(double a, double b);

template < typename Func>
PassiveSearchResult PassiveSearch(Func func, double a, double b,
                                  size_t N) {
    IfInvalidBoundsThrow(a, b);

    PassiveSearchResult result{a, b, N};

    double leftPoint = a + result.GetDelta();
    double rightPoint = b - result.GetDelta();

    for (size_t counter = 0; counter < N; ++counter) {
        double leftResult = func(leftPoint);
        double rightResult = func(rightPoint);

        if (leftResult < rightResult) {
            result.SetMinimum(leftResult);
            rightPoint -= result.GetDelta();
        } else {
            result.SetMinimum(rightResult);
            leftPoint += result.GetDelta();
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

    std::vector<DichotomySearchResult> results;

    while (true) {
        double ak = (a + b)/2. - delta;
        double bk = (a + b)/2. + delta;

        double f_ak = func(ak);
        double f_bk = func(bk);

        DichotomySearchResult result{a, b, f_ak, f_bk};
        results.push_back(result);

        if (!result.IsValidInterval(epsilon)) {
            return results;
        }

        if (f_ak < f_bk) {
            b = bk;
        } else {
            a = ak;
        }
    }
}

#endif // INCLUDE_METHODS_HPP
