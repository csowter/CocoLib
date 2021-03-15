#ifndef interpolator_h
#define interpolator_h

namespace CocoLib
{
	template <typename T>
	class Interpolator
	{
	public:
		static T LinearInterpolate(T xMin, T xMax, T yMin, T yMax, T value)
		{
			return yMin + (value - xMin) * ((yMax - yMin) / (xMax - xMin));
		}
	};
}

#endif
