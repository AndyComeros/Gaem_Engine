#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "glm/gtx/hash.hpp"
#include <iostream>
#include <fstream>
#include <unordered_map>
	/**
	*	@struct vertex
	*	@brief stores vertex data from an obj file
	*/
struct vertex {
	glm::vec3 vertex;
	glm::vec3 normal;
	glm::vec2 texCoord;

};
	/**
	*	@struct OBJData
	*	@brief stores all obj data
	*/
struct OBJData
{
	std::vector<unsigned int> elements;
	std::vector<vertex> vertexData;
};
	/*
	*	@brief reads an OBJ file and retuns its vertex data in an OBJData struct
	*/
OBJData* ReadObjFile(const char* fileName);