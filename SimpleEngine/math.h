#ifndef MATH_H_
#define MATH_H_

#include <cmath>

const float floatEpsilon = 0.001;
const float PI = 3.1415926535;
const float TWO_PI = 6.2831853071;
const float invPI = 0.3183098861;
const float invTWO_PI = 0.1591549430;
const float MAXNUMBER = 1.0E10;
const float MINNUMBER = 0.0001;
const double 	kEpsilon = 0.0001;
const double	kHugeValue = 1.0E10;
static inline bool
floatEqual(float a,float b){
	return fabsf(a - b) <= floatEpsilon;
}
static inline float clamp(float x,float min,float max){
	return ( x < min ? min : ( x > max ? max : x));
}

#endif