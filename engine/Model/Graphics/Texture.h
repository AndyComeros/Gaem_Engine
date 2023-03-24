#pragma once
#include <stb_image/stb_image.h>
#include <glad/glad.h>
#include <iostream>
/**
*	@Class Texture
*	@brief Stores Opengl 2D texture data
*
*	@author Andres Comeros-Ochtman
*	@version 1.0
*	@date 05/09/2022
*/
class Texture {
public:
		//read in from file
	Texture(const char *fileName);
	~Texture();
		//read raw image data
	Texture(unsigned char *imgData, int w,int h,int c);
		//bind to one of the approx 16 texture units to be used in rendering
	void Bind(GLuint tUnit);
	
		//get a pixel value at specific coord in texture. index to get r,g,b,a values etc.
	 unsigned char GetPixelValue(int x,int y,int index);

	int GetChannelCount();

	unsigned int ID;
private:
	Texture();
	int width, height, numColorChannels;
	unsigned char* imageData = nullptr;
};