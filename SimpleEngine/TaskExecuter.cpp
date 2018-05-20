#include "TaskExecuter.h"
#include "FreeImage.h"
#include "scene.h"
#include "variables.h"

std::shared_ptr<TaskExecuter> TaskExecuter::task_executer_ = nullptr;
std::shared_ptr<ITaskExecuter> GetTaskExecuter()
{
	if (TaskExecuter::task_executer_ == nullptr)
	{
		TaskExecuter::task_executer_ = std::make_shared<TaskExecuter>();
	}
	return TaskExecuter::task_executer_;
}

void TaskExecuter::Init()
{
	FreeImage_Initialise();
}

void TaskExecuter::Start()
{
	Scene::thread_render(128);
}

void TaskExecuter::Stop()
{
}

void TaskExecuter::SetPixelCallback(std::function<void(int,int,double,double,double)> callback)
{
	Scene::SetPixmapCallback(callback);
}

void TaskExecuter::SetLogCallback(std::function<void(const std::string&)> callback)
{
	log_callback_ = callback;
}

void TaskExecuter::SetEndCallback(std::function<void()> callback)
{
	end_callback_ = callback;
}

void TaskExecuter::SetCameraParam(double pox_x, double pox_y, double pox_z,
	double up_x, double up_y, double up_z,
	double target_x, double target_y, double target_z,
	int angle) 
{
	Scene::SetCameraParam(pox_x, pox_y, pox_z, up_x, up_y, up_z,
		target_x, target_y, target_z, angle);
}

void TaskExecuter::SetGloablParam(double width, double height, int sample)
{
	Scene::SetGloablParam(width, height, sample);
}

void TaskExecuter::SetSettingFile(const char* file)
{
	Scene::SetSettingFile(file);
}

void TaskExecuter::SetModuleFile(const char* file)
{
	Scene::SetModuleFile(file);
}

void TaskExecuter::SetType(bool model_type)
{
	Scene::SetType(model_type);
}