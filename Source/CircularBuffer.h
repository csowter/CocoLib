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
	volatile bool mFull{ false };

	std::mutex mMutex;
	
public:
	CircularBuffer(CircularBuffer const&) = delete;
	CircularBuffer& operator=(CircularBuffer const&) = delete;
	CircularBuffer() {}

	unsigned int Size() const
	{
		return Length;
	}

	unsigned int Count() 
	{
		std::lock_guard<std::mutex> lock(mMutex);

		if (mFull)
			return Length;

		if (mHead >= mTail)
			return mHead - mTail;
		else
			return (Length + mHead) - mTail;
	}

	bool IsEmpty() 
	{
		std::lock_guard<std::mutex> lock(mMutex);

		return !mFull && (mHead == mTail);
	}
	
	bool IsFull() 
	{
		std::lock_guard<std::mutex> lock(mMutex);

		return mFull;
	}
	
	BufferStatus Add(const T& item)
	{
		std::lock_guard<std::mutex> lock(mMutex);

		if(mFull)
			return BufferStatus::Full;
		
		mBuffer[mHead] = item;
		
		mHead = (mHead + 1) % Length;

		if (mHead == mTail)
			mFull = true;

		return BufferStatus::OK;
	}
	
	BufferStatus Remove(T& item)
	{
		std::lock_guard<std::mutex> lock(mMutex);

		if(mHead == mTail && !mFull)
			return BufferStatus::Empty;
		
		item = mBuffer[mTail];
		mTail = (mTail + 1) % Length;
		mFull = mHead == mTail;
		return BufferStatus::OK;
	}
};
}

#endif
