#ifndef mocktimer_h
#define mocktimer_h

#include "TimerInterface.h"

class MockTimer : public CocoLib::TimerInterface
{
	uint32_t mTickCount;
	uint32_t mTicksPerMilliSecond;

public:
	MockTimer(uint32_t ticksPerMilliSecond);
	void Tick();
	uint32_t GetTicks() override;
	uint32_t TicksPerMilliSecond() override;
};

#endif
