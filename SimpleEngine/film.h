#ifndef FILM_H_
#define FILM_H_
#include "sampler.h"
#include "color.h"
#include "variables.h"
#include <mutex>

class Film{
public:
	Film(int w, int h){
		this->width = w;
		this->height = h;
		pixels = new unsigned int[(height+1)*(width+1)];
	}
	~Film(){
		delete []pixels;
	}
	void commit(Sample& sample, Color& color);
	void writeImage();
	void SetCommitCallback(std::function<void(int, int, double,double,double)> callback);
public:
	int height, width;
	unsigned int* pixels;
	std::mutex mutex_;
	std::function<void(int,int,double,double,double)> pixel_callback_;
};


#endif