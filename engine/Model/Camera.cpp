#include"Camera.h"

Camera::Camera()
{	
	position = glm::vec3(0.0f,0.0f,0.0f);
	rotation = glm::vec3(0.0f,0.0f,0.0f);

	front = glm::vec3(0.0f, 0.0f, 1.0f);
	right = glm::vec3(0.0f, 0.0f, -1.0f);
	up	 = glm::vec3(0.0f, 1.0f, 0.0f);

	FOV = 45.0f;
	aspectRatio =  16.0f / 9.0f;
	nearPlane = 0.1f;
	farPlane = 100.0f;
}

Camera::Camera(float nFOV, float nAspect, float nNear, float nFar)
{
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	rotation = glm::vec3(0.0f, 0.0f, 0.0f);

	front = glm::vec3(0.0f, 0.0f, 3.0f);
	right = glm::vec3(0.0f, 0.0f, -1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);

	FOV = nFOV;
	aspectRatio = nAspect;
	farPlane = nFar;
	nearPlane = nNear;

}

void Camera::LookAt(glm::vec3 lookPos) {
	 front = glm::normalize(lookPos - position);
}

glm::mat4 Camera::GetView() 
{		
	front.x = cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
	front.y = sin(glm::radians(rotation.x));
	front.z = sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front,glm::vec3(0.0f,1.0f,0.0f)));

	up = glm::normalize(glm::cross(right, front));

	return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::GetProjection() {

	glm::mat4 projection = glm::perspective(glm::radians(FOV), aspectRatio, nearPlane, farPlane);
	return projection;
}