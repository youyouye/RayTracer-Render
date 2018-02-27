#include "sampler.h"

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

std::string Sampler::getExecPercent()
{
	float percent = ((float)index/ (float)((h + 1)*(w + 1)) )*100;
	return std::to_string(percent) + "%";
}
