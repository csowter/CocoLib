#ifndef firfilter_h
#define firfilter_h

namespace CocoLib
{
template<typename T, unsigned int Length>
class FIRFilter
{
	T mSampleBuffer[Length];
	T mCoeffBuffer[Length];
	unsigned int mIndex;


public:
	FIRFilter(T coefficients[Length])
	{
		for (unsigned int i = 0; i < Length; i++)
		{
			mSampleBuffer[i] = 0;
			mCoeffBuffer[i] = coefficients[i];
		}

		mIndex = 0;
	}

	T Process(T sample)
	{
		mSampleBuffer[mIndex] = sample;

		unsigned int readIndex = mIndex;

		T output(0);

		for (unsigned int i = 0; i < Length; i++)
		{
			output += mCoeffBuffer[i] * mSampleBuffer[readIndex];

			if (readIndex == 0)
				readIndex = Length - 1;
			else
				readIndex--;
		}

		mIndex++;
		if (mIndex >= Length)
			mIndex = 0;

		return output;
	}

};
}

#endif
