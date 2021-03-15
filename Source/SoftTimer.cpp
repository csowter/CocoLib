#include "SoftTimer.h"

namespace CocoLib
{
	SoftTimer::SoftTimer(TimerInterface *timer, uint32_t durationMilliSeconds)
	: mTimer{ timer }
	, mStartTicks{ mTimer->GetTicks() }
	, mDuration{mTimer->TicksPerMilliSecond() * durationMilliSeconds}
	, mElapsed{ false }
	{

	}

	void SoftTimer::Restart()
	{
		mStartTicks = mTimer->GetTicks();
		mElapsed = false;
	}

	bool SoftTimer::Elapsed()
	{
		if (mElapsed)
			return true;

		if (mTimer->GetTicks() >= mStartTicks + mDuration)
		{
			mElapsed = true;
			return true;
		}

		return false;
	}
}
