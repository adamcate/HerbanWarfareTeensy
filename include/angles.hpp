#ifndef ANGLES_H
#define ANGLES_H

#include <Arduino.h>

#define MOD_U(a,n) fmodf(fmod(a,n)+n,n)

inline float angleDiff(float angleInitial, float angleFinal)
{
	float a = angleFinal - angleInitial;
	a = MOD_U(a + 180.f, 360.f) - 180.f;
	return a;
}

inline float getAngle(float x, float y) 
{
	float angle = atan2f(y,x) * RAD_TO_DEG;
	if (angle >= 0.f) return angle;
	return 360.f + angle;
}

#endif