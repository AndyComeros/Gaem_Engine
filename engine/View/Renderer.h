#pragma once
#include "../Model/Scene.h"
#include "../Model/Graphics/Graphics.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void Init(GLFWwindow* window);
	void Resize(GLFWwindow* window, int w, int h);

	void Draw(Scene& scene);

private:
	Shader mainShader;
};