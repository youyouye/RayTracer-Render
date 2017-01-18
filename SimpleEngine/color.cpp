#include"color.h"
Color::Color(float red, float green, float blue, float alpha){
	r = red;
	g = green;
	b = blue;
	a = alpha;
}
uint32_t Color::uint32() const
{
	
	uint32_t R = (uint32_t)(r );
	uint32_t G = (uint32_t)(g );
	uint32_t B = (uint32_t)(b );
	uint32_t A = (uint32_t)(a );
	uint32_t value = (A << 24) | (R << 16) | (G << 8) | B;
	return value;
}
