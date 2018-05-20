#pragma once
#include <memory>
#include "ITaskExecuter.h"

class TaskExecuter : 
	public std::enable_shared_from_this<TaskExecuter>,
	public ITaskExecuter 
{
public:
	TaskExecuter() = default;
	~TaskExecuter() = default;
public:
	void Init() override;
	void Start() override;
	void Stop() override;
	void SetPixelCallback(std::function<void(int,int,double,double,double)> callback) override;
	void SetLogCallback(std::function<void(const std::string&)> callback) override;
	void SetEndCallback(std::function<void()> callback) override;
	void SetCameraParam(double pox_x, double pox_y, double pox_z,
		double up_x, double up_y, double up_z,
		double target_x, double target_y, double target_z,
		int angle) override;
	void SetGloablParam(double width, double height, int sample) override;
	void SetSettingFile(const char* file) override;
	void SetModuleFile(const char* file) override;
	void SetType(bool model_type) override;
public:
	static std::shared_ptr<TaskExecuter> task_executer_;
};