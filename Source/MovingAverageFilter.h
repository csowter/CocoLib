#ifndef movingaveragefilter_h
#define movingaveragefilter_h

namespace Cocolib
{
template <typename T, unsigned int Length>
class MovingAverageFilter
{
	T mBuffer[Length];
	unsigned int mIndex;
	T mSum;

public:
	MovingAverageFilter()
	: mIndex{0}
	, mSum{ 0 }
	{
		for (unsigned int i = 0; i < Length; i++)
		{
			mBuffer[i] = 0;
		}
	}

	T Process(T sample)
	{
		mSum -= mBuffer[mIndex];
		mBuffer[mIndex] = sample;
		mSum += mBuffer[mIndex];

		mIndex++;
		if (mIndex >= Length)
		{
			mIndex = 0;
		}

		T filtered = mSum / Length;
		return filtered;
	}
};
}

#endif
