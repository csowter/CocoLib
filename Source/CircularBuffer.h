#ifndef circularbuffer_h
#define circularbuffer_h

#include <mutex>
#include "BufferStatus.h"

namespace CocoLib
{

template <typename T, unsigned int Length>
class CircularBuffer
{
	volatile T mBuffer[Length];
	volatile unsigned int mHead{0};
	volatile unsigned int mTail{0};

	std::mutex mMutex;
	
public:
	CircularBuffer(CircularBuffer const&) = delete;
	CircularBuffer& operator=(CircularBuffer const&) = delete;
	CircularBuffer() {}
	bool IsEmpty()
	{
		std::lock_guard<std::mutex> lock(mMutex);
		return mHead == mTail;
	}

	bool IsFull()
	{
		std::lock_guard<std::mutex> lock(mMutex);
		return ((mHead + 1) % Length) == mTail;
	}

	BufferStatus Add(const T& item)
	{
		std::lock_guard<std::mutex> lock(mMutex);
		unsigned int inPos = (mHead + 1) % Length;
		if (inPos == mTail)
			return BufferStatus::Full;

		mBuffer[mHead] = item;
		mHead = inPos;
		return BufferStatus::OK;
	}

	BufferStatus Remove(T& item)
	{
		std::lock_guard<std::mutex> lock(mMutex);
		if (mHead == mTail)
			return BufferStatus::Empty;

		item = mBuffer[mTail];
		mTail = (mTail + 1) % Length;
		return BufferStatus::OK;
	}
};
}

#endif
