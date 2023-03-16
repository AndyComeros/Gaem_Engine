#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


/**
*	@Class Camera
*	@brief Stores all view and projection matrix data	
*	
*	@author Andres Comeros-Ochtman
*	@version 1.0
*	@date 05/09/2022
*/
class Camera {
public:
		/**
		*	@brief default constructor
		*	@details sets defualt values for a generic camera setup
		*/
	Camera();
		/**
		*	@brief default constructor with user defined values
		*	@param nFOV initial field of view in degrees
		*	@param nAspect inital aspect ratio, calculate using screen width/height
		*	@param nNear minumum distance faces are not clipped from view
		*	@param nNear maximum distance faces are clipped from view
		*/
	Camera(float nFOV,float nAspect, float nNear, float nFar);
		/**
		*	@brief changes front vec to look at a positon
		*	@return void
		*/
	void SetFrontVec(glm::vec3 lookPos);
		/**
		*	@brief returns view matrix
		*	@details returns a view matrix based on cameras position and orentation in space.
		*	used by opengl to deform vertecies in the vertex shader.
		*	@return Cameras view Matrix
		*/
	glm::mat4 GetViewMatrix();
		/**
		*	@brief returns a projection matrix
		*	@details returns a projection matrix based on cameras clipping planes, aspect ratio and FOV.
		*	used by opengl to deform vertecies in the vertex shader to simulate perspective.
		*	@return Cameras Projection Matrix
		*/
	glm::mat4 GetProjectionMatrix();

	glm::vec3 position;
	glm::vec3 rotation;

	glm::vec3 frontVec;	//lookat target
	glm::vec3 rightVec;
	glm::vec3 upVec;

	float FOV;
	float aspectRatio;
	float nearPlane;
	float farPlane;
private:
	bool isLook = false;

};