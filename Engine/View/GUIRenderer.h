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
		*	@brief free up GUI resources
		*	@return void
		*/
	void Shutdown();

		/**
		*	@brief initalize gui
		*	@param nwindow window being rendered to
		*	@return void
		*/
	void Init(GLFWwindow* nwindow);

		/**
		*	@brief set font to a ttf font
		*	@param path path to font
		*	@return void
		*/
	void SetFont(std::string path);

	//lua programmable GUI//

	void Start(bool background);
	void End();

	void Text(const std::string label, float alignment);
	bool Button(const std::string label, float alignment, float width, float height);
	void Image(const std::string texture, float width, float height, float alignX, float alignY);
	bool ImageButton(const std::string texture, float width, float height, float alignX, float alignY);
	void Tab(float size);
	void SetCursorPosX(float pos);
	void SetCursorPosY(float pos);


private:

	ImGuiIO* io;

	void AlignForWidth(float width, float alignment);
		
		///imgui settings for windos
	ImGuiWindowFlags flags;
		///window being drawn to
	GLFWwindow* window;
};