#pragma once
#include "Graphics/Graphics.h"
#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>

class GameObject
{
public:
	GameObject();
	~GameObject();

	glm::vec3 position = {0,0,0};
	glm::vec3 scale =	{0,0,0};
	glm::vec3 rotation = {0,0,0};


	Model3D* model_data = nullptr;
	Shader* shader = nullptr;
private:

	unsigned int ID;
};
