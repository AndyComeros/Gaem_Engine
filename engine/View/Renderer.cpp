#include "Renderer.h"

Renderer::Renderer() {}

Renderer::~Renderer() {}

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

void Renderer::Resize(GLFWwindow* window, int w, int h) {
	glViewport(0, 0, w, h);

}

//may want to make several "draw queues" to seperate shaders and opacity
void Renderer::Draw(Scene& scene) {

	//set appropriate uniforms.

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

	//draw skybox
	scene.skybox->render(&scene.camera);
}

void Renderer::SetLightUniforms(Lights& sLights) {

	mainShader.setUniform("ambient_Light", sLights.ambientLight);

	SetPointLightUniforms(sLights);
	SetDirectionLightUniforms(sLights);
	SetPointLightUniforms(sLights);

}

void Renderer::SetPointLightUniforms(Lights& sLights) {

	mainShader.setUniform("numPointLights", (int)sLights.pointLights.size());

	for (int i = 0; i < (int)sLights.pointLights.size(); i++)
	{
		char buffer[32];

		sprintf_s(buffer, "pointLights[%i].position", i);
		mainShader.setUniform(buffer, sLights.pointLights[i].position);

		sprintf_s(buffer, "pointLights[%i].diffuse", i);
		mainShader.setUniform(buffer, sLights.pointLights[i].diffuse);

		sprintf_s(buffer, "pointLights[%i].specular", i);
		mainShader.setUniform(buffer, sLights.pointLights[i].specular);

		sprintf_s(buffer, "pointLights[%i].constant", i);
		mainShader.setUniform(buffer, sLights.pointLights[i].constant);

		sprintf_s(buffer, "pointLights[%i].linear", i);
		mainShader.setUniform(buffer, sLights.pointLights[i].linear);

		sprintf_s(buffer, "pointLights[%i].quadratic", i);
		mainShader.setUniform(buffer, sLights.pointLights[i].quadratic);
	}

}

void Renderer::SetDirectionLightUniforms(Lights& sLights) {


	mainShader.setUniform("numDirectionLights", (int)sLights.directionLights.size());

	for (int i = 0; i < sLights.directionLights.size(); i++)
	{
		char buffer[32];

		sprintf_s(buffer, "directionLights[%i].direction", i);
		mainShader.setUniform(buffer, sLights.directionLights[i].direction);

		sprintf_s(buffer, "directionLights[%i].diffuse", i);
		mainShader.setUniform(buffer, sLights.directionLights[i].diffuse);

		sprintf_s(buffer, "directionLights[%i].specular", i);
		mainShader.setUniform(buffer, sLights.directionLights[i].specular);
	}
}

void Renderer::SetSpotLightUniforms(Lights& sLights) {

	mainShader.setUniform("numSpotLights", (int)sLights.spotLights.size());

	for (int i = 0; i < sLights.spotLights.size(); i++)
	{
		char buffer[32];

		sprintf_s(buffer, "spotLights[%i].position", i);
		mainShader.setUniform(buffer, sLights.spotLights[i].position);

		sprintf_s(buffer, "spotLights[%i].direction", i);
		mainShader.setUniform(buffer, sLights.spotLights[i].direction);

		sprintf_s(buffer, "spotLights[%i].maxAngle", i);
		mainShader.setUniform(buffer, sLights.spotLights[i].maxAngle);

		sprintf_s(buffer, "spotLights[%i].featherAngle", i);
		mainShader.setUniform(buffer, sLights.spotLights[i].featherAngle);

		sprintf_s(buffer, "spotLights[%i].diffuse", i);
		mainShader.setUniform(buffer, sLights.spotLights[i].diffuse);

		sprintf_s(buffer, "spotLights[%i].specular", i);
		mainShader.setUniform(buffer, sLights.spotLights[i].specular);

		sprintf_s(buffer, "spotLights[%i].constant", i);
		mainShader.setUniform(buffer, sLights.spotLights[i].constant);

		sprintf_s(buffer, "spotLights[%i].linear", i);
		mainShader.setUniform(buffer, sLights.spotLights[i].linear);

		sprintf_s(buffer, "spotLights[%i].quadratic", i);
		mainShader.setUniform(buffer, sLights.spotLights[i].quadratic);
	}
}

