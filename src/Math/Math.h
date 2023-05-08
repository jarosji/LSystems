#pragma once
#include <cstdlib>

class Math {

public:
	static inline float Lerp(float a, float b, float t) {
		return a + (b - a) * Clamp01(t);
	}

	static inline float Clamp01(float value)
	{
		if (value < 0)
			return 0;
		else if (value > 1)
			return 1;
		else
			return value;
	}
	static float Clamp(float value, float min, float max) {
		if (value < min)
			value = min;
		else if (value > max)
			value = max;
		return value;
	}
	static inline float PingPong(float t, float length) {
		t = Repeat(t, length * 2.0F);
		return length - std::abs(t - length);
	}
	static inline float Repeat(float t, float length) {
		return Clamp(t - floor(t / length) * length, 0.0f, length);
	}

	static inline float SmoothStep(float from, float to, float t)
	{
		t = Clamp01(t);
		t = -2.0F * t * t * t + 3.0f * t * t;
		return to * t + from * (1.0f- t);
	}
};