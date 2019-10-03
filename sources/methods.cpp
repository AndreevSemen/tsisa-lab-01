// Copyright 2109 Andreev Semen semen.andreev00@mail.ru

#include <methods.hpp>

void IfInvalidBoundsThrow(double a, double b) {
    if (a >= b) throw std::invalid_argument{
        "Left interval bound must be less than right bound"
    };
}
