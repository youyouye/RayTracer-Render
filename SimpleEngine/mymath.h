#ifndef MATH_H_
#define MATH_H_

#include <cmath>

const float floatEpsilon = 0.001;
const float PI = 3.1415926535;

static inline bool
floatEqual(float a,float b){
	return fabsf(a - b) <= floatEpsilon;
}


#endif