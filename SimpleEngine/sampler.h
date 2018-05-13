#ifndef SAMPLE_H_
#define SAMPLE_H_
#include <string>

class Sample{
public:
	Sample():x(0.0),y(0.0) {}
	Sample(float x, float y){
		this->x = x;
		this->y = y;
	}
public:
	float x, y;
};


class Sampler
{
public:
	Sampler(int width,int height)
	{
		this->w = width;
		this->h = height;
	}
	~Sampler();
	bool getSample(Sample& sample);
	bool getThreadSample(int thread_id,Sample& sample);
	void getExecPercent();
public:
	int h, w;
	static thread_local int index;
	static thread_local float last_percent_;
};

#endif