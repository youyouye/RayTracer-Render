#include "sampler.h"
#include "Log.h"

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

void Sampler::getExecPercent()
{
	float percent = ((float)index/ (float)((h + 1)*(w + 1)) )*100;
	if (percent - last_percent_ >= 1)
	{
		LOG_INFO <<"percent:"<< std::to_string(percent) + "%" << LOG_END;
		last_percent_ = percent;
	}
}
