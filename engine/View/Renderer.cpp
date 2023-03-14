#include "Renderer.h"

Renderer::Renderer() {

	//check if glfw/opengl is setup is setup

	//set gl settings and viewport

	//settup main shader	
}

Renderer::~Renderer() {

}

//may want to make several "draw queues" to seperate shaders and opacity
void Renderer::Draw(Scene& scene) {

	//draw skybox
	scene.skybox->render(&scene.camera);

	mainShader.setUniform("cameraPos", &scene.camera);

	for (auto obj : scene.gameObjects) {

		//set model matrix uniforms
		glm::mat4 modelMat(1.0f);
		modelMat = glm::translate(modelMat, obj.position);
		modelMat = glm::scale(modelMat, obj.scale);

		//x y z rotationss
		modelMat = glm::rotate(modelMat, glm::radians(obj.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		modelMat = glm::rotate(modelMat, glm::radians(obj.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		modelMat = glm::rotate(modelMat, glm::radians(obj.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));

		mainShader.setUniform("model", modelMat);

		if (obj.shader) {
			obj.model_data->render(&scene.camera,obj.shader, true, GL_TRIANGLES);
		}
		else {
			obj.model_data->render(&scene.camera, &mainShader, true, GL_TRIANGLES);
		}
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