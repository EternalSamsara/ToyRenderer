#include "Color.h"


Color Color::operator+(const Color& c) const {
	Color color = { r + c.r, g + c.g, b + c.b, a };
	return color;
}

Color Color::operator-(const Color& c) const {
	Color color = { r - c.r, g - c.g, b - c.b, a };
	return color;
}

Color Color::operator*(const Color& c) const {
	Color color = { r * c.r, g * c.g, b * c.b, a };
	return color;
}

Color Color::operator*(const float& w) const {
	Color color = { r * w, g * w, b * w, a };
	return color;
}

Color Color::operator/(const float& w) const {
	Color color = { r / w, g / w, b / w, a };
	return color;
}

Color lerp(const Color& c1, const Color& c2, const int& w) {
	return c1 + (c2 - c1) * w;
}