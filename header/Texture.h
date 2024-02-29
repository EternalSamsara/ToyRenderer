#pragma once
#include "Light.h"


struct Texture {
	Texture() = default;
	Texture(const unsigned w, const unsigned h);
	Color getTextureColor(Vertex2f uv);

	unsigned width = 1, height = 1;
	std::vector<Color> content = {};
};

void getTexture(Texture& texture, const std::wstring& path);