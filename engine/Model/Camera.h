#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
public:

	Camera();
	Camera(float nFOV,float nAspect, float nNear, float nFar);
	void LookAt(glm::vec3 lookPos);
	glm::mat4 GetView();
	glm::mat4 GetProjection();

	glm::vec3 position;
	glm::vec3 rotation;

	glm::vec3 front;
	glm::vec3 right;
	glm::vec3 up;

	float FOV;
	float aspectRatio;
	float nearPlane;
	float farPlane;
private:

};