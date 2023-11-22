#pragma once
#include <vector>

namespace MyMath2D
{
	float GetRandomFloat(float a, float b);

	enum class InterpMode
	{
		INTERP_LINEAR = 0,
		INTERP_EASE_IN,
		INTERP_EASE_OUT,
		INTERP_EASE_INOUT,
		INTERP_PROPORTIONAL,
		INTERP_SPRING,
		MAX_INTERPS
	};

	float interpolate(float startValue, float endValue, float startTime, float endTime, float currentTime);

	float ClampFloat(float value, float v_min, float v_max);
}

