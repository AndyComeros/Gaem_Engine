#pragma once
#include<glad/glad.h>
#include<iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader{
public:
	Shader();
	Shader(const char* vertShader, const char* fragShader, const char* geomShader);
	~Shader();
	Shader(const Shader& rhs);

	void Use();

	//uniform modifiers:
	void setUniform(const std::string &uName, float uValue);
	void setUniform(const std::string& uName, float v1, float v2);
	void setUniform(const std::string& uName, glm::vec2 uValue);
	void setUniform(const std::string &uName, float v1, float v2, float v3);
	void setUniform(const std::string &uName, glm::vec3 uValue);
	void setUniform(const std::string &uName, float v1, float v2, float v3, float v4);
	void setUniform(const std::string &uName, glm::vec4 uValue);
	void setUniform(const std::string &uName, int uValue);
	void setUniform(const std::string &uName, bool uValue);
	void setUniform(const std::string &uName, glm::mat4 &uValue);

	
private:

	unsigned int createVertexShader(const char* filePath);
	unsigned int createFragmentShader(const char* filePath);
	unsigned int createGeometryShader(const char* filePath);

	std::string readFile(const char* fileName);
	unsigned int ID;
};