#pragma once
#include <functional>
#include <string>
#include <memory>

class ITaskExecuter 
{
public:
	virtual ~ITaskExecuter() = default;
public:
	virtual void Init() {}
	virtual void Start() {}
	virtual void Stop() {}
	virtual void SetPixelCallback(std::function<void(int, int, double,double,double)> callback) {}
	virtual void SetLogCallback(std::function<void(const char*, size_t)> callback) {}
	virtual void SetEndCallback(std::function<void()> callback) {}
	virtual void SetType(bool model_type) {}
	virtual void SetCameraParam(double pox_x, double pox_y, double pox_z,
		double up_x, double up_y, double up_z,
		double target_x, double target_y, double target_z,
		int angle) {}
	virtual void SetGloablParam(double width, double height, int sample) {}
	virtual void SetSettingFile(const char* file) {}
	virtual void SetModuleFile(const char* file) {}
};

__declspec(dllexport) std::shared_ptr<ITaskExecuter> GetTaskExecuter();
