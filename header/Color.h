#pragma once

struct Color {
	float r = 0, g = 0, b = 0, a = 1.0f;

	Color operator+(const Color& c) const;
	Color operator-(const Color& c) const;
	Color operator*(const Color& c) const;

	Color operator*(const float& w) const;
	Color operator/(const float& w) const;
};

Color lerp(const Color& c1, const Color& c2, const int& w);