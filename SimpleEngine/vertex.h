#ifndef VERTEX_H_
#define VERTEX_H_
#include "vector.h"
#include "color.h"
class Vertex2{
public:
	Vertex2(const Vector2 &position, const Color &color){
		this->position = position;
		this->color = color;
	}
public:
	Vector2 position;
	Color color;
};

#endif