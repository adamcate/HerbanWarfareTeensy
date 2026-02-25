#ifndef ANGLES_H
#define ANGLES_H
#include <Arduino.h>

inline float angleDiff(float angleInitial, float angleFinal)
{
	float stepPositive = angleFinal - angleInitial;
	float stepNegative = angleFinal - angleInitial - 360.f;

	if (fabs(stepPositive) <= fabs(stepNegative)) return stepPositive;

	return stepNegative;
}

inline float angleGet(float x, float y) 
{
	float angle = atan2f(y,x) * 57.3248f;
	if (angle >= 0.f) return angle;
	return 360.f + angle;
}

#endif