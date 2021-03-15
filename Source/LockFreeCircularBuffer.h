#ifndef lockfreecircularbuffer_h
#define lockfreecircularbuffer_h

#include "BufferStatus.h"

namespace CocoLib
{

template <typename T, unsigned int Length>
class LockFreeCircularBuffer
{
	volatile T mBuffer[Length];
	volatile unsigned int mHead{0};
	volatile unsigned int mTail{0};
	
public:
	LockFreeCircularBuffer(LockFreeCircularBuffer const&) = delete;
	LockFreeCircularBuffer& operator=(LockFreeCircularBuffer const&) = delete;
	LockFreeCircularBuffer() {}

	bool IsEmpty() const
	{
		return mHead == mTail;
	}
	
	bool IsFull() const
	{
		return ((mHead + 1) % Length) == mTail;
	}
	
	BufferStatus Add(const T& item)
	{
		unsigned int inPos = (mHead + 1) % Length;
		if(inPos == mTail)
			return BufferStatus::Full;
		
		mBuffer[mHead] = item;
		mHead = inPos;
		return BufferStatus::OK;
	}
	
	BufferStatus Remove(T& item)
	{
		if(mHead == mTail)
			return BufferStatus::Empty;
		
		item = mBuffer[mTail];
		mTail = (mTail + 1) % Length;
		return BufferStatus::OK;
	}
};
}

#endif
