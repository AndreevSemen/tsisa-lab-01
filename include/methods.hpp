    // Copyright 2109 Andreev Semen semen.andreev00@mail.ru

    #ifndef INCLUDE_METHODS_HPP
    #define INCLUDE_METHODS_HPP

    #include <stdexcept>
    #include <iostream>
    #include <vector>
    #include <limits>
    #include <iomanip>

    struct SearchResult {};

    class PassiveSearchResult : public SearchResult {
    private:
        size_t _N;
        double _x;
        double _F_x;
        double _minimum;
        double _delta;

    public:
        PassiveSearchResult(size_t N, double x, double F_x, double minimum, double delta);

        size_t GetN() const;
        double GetX() const;
        double GetMinimum() const;
        double GetEpsilon() const;
        double GetF_x() const;

        void SetMinimum(double minimum);

        template < class Logger >
        static void LogHeader(Logger& logger) {
            logger << "_______________________________" << std::endl;
            logger << "|   N   |     xk   |    F(x)  |" << std::endl;
        }

        template < class Logger >
        void LogResult(Logger& logger) const {
            LogFooter(logger);
            logger << "|" << std::setw(7) << GetN();
            logger << "|" << std::setw(10) << GetX();
            logger << "|" << std::setw(10) << GetF_x();
            logger << "|" << std::endl;
        }

        template < class Logger >
        static void LogFooter(Logger& logger) {
            logger << "|_______|__________|__________|" << std::endl;
        }
    };

    class DichotomySearchResult : public SearchResult {
    private:
        double _ak;
        double _bk;
        double _x1;
        double _x2;
        double _f_ak;
        double _f_bk;

    public:
        DichotomySearchResult(double ak, double bk, double x1, double x2, double f_ak, double f_bk);

        bool IsValidInterval(double epsilon) const;

        double CalculateMinimum() const;

        template < class Logger >
        static void LogHeader(Logger& logger) {
            logger << "_______________________________________________________________________" << std::endl;
            logger << "|    ak   |    bk   |    lk   |    x1   |    x2   |  f(ak)  |  f(bk)  |" << std::endl;
        }

        template < class Logger >
        void LogResult(Logger& logger, double epsilon) const {
            LogFooter(logger);
            logger << "|" << std::setw(9) << _ak;
            logger << "|" << std::setw(9) << _bk;
            logger << "|" << std::setw(9) << IntervalLength();
            logger << "|" << std::setw(9) << _x1;
            logger << "|" << std::setw(9) << _x2;

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
            logger << "|_________|_________|_________|_________|_________|_________|_________|" << std::endl;
        }

    private:
        double IntervalLength() const;
    };

    void IfInvalidBoundsThrow(double a, double b);

    template < typename Func>
    std::vector<PassiveSearchResult> PassiveSearch(Func func, double a, double b,
                                                   double epsilon) {
        IfInvalidBoundsThrow(a, b);
        std::vector<PassiveSearchResult> results;

        size_t N = 2*(b - a)/epsilon - 1;
        double delta = (b - a)/(N + 1.);

        double minimum = std::numeric_limits<double>::max();

        for (size_t k = 1; k <= N; ++k) {
            double xk = a + k*delta;
            double F_xk = func(xk);

            if (F_xk < minimum) {
                minimum = F_xk;
            }

            PassiveSearchResult result{k, xk, F_xk, minimum, delta};
            results.push_back(result);
        }

        return results;
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
            double x1 = (a + b)/2. - delta;
            double x2 = (a + b)/2. + delta;

            double f_ak = func(x1);
            double f_bk = func(x2);

            DichotomySearchResult result{a, b, x1, x2, f_ak, f_bk};
            results.push_back(result);

            if (!result.IsValidInterval(epsilon)) {
                return results;
            }

            if (f_ak < f_bk) {
                b = x2;
            } else {
                a = x1;
            }
        }
    }

    #endif // INCLUDE_METHODS_HPP
