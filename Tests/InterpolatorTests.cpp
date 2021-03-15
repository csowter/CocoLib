#include "catch.hpp"
#include "Interpolator.h"

SCENARIO("Minimum", "[Interpolator]")
{
	GIVEN("Input ranges")
	{
		uint32_t xMin = 0;
		uint32_t xMax = 100;
		uint32_t yMin = 0;
		uint32_t yMax = 10000;

		WHEN("0 is interpolated")
		{
			uint32_t interp = CocoLib::Interpolator<uint32_t>::LinearInterpolate(xMin, xMax, yMin, yMax, 0);
			THEN("0 is returned")
			{
				REQUIRE(0 == interp);
			}
		}
	}
}

SCENARIO("Maximum", "[Interpolator]")
{
	GIVEN("Input ranges")
	{
		uint32_t xMin = 0;
		uint32_t xMax = 100;
		uint32_t yMin = 0;
		uint32_t yMax = 10000;

		WHEN("100 is interpolated")
		{
			uint32_t interp = CocoLib::Interpolator<uint32_t>::LinearInterpolate(xMin, xMax, yMin, yMax, 100);
			THEN("10000 is returned")
			{
				REQUIRE(10000 == interp);
			}
		}
	}
}

SCENARIO("LinearInterpolation", "[Interpolator]")
{
	GIVEN("Input ranges")
	{
		uint32_t xMin = 0;
		uint32_t xMax = 100;
		uint32_t yMin = 0;
		uint32_t yMax = 10000;

		WHEN("25 is interpolated")
		{
			uint32_t interp = CocoLib::Interpolator<uint32_t>::LinearInterpolate(xMin, xMax, yMin, yMax, 25);
			THEN("2500 is returned")
			{
				REQUIRE(2500 == interp);
			}
		}
	}
}