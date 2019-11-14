// Copyright 2109 Andreev Semen semen.andreev00@mail.ru

#include <methods.hpp>

PassiveSearchResult::PassiveSearchResult(size_t N, double x, double F_x, double minimum, double delta)
  : SearchResult{}
  , _N{N}
  , _F_x{F_x}
  , _x{x}
  , _minimum{minimum}
  , _delta{delta}
{}

size_t PassiveSearchResult::GetN() const {
    return _N;
}

double PassiveSearchResult::GetX() const {
    return _x;
}

double PassiveSearchResult::GetMinimum() const {
    return _minimum;
}

double PassiveSearchResult::GetEpsilon() const {
    return 2*_delta;
}

double PassiveSearchResult::GetF_x() const {
    return _F_x;
}

void PassiveSearchResult::SetMinimum(double minimum) {
    _minimum = minimum;
}

DichotomySearchResult::DichotomySearchResult(double ak, double bk, double x1, double x2,double f_ak, double f_bk)
  : SearchResult{}
  , _ak{ak}
  , _bk{bk}
  , _x1{x1}
  , _x2{x2}
  , _f_ak{f_ak}
  , _f_bk{f_bk}
{}

bool DichotomySearchResult::IsValidInterval(double epsilon) const {
    return IntervalLength() > epsilon;
}

double DichotomySearchResult::CalculateMinimum() const {
    return (_f_ak + _f_bk)/.2;
}

double DichotomySearchResult::IntervalLength() const {
    return _bk - _ak;
}

void IfInvalidBoundsThrow(double a, double b) {
    if (a >= b) throw std::invalid_argument{
        "Left interval bound must be less than right bound"
    };
}
