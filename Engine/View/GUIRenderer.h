#pragma once
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <Graphics/Graphics.h>
#include <ResourceManager.h>
#include <map>
#include <string>


class GUIRenderer
{
public:
	GUIRenderer();
	~GUIRenderer();
	void Init(GLFWwindow* nwindow);
	void Draw();

	void SwitchMenu(int nGUI);

private:

	void GUI_Main();
	void GUI_Settings();
	void GUI_Exit();
	void GUI_Debug();

	int currentGUI = 0;
	ImGuiWindowFlags flags;
	GLFWwindow* window;
};