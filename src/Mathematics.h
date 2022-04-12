//PULLED FROM https://github.com/coelacant1/ProtoTracer
#pragma once
#include <math.h>
#include <Arduino.h>

class Mathematics {
public:
	static const float EPSILON;
	static const float MPI;
	static const float MPID180;
	static const float M180DPI;

	static uint32_t Constrain(uint32_t value, uint32_t minimum, uint32_t maximum);
	static unsigned int Constrain(unsigned int value, unsigned int minimum, unsigned int maximum);
	static float Constrain(float value, float minimum, float maximum);
	static float DegreesToRadians(float degrees);
	static float RadiansToDegrees(float radians);
	static String DoubleToCleanString(float value);
	static bool IsNaN(float);
	static bool IsInfinite(float);
	static bool IsFinite(float);
	static bool IsClose(float, float, float);
	static int Sign(float);
	static int RoundUpWindow(int value, int multiple);
	static float Map(float value, float inLow, float inMax, float outMin, float outMax);
	static float Pow(float value, float exponent);
	static float Sqrt(float value);
	static float Fract(float value);

	static float CosineInterpolation(float, float, float);
	static float BounceInterpolation(float, float, float);
};
