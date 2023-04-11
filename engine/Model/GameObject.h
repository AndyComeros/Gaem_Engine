#pragma once
#include <Graphics/Graphics.h>
#include <Model.h>

class GameObject
{
public:
	GameObject();
	~GameObject();

	glm::vec3 position = {0,0,0};
	glm::vec3 scale =	{1,1,1};
	glm::vec3 rotation = {0,0,0};

	Model* model_data = nullptr;
	Shader* shader = nullptr;
	std::string name;

	int GetID() { return ID; }
	void SetID(int id) { ID = id; };
private:

	unsigned int ID = -1;
	
};
