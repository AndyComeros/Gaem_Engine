#pragma once
#include <Scene.h>
#include <Graphics/Graphics.h>

class Renderer
{
public:
	Renderer();
	~Renderer();

	void Init(GLFWwindow* window);
	void Resize(GLFWwindow* window, int w, int h);

	void Draw(Scene& scene);

	void SetLightUniforms(Lights& sLights);

	void SetPointLightUniforms(Lights& sLights);
	void SetDirectionLightUniforms(Lights& sLights);
	void SetSpotLightUniforms(Lights& sLights);

private:
	Shader mainShader;
};