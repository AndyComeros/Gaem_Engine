#include "Camera.h"

Camera::Camera()
{	
	position = glm::vec3(0.0f,0.0f,0.0f);
	rotation = glm::vec3(0.0f,0.0f,0.0f);

	frontVec = glm::vec3(0.0f, 0.0f, 1.0f);
	rightVec = glm::vec3(0.0f, 0.0f, -1.0f);
	upVec	 = glm::vec3(0.0f, 1.0f, 0.0f);

	FOV = 45.0f;
	aspectRatio =  16.0f / 9.0f;
	nearPlane = 0.1f;
	farPlane = 100.0f;
}

Camera::Camera(float nFOV, float nAspect, float nNear, float nFar)
{
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	rotation = glm::vec3(0.0f, 0.0f, 0.0f);

	frontVec = glm::vec3(0.0f, 0.0f, 3.0f);
	rightVec = glm::vec3(0.0f, 0.0f, -1.0f);
	upVec = glm::vec3(0.0f, 1.0f, 0.0f);

	FOV = nFOV;
	aspectRatio = nAspect;
	farPlane = nFar;
	nearPlane = nNear;

}

void Camera::SetFrontVec(glm::vec3 lookPos) {
	frontVec = glm::normalize(lookPos - position);
}

glm::mat4 Camera::GetViewMatrix() 
{	
	if (isLook) {
		return glm::lookAt(position, position + frontVec, upVec);
	}
		
	frontVec.x = cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
	frontVec.y = sin(glm::radians(rotation.x));
	frontVec.z = sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
	frontVec = glm::normalize(frontVec);

	rightVec = glm::normalize(glm::cross(frontVec,glm::vec3(0.0f,1.0f,0.0f)));

	upVec = glm::normalize(glm::cross(rightVec, frontVec));

	return glm::lookAt(position, position + frontVec, upVec);
}

glm::mat4 Camera::GetProjectionMatrix() {

	glm::mat4 projection = glm::perspective(glm::radians(FOV), aspectRatio, nearPlane, farPlane);
	return projection;
}