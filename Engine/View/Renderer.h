#pragma once
#include <Scene.h>
#include <Graphics/Graphics.h>

class Renderer
{
public:
	Renderer();
	~Renderer();

	void Init(GLFWwindow* window);
	void Resize();

	void Draw(Scene& scene);

private:
	Shader mainShader;
};