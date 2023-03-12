#include "Renderer.h"

Renderer::Renderer() {
	//settup main shader
	mainShader = Shader("resources/shaders/Default.vert", "resources/shaders/Default.frag", nullptr);
	
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