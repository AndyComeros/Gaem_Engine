#pragma once
#include <Scene.h>
#include <Graphics/Graphics.h>

class Renderer
{
public:
	
	Renderer();
	~Renderer();
	void Init(GLFWwindow* window);

	void Draw(Scene& scene);

	static void SetLightUniforms(Lights& sLights,Shader& sShader);
	static void SetPointLightUniforms(Lights& sLights, Shader& sShader);
	static void SetDirectionLightUniforms(Lights& sLights, Shader& sShader);
	static void SetSpotLightUniforms(Lights& sLights, Shader& sShader);

	Shader& GetShader();

	bool wireFrame = false;
private:
	GLFWwindow* mainWindow;
	Shader mainShader;

};