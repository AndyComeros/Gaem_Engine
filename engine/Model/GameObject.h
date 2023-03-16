#pragma once
#include "Graphics/Graphics.h"
#include <glm/glm.hpp>
#include <string>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>

class GameObject
{
public:
	GameObject();
	~GameObject();

	glm::vec3 position = {0,0,0};
	glm::vec3 scale =	{1,1,1};
	glm::vec3 rotation = {0,0,0};

	Model3D* model_data = nullptr;
	Shader* shader = nullptr;
	std::string name;

	int GetID() { return ID; }
private:

	unsigned int ID = -1;
	
};
