#include "catch.hpp"

#include "SoftTimer.h"
#include "MockTimer.h"

SCENARIO("TimerIsNotElapsedBeforeHWTimerReachesCount", "[SoftTimer]")
{
	GIVEN("A timer is created")
	{
		MockTimer hwTimer(10);
		CocoLib::SoftTimer softTimer(&hwTimer, 10);
		WHEN("timer is ticked, but not to reach duration")
		{
			for (int i = 0; i < 99; i++)
				hwTimer.Tick();

			THEN("The timer has not elapsed")
			{
				REQUIRE(!softTimer.Elapsed());
			}
		}
	}
}

SCENARIO("TimerIsElapsedOnceHWTimerReachesCount", "[SoftTimer]")
{
	GIVEN("A timer is created")
	{
		MockTimer hwTimer(10);
		CocoLib::SoftTimer softTimer(&hwTimer, 10);

		WHEN("The time has passed")
		{
			for(int i = 0; i < 100; i++)
				hwTimer.Tick();

			THEN("The timer is elapsed")
			{
				REQUIRE(softTimer.Elapsed());
			}
		}
	}
}

SCENARIO("TimerHasSameDurationWhenRestarted", "[SoftTimer]")
{
	GIVEN("A timer has elapsed")
	{
		MockTimer hwTimer(10);
		CocoLib::SoftTimer softTimer(&hwTimer, 10);

		for (int i = 0; i < 50; i++)
			hwTimer.Tick();

		REQUIRE(!softTimer.Elapsed());

		WHEN("The timer is restarted")
		{
			softTimer.Restart();
			for (int i = 0; i < 99; i++)
				hwTimer.Tick();

			THEN("The timer requires the same period")
			{
				REQUIRE(!softTimer.Elapsed());

				hwTimer.Tick();

				REQUIRE(softTimer.Elapsed());
			}
		}
	}
}

SCENARIO("TimerIsNotElapsedWhenRestarted", "[SoftTimer]")
{
	GIVEN("A timer has elapsed")
	{
		MockTimer hwTimer(10);
		CocoLib::SoftTimer softTimer(&hwTimer, 10);

		for (int i = 0; i < 100; i++)
			hwTimer.Tick();

		REQUIRE(softTimer.Elapsed());
		WHEN("The timer is restarted")
		{
			softTimer.Restart();
			THEN("The timer is not elapsed")
			{
				REQUIRE(!softTimer.Elapsed());
			}
		}
	}
}

SCENARIO("TimerRemainsElapsedOnceTimeHasPassed", "[SoftTimer]")
{
	GIVEN("A timer has elapsed")
	{
		MockTimer hwTimer(10);
		CocoLib::SoftTimer softTimer(&hwTimer, 10);

		for (int i = 0; i < 100; i++)
			hwTimer.Tick();

		REQUIRE(softTimer.Elapsed());
		WHEN("The hw timer continues to tick")
		{
			for (int i = 0; i < 10; i++)
				hwTimer.Tick();

			THEN("The timer remains elapsed")
			{
				REQUIRE(softTimer.Elapsed());
			}
		}
	}
}
