#include"Camera.h"
#include <iostream>


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

	Yaw = 90.0f;
	Pitch = 0.0f;
	MovementSpeed = 100.0f;
	MouseSensitivity = 0.1f;
	Distance = 20.0f;
	updateCameraVectors();
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

	Yaw = 90.0f;
	Pitch = 0.0f;
	MovementSpeed = 100.0f;
	MouseSensitivity = 0.1f;
	Distance = 20.0f;
	updateCameraVectors();
}

void Camera::LookAt(glm::vec3 lookPos) {
	 front = glm::normalize(lookPos - position);
}

glm::mat4 Camera::GetView() 
{
	return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::GetProjection() {

	glm::mat4 projection = glm::perspective(glm::radians(FOV), aspectRatio, nearPlane, farPlane);
	return projection;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, glm::vec3 playerPos, bool constrainPitch)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw -= xoffset;

	Pitch -= yoffset;
	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (Pitch < -89.0f)
			Pitch = -89.0f;
		if (Pitch > 0.0f)
			Pitch = 0.0f;
	}

	
	//thirdperson
	CalaulateCamPos(playerPos);

	// update Front, Right and Up Vectors using the updated Euler angles
	updateCameraVectors();
}

void Camera::CalaulateCamPos(glm::vec3 playerPos)
{
	//third person camera
	float yaw = Yaw - 90.0f;
	float pitch = -Pitch;
	float x = Distance * cos(glm::radians(pitch)) * sin(glm::radians(-yaw));
	float y = Distance * sin(glm::radians(pitch));
	float z = Distance * cos(glm::radians(pitch)) * cos(glm::radians(yaw));

	position = playerPos + glm::vec3(-x, y, -z);
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = MovementSpeed * deltaTime;
	if (direction == FORWARD)
		position += front * velocity;
	if (direction == BACKWARD)
		position -= front * velocity;
	if (direction == LEFT)
		position -= right * velocity;
	if (direction == RIGHT)
		position += right * velocity;
}

void Camera::updateCameraVectors()
{
	// calculate the new Front vector
	glm::vec3 Front;
	Front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front.y = sin(glm::radians(Pitch));
	Front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front = glm::normalize(Front);
	// also re-calculate the Right and Up vector
	right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	up = glm::normalize(glm::cross(right, front));
}