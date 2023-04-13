#pragma once
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

class GUIRenderer
{
public:
	GUIRenderer() : window(nullptr){}
	~GUIRenderer() {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
	
	void Init(GLFWwindow* nwindow) {

		window = nwindow;

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		ImGui::StyleColorsDark();

		ImGui_ImplGlfw_InitForOpenGL(window,true);
		ImGui_ImplOpenGL3_Init("#version 330");
	
	}

	void Draw() {
	
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		
		ImGui::Begin("My Window");
		ImGui::Text("Hello World!");
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}


private:
	GLFWwindow* window;
};