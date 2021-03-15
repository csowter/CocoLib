#ifndef softtimer_h
#define softtimer_h

#include <cstdint>
#include "TimerInterface.h"

namespace CocoLib
{
	class SoftTimer
	{
	private:
		TimerInterface *mTimer;
		uint32_t mStartTicks;
		uint32_t mDuration;
		bool mElapsed;



	public:
		SoftTimer(TimerInterface *timer, uint32_t durationMilliSeconds);
		void Restart();
		bool Elapsed();
	};
}

#endif
