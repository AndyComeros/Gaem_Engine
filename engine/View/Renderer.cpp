#include "Renderer.h"

Renderer::Renderer() {}

Renderer::~Renderer() {}

void Renderer::Init(GLFWwindow* window) {

	mainWindow = window;
	mainShader = Shader("resources/shaders/Default.vert", "resources/shaders/Default.frag", "");

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_MULTISAMPLE);


	int	wWidth, wHeight;
	glfwGetWindowSize(window, &wWidth, &wHeight);
	glViewport(0, 0, wWidth, wHeight);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

//may want to make several "draw queues" to seperate shaders and opacity
void Renderer::Draw(Scene& scene) {

	//Set render mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (wireFrame)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//Clear Buffers
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//set appropriate uniforms.
	mainShader.SetUniform("wireframe", wireFrame);

	for (auto& it : scene.gameObjects) {

		GameObject* obj = &it.second;
		
		//set special uniforms
		obj->SetUniforms();

		//set model matrix uniforms
		glm::mat4 modelMat(1.0f);
		modelMat = glm::translate(modelMat, obj->position);
		modelMat = glm::scale(modelMat, obj->scale);

		//pitch roll and yaw rotationss
		modelMat = glm::rotate(modelMat, glm::radians(obj->rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

		modelMat = glm::rotate(modelMat, glm::radians(obj->rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		
		modelMat = glm::rotate(modelMat, glm::radians(obj->rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));

		if (obj->shader) {
			obj->shader->SetUniform("model", modelMat);
			obj->model_data->Render(&scene.camera,obj->shader, true, GL_TRIANGLES);
		}
		else {
			mainShader.SetUniform("model", modelMat);
			obj->model_data->Render(&scene.camera, &mainShader, true, GL_TRIANGLES);
		}
	}

	//draw skybox
	if(scene.skybox)
		scene.skybox->Render(&scene.camera);
}

void Renderer::SetLightUniforms(Lights& sLights, Shader& sShader) {

	sShader.SetUniform("ambient_Light", sLights.ambient);

	SetPointLightUniforms(sLights, sShader);
	SetDirectionLightUniforms(sLights, sShader);
	SetPointLightUniforms(sLights, sShader);

}

void Renderer::SetPointLightUniforms(Lights& sLights, Shader& sShader) {

	sShader.SetUniform("numPointLights", (int)sLights.point.size());

	for (int i = 0; i < (int)sLights.point.size(); i++)
	{
		char buffer[32];

		sprintf_s(buffer, "pointLights[%i].position", i);
		sShader.SetUniform(buffer, sLights.point[i].position);

		sprintf_s(buffer, "pointLights[%i].diffuse", i);
		sShader.SetUniform(buffer, sLights.point[i].diffuse);

		sprintf_s(buffer, "pointLights[%i].specular", i);
		sShader.SetUniform(buffer, sLights.point[i].specular);

		sprintf_s(buffer, "pointLights[%i].constant", i);
		sShader.SetUniform(buffer, sLights.point[i].constant);

		sprintf_s(buffer, "pointLights[%i].linear", i);
		sShader.SetUniform(buffer, sLights.point[i].linear);

		sprintf_s(buffer, "pointLights[%i].quadratic", i);
		sShader.SetUniform(buffer, sLights.point[i].quadratic);
	}

}

void Renderer::SetDirectionLightUniforms(Lights& sLights, Shader& sShader) {


	sShader.SetUniform("numDirectionLights", (int)sLights.direction.size());

	for (int i = 0; i < sLights.direction.size(); i++)
	{
		char buffer[32];

		sprintf_s(buffer, "directionLights[%i].direction", i);
		sShader.SetUniform(buffer, sLights.direction[i].direction);

		sprintf_s(buffer, "directionLights[%i].diffuse", i);
		sShader.SetUniform(buffer, sLights.direction[i].diffuse);

		sprintf_s(buffer, "directionLights[%i].specular", i);
		sShader.SetUniform(buffer, sLights.direction[i].specular);
	}
}

void Renderer::SetSpotLightUniforms(Lights& sLights, Shader& sShader) {

	sShader.SetUniform("numSpotLights", (int)sLights.spot.size());

	for (int i = 0; i < sLights.spot.size(); i++)
	{
		char buffer[32];

		sprintf_s(buffer, "spotLights[%i].position", i);
		sShader.SetUniform(buffer, sLights.spot[i].position);

		sprintf_s(buffer, "spotLights[%i].direction", i);
		sShader.SetUniform(buffer, sLights.spot[i].direction);

		sprintf_s(buffer, "spotLights[%i].maxAngle", i);
		sShader.SetUniform(buffer, sLights.spot[i].maxAngle);

		sprintf_s(buffer, "spotLights[%i].featherAngle", i);
		sShader.SetUniform(buffer, sLights.spot[i].featherAngle);

		sprintf_s(buffer, "spotLights[%i].diffuse", i);
		sShader.SetUniform(buffer, sLights.spot[i].diffuse);

		sprintf_s(buffer, "spotLights[%i].specular", i);
		sShader.SetUniform(buffer, sLights.spot[i].specular);

		sprintf_s(buffer, "spotLights[%i].constant", i);
		sShader.SetUniform(buffer, sLights.spot[i].constant);

		sprintf_s(buffer, "spotLights[%i].linear", i);
		sShader.SetUniform(buffer, sLights.spot[i].linear);

		sprintf_s(buffer, "spotLights[%i].quadratic", i);
		sShader.SetUniform(buffer, sLights.spot[i].quadratic);
	}

}

Shader& Renderer::GetShader() {
	return mainShader;
}

