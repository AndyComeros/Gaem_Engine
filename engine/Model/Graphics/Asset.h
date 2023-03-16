#pragma once
#include <string>
#include "Model3D.h"
#include "Texture.h"
#include "Shader.h"
#include <glm/glm.hpp>

struct Asset
{
	std::string id;
	std::string name;

	Model3D* model = nullptr;

	Texture* Diffuse = nullptr;
	Texture* Emission = nullptr;

	Shader* Shader = nullptr;
};