#ifndef SPHEREICALMAP_H_
#define SPHEREICALMAP_H_
#include "Mapping.h"
class SphericalMap : public Mapping
{
public:
	SphericalMap();
	~SphericalMap();
	virtual void getPixelCoordinates(
		const Vector3& local_hit_point,
		const int hres,
		const int vres,
		int& row,
		int& column
		)const;
};

#endif