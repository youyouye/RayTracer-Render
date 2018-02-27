#include "small_test.h"
#include "BBox.h"
#include "Ray.h"
#include "Log.h"
#include <iostream>

void SmallTest::testBBox()
{
	BBox bbox(Vector3(-4, -4, -4), Vector3(4, 4, 4));
	Ray ray;
	ray.pos = Point(5, 5, 5);
	ray.dir = Vector3(0, 0, 0);

	bool hit = bbox.hit(ray);
	LOG_DEBUG << (hit ? "right" : "error") << LOG_END;

	BBox bbox2(Vector3(-4, -4, -4),Vector3(4,4,4));
	Ray ray2;
	ray2.pos = Point(0,0,0);
	ray2.dir = Point(0.1,0.1,0.1);
	hit = bbox2.hit(ray2);
	LOG_DEBUG << (hit ? "right" : "error") << LOG_END;
}