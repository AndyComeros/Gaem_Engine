#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <Graphics/Texture.h>

	/**
	*	@struct PontLight
	*	@brief Point light data
	*	@details Point lights effect attenuates with distance
	*	uniformly in all directions.
	*/
struct PointLight {
	glm::vec3 position;
	glm::vec3 diffuse;
	glm::vec3 specular;

	//attenuation values
	float constant;
	float linear;
	float quadratic;
};
	/**
	*	@struct SpotLight
	*	@brief SpotLight light data
	*	@details Spot lights point in a  direction accross
	*	maxAngle degrees and attenuate in affect in that direction.
	*/
struct SpotLight {
	glm::vec3 position;
	glm::vec3 direction;
	float maxAngle;
	float featherAngle;

	glm::vec3 diffuse;
	glm::vec3 specular;

	//attenuation values
	float constant;
	float linear;
	float quadratic;
};

	/**
	*	@struct DirectionLight
	*	@brief light poining on all surfaces uniformly from a specified direction
	*	@details Simulates light from infinite distance away pointing in a specified vector.
	*/
struct DirectionLight {
	glm::vec3 direction;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

	/**
	*	@struct Lights
	*	@brief Collection of lights for a scene
	*	@details stores all lights a scene may use
	*/
struct Lights {
	glm::vec3 ambientLight = {1,1,1};
	std::vector<PointLight> pointLights;
	std::vector<SpotLight> spotLights;
	std::vector<DirectionLight> directionLights;
};

struct Material {
	std::vector<Texture*> diffuseTexture;
	std::vector<Texture*> specularMap;
	std::vector<Texture*> emissionMap;
	std::vector<Texture*> normalMap;

	float shine = 1.0f;
};
