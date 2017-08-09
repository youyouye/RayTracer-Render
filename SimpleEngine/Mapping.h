#ifndef MAPPING_H_
#define MAPPING_H_
#include "vector.h"
class Mapping
{
public:
	Mapping();
	~Mapping();
	virtual void getPixelCoordinates(
		const Vector3& local_hit_point,
		const int hres,
		const int vres,
		int& row,
		int& column
		)const = 0;
};

#endif