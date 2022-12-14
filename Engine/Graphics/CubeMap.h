#pragma once
#include "VAO.h"
#include "Texture.h"
#include "Camera.h"
#include "Shader.h"
#include <string>
#include <vector>
#include <glm/glm.hpp>
/**
*	@Class CubeMap
*	@brief Stores a cubemap texture
*
*	@author Andres Comeros-Ochtman
*	@version 1.0
*	@date 05/09/2022
*/
class CubeMap {
public:
		/**
		*	@brief default constructor
		*	@details sets defualt values for a generic cubemap setup.
		*	shader files for the cubemap are assumed to be in:
		*		-"shaders/vert_cube_map.vert"
		*		-"shaders/frag_cube_map.frag"
		*/
	CubeMap();
		/**
		*	@brief draws cubemap texture as skybox.
		*	@details draws a skybox using the cubemap texture from the
		*	cameras POV. Skybox is rendered with maximum depth in the depth buffer
		*	so will always be draw behind other vertecies.
		*	@param camera Camera object to be drawn using
		*/
	void render(Camera* camera);
		/**
		*	@brief Sets all 6 textures for the cubemap
		*	@warning Function expects textures in the following order:
		*	right, left, top, bottom, front, back.
		*	@param nTextures vector containing all 6 filepaths to cubemap textures.
		*/
	void setTextures(std::vector<std::string> nTextures);
		///Shader used to render cubemap
	Shader shader;
private:
		///Cubemap VAO
	VAO vao;
		///ID for cubemap texure
	unsigned int ID;
		///Texture details
	int width, height, numColorChannels;

};

static float cubeMapVertices[] = {         
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f
};