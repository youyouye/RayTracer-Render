#include "sampler.h"
#include "Log.h"

thread_local int Sampler::index = 0;
thread_local float Sampler::last_percent_ = 0;

Sampler::~Sampler()
{
}
bool Sampler::getSample(Sample& sample){
	if (index>=(h+1)*(w+1))
	{
		return false;
	}
	sample = Sample(index%(w+1),index/(w+1));
	index++;
	return true;
}

bool Sampler::getThreadSample(int thread_id, Sample& sample)
{
	if (index == 0)
	{
		index = ((float)thread_id/6)*(w + 1)*(h + 1);
	}
	if (index >= ((float)(thread_id+1)/6)*(h+1)*(w+1))
	{
		return false;
	}
	sample = Sample(index%(w+1),index/(w+1));
	index++;
	return true;
}

void Sampler::getExecPercent()
{
	float percent = ((float)index/ (float)((h + 1)*(w + 1)) )*100;
	if (percent - last_percent_ >= 5)
	{
		LOG_INFO <<"percent:"<< std::to_string(percent) + "%" << LOG_END;
		last_percent_ = percent;
	}
}
