#include "MockTimer.h"

MockTimer::MockTimer(uint32_t ticksPerMilliSecond)
: mTickCount{ 0 }
, mTicksPerMilliSecond{ ticksPerMilliSecond }
{

}

void MockTimer::Tick()
{
	++mTickCount;
}

uint32_t MockTimer::GetTicks()
{
	return mTickCount;
}

uint32_t MockTimer::TicksPerMilliSecond()
{
	return mTicksPerMilliSecond;
}
