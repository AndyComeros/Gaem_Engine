#pragma once
#include <Scene.h>
#include <Graphics/Graphics.h>

class Renderer
{
public:
	Renderer();
	~Renderer();

	void Init();
	void Resize();

	void DrawScene(Scene& scene);

private:
	Shader mainShader;
};