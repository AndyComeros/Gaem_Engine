#include "Renderer.h"

Renderer::Renderer() {

	//check if glfw/opengl is setup is setup

	//set gl settings and viewport

	//settup main shader
	
	
}

Renderer::~Renderer() {

}

void Renderer::DrawScene(Scene& scene) {

	for (auto obj : scene.gameObjects) {
		
		
		//setlight uniforms

		//draw object
		obj.model_data->render(scene.camera,mainShader,true,GL_TRIANGLES);
		
		//draw skybox
	}

}

void Renderer::Init(GLFWwindow* window) {

	mainShader = Shader("resources/shaders/Default.vert", "resources/shaders/Default.frag", nullptr);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_MULTISAMPLE);

	int	wWidth, wHeight;
	glfwGetWindowSize(window, &wWidth, &wHeight);
	glViewport(0, 0, wWidth, wHeight);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Resize() {

}