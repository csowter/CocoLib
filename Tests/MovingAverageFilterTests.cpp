#include "catch.hpp"

#include "MovingAverageFilter.h"

SCENARIO("Average is available before filter is full", "[MovingAverage]")
{
	GIVEN("A moving average with length 4")
	{
		Cocolib::MovingAverageFilter<uint32_t, 4> filter;
		WHEN("one sample with the value 20 is added")
		{
			uint32_t output = filter.Process(20);
			THEN("The output is one quarter")
			{
				REQUIRE(5 == output);
			}
		}
	}
}

SCENARIO("Average is available before filter is full 2", "[MovingAverage]")
{
	GIVEN("A moving average with length 4")
	{
		Cocolib::MovingAverageFilter<uint32_t, 4> filter;
		WHEN("two samples with the value 20 is added")
		{
			filter.Process(20);
			uint32_t output = filter.Process(20);
			THEN("The output is one half")
			{
				REQUIRE(10 == output);
			}
		}
	}
}