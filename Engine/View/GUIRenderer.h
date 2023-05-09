#pragma once
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <Graphics/Graphics.h>
#include <ResourceManager.h>
#include <Renderer.h>
#include <map>
#include <string>
/**
*	@Class GUIRenderer
*	@brief Used to draw gui elements to the screen
*
*	@author Andres Comeros-Ochtman
*	@version 1.0
*	@date 15/04/2023
*/
class GUIRenderer
{
public:
		/**
		*	@brief default constructor
		*/
	GUIRenderer();

		/**
		*	@brief destructor
		*/
	~GUIRenderer();

		/**
		*	@brief initalize gui
		*	@param nwindow window being rendered to
		*	@return void
		*/
	void Init(GLFWwindow* nwindow);

		/**
		*	@brief Draw current GUI to the screen
		*	@return void
		*/
	void Draw();

		/**
		*	@brief Switch the current GUI
		*	@param nGUI GUI being switched to
		*	@return void
		*/
	void SwitchMenu(int nGUI);

private:

		///Draw generic main menu
	void GUI_Main();
		///Draw generic settings menu
	void GUI_Settings();
		///Draw generic exit menu
	void GUI_Exit();
		///Draw generic main menu
	void GUI_Manual();
		///Draw generic debug menu
	void GUI_Debug();
		///Draw generic in game menu
	void GUI_InGame();

	void TextCenteredOnLine(const char* label, float alignment);

	bool ButtonCenteredOnLine(const char* label, float alignment);

	void AlignForWidth(float width, float alignment);
		
		///Current GUI to be drawn
	int currentGUI = 0;
		
		///imgui settings for windos
	ImGuiWindowFlags flags;
		///window being drawn to
	GLFWwindow* window;
};