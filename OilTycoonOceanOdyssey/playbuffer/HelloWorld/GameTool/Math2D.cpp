#include "Play.h"
#include "Math2D.h"
#include "Timer.h"
using namespace std;

namespace MyMath2D
{
	float GetRandomFloat(float a, float b)
	{
		return ((b - a) * ((float)rand() / RAND_MAX)) + a;
	}

	float interpolate(float startValue, float endValue, float startTime, float endTime, float currentTime) {
		// Calculate the time interval between the start and end times
		float timeInterval = endTime - startTime;

		// Calculate the value interval between the start and end values
		float valueInterval = endValue - startValue;

		// Calculate the fraction of time that has elapsed
		float timeFraction = (currentTime - startTime) / timeInterval;

		// Calculate the interpolated value
		float interpolatedValue = startValue + (valueInterval * timeFraction);

		// Return the interpolated value
		return interpolatedValue;
	}

	float ClampFloat(float value, float v_min, float v_max)
	{
		if (value <= v_min)
		{
			value = v_min;
		}
		if (value >= v_max)
		{
			value = v_max;
		}
		return value;
	}
}


