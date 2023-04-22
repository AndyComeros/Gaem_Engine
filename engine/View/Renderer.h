#pragma once
#include <Scene.h>
#include <Graphics/Graphics.h>
/**
*	@Class Renderer
*	@brief Used to draw scene to the screen
*
*	@author Andres Comeros-Ochtman
*	@version 1.0
*	@date 15/04/2023
*/
class Renderer
{
public:
		/**
		*	@brief default constructor
		*/
	Renderer();

		/**
		*	@brief destructor
		*/
	~Renderer();

		/**
		*	@brief initalize OpenGL
		*	@param window window being drawn
		*	@return void
		*/
	void Init(GLFWwindow* window);

		/**
		*	@brief Draw the scene
		*	@param scene scene to be drawn
		*	@return void
		*/
	void Draw(Scene& scene);

		/**
		*	@brief Set uniforms for All lights in a scene
		*	@param sLights lights to set uniforms for
		*	@param sShader shader to set uniforms for
		*	@return void
		*/
	static void SetLightUniforms(Lights& sLights,Shader& sShader);

		/**
		*	@brief Set uniforms for all  point lights in a scene
		*	@param sLights lights to set uniforms for
		*	@param sShader shader to set uniforms for
		*	@return void
		*/
	static void SetPointLightUniforms(Lights& sLights, Shader& sShader);

		/**
		*	@brief Set uniforms for all direction lights in a scene
		*	@param sLights lights to set uniforms for
		*	@param sShader shader to set uniforms for
		*	@return void
		*/
	static void SetDirectionLightUniforms(Lights& sLights, Shader& sShader);

		/**
		*	@brief Set uniforms for all spot lights in a scene
		*	@param sLights lights to set uniforms for
		*	@param sShader shader to set uniforms for
		*	@return void
		*/
	static void SetSpotLightUniforms(Lights& sLights, Shader& sShader);

		/**
		*	@brief Returns the default shader
		*	@return void
		*/
	Shader& GetShader();


	void ToggleWireFrame();
private:

	///Whether to draw in wireframe mode or not
	bool wireFrame = false;
		///main window
	GLFWwindow* mainWindow;
		///default shader
	Shader mainShader;

};