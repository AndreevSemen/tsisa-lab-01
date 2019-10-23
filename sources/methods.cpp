// Copyright 2109 Andreev Semen semen.andreev00@mail.ru

#include <methods.hpp>

PassiveSearchResult::PassiveSearchResult(double a, double b, size_t N)
  : SearchResult{}
  , _N{N}
  , _delta{(b - a)/(N + 1.)}
{}

size_t PassiveSearchResult::GetN() const {
    return _N;
}

double PassiveSearchResult::GetMinimum() const {
    return _minimum;
}

double PassiveSearchResult::GetDelta() const {
    return _delta;
}

double PassiveSearchResult::Epsilon() const {
    return 2 * GetDelta();
}

void PassiveSearchResult::SetMinimum(double minimum) {
    _minimum = minimum;
}

DichotomySearchResult::DichotomySearchResult(double ak, double bk, double f_ak, double f_bk)
  : SearchResult{}
  , _ak{ak}
  , _bk{bk}
  , _f_ak{f_ak}
  , _f_bk{f_bk}
{}

bool DichotomySearchResult::IsValidInterval(double epsilon) const {
    return IntervalLength() > epsilon;
}

double DichotomySearchResult::IntervalLength() const {
    return _bk - _ak;
}

void IfInvalidBoundsThrow(double a, double b) {
    if (a >= b) throw std::invalid_argument{
        "Left interval bound must be less than right bound"
    };
}
