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
	Sampler(int width,int height):index(0) {
		this->w = width;
		this->h = height;
	}
	~Sampler();
	bool getSample(Sample& sample);
	std::string getExecPercent();
public:
	int h, w;
	int index;
};

#endif