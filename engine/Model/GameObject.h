#pragma once
#include <Graphics/Graphics.h>
#include <Model.h>
#include <Rigidbody.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>


class GameObject
{
public:
	GameObject();
	~GameObject();

	void SetPosition(glm::vec3 nPos);
	void SetRotation(glm::vec3 nRot);

	void SetUpVec(glm::vec3 nUp);
	virtual void SetUniforms();


	glm::vec3 GetUpVec();
	glm::vec3 GetForwardVec();
	glm::vec3 GetRightVec();
	


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
