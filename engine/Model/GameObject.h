#pragma once
#include <Graphics/Graphics.h>
#include <Model.h>
#include <Rigidbody.h>


class GameObject
{
public:
	GameObject();
	~GameObject();

	void SetPosition(glm::vec3 nPos);
	void SetRotation(glm::vec3 nRot);

	glm::vec3 position = {0,0,0};
	glm::vec3 scale =	{1,1,1};
	glm::vec3 rotation = {0,0,0};

	Model *model_data = nullptr;
	Rigidbody rigidBody;
	Shader* shader = nullptr;

	std::string name;

	int GetID() { return ID; }
  
	void SetID(int id) { ID = id; };
private:
	unsigned int ID = 0;
};
