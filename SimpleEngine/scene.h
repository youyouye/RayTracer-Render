#ifndef SCENE_H_
#define SCENE_H_
#include "RayTracer.h"
#include "camera.h"

class Scene{
public:
	static void render(int samples = 1);
	static void readUserDefinedFile(RayTracer& raytrace, Camera& camera);
	template<typename T>
	static void addObject(RayTracer& raytrace,T& object)
	{
		auto primitives = object.getPrimitives();
		auto lights = object.getLights();
		raytrace.primitives.insert(std::end(raytrace.primitives), std::begin(primitives), std::end(primitives));
		raytrace.lights.insert(std::end(raytrace.lights), std::begin(lights), std::end(lights));
	}
	static void addSingleObject(RayTracer& raytrace, std::shared_ptr<Primitive> primitive);
	static void testObjectModel(RayTracer& raytrace, Camera& camera);
};

#endif