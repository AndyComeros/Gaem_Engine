#pragma once
#include <vector>
#include <Graphics/Graphics.h>

struct Material {
	std::vector<Texture*> diffuseTexture;
	std::vector<Texture*> specularMap;
	std::vector<Texture*> emissionMap;
	std::vector<Texture*> normalMap;

	float shine = 1;
};