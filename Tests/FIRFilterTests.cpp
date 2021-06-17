#include "catch.hpp"

#include "FIRFilter.h"

float coeff[] = { 1.0f, 0.0f, 0.0f, 0.0f };

CocoLib::FIRFilter<float, 4> filter(coeff);
