#include "Utils.h"

float Utils::RandomFloatInRange(float Range)
{
	float Value = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	Value -= 0.5;
	Value *= 2*Range;

	return Value;
}
