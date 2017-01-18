#ifndef COLOR_H_
#define COLOR_H_
#include<cstdint>
class Color{
public:
	Color(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f);
	uint32_t uint32() const;
	Color operator+(const Color &color) const{
		return Color(r + color.r, g + color.g, b + color.b, a + color.a);
	}
	Color operator-(const Color &color) const {
		return Color(r - color.r, g - color.g, b - color.b, a - color.a);
	};

	Color operator*(float factor) const {
		return Color(r * factor, g * factor, b * factor, a * factor);
	};
	Color operator*(const Color &color) const{
		return Color(r*color.r, g*color.g, b*color.b, a*color.a);
	};

	Color interpolate(const Color &c, float factor) const {
		return *this + (c - *this) * factor;
	};
public:
	float r;
	float g;
	float b;
	float a;
};

#endif