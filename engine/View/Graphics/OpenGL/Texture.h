#pragma once
#include <stb_image/stb_image.h>
#include <glad/glad.h>
#include <iostream>

class Texture {
public:

	Texture();
	Texture(const char *fileName);
	~Texture();
	Texture(unsigned char *imgData, int w,int h,int c);
	void Bind(GLuint tUnit);
	
	 unsigned char GetPixelValue(int x,int y,int index);

	int GetChannelCount();
	int GetWidth();
	int GetHeight();
  
	unsigned char* GetImageData() {
		return imageData;
	}
  
	std::string GetPath();

	unsigned int ID;
private:

	
	void GenTexture(unsigned char* imgData, int w, int h, int c);
	int width, height, numColorChannels;
	unsigned char* imageData = nullptr;
	std::string filePath = "";
};