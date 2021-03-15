#ifndef timerinterface_h
#define timerinterface_h

#include <cstdint>

namespace CocoLib
{
	class TimerInterface
	{
	public:
		virtual ~TimerInterface(){}
		virtual uint32_t GetTicks() = 0;
		virtual uint32_t TicksPerMilliSecond() = 0;
	};
}

#endif
