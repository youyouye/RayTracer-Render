#ifndef SCENE_H_
#define SCENE_H_
#include "RayTracer.h"
#include "camera.h"
#include "film.h"

class Scene{
public:
	static void render(int samples = 1);
	static void thread_render(int samples = 1);
	static void render_task(int n, int samples, Film& film);
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

	static void SetGloablParam(double width, double height, int sample);
	static void SetSettingFile(const std::string& file);
	static void SetModuleFile(const std::string& file);
	static void SetCameraParam(double pox_x, double pox_y, double pox_z,
		double up_x, double up_y, double up_z,
		double target_x, double target_y, double target_z,
		int angle);
	static void SetType(bool model_type);
	static void SetPixmapCallback(const std::function<void(int,int,double,double,double)> callback);
	static std::function<void(int, int, double,double,double)> pixmap_callback_;
};

#endif