#include "Texture.h"
Texture::Texture() {}

Texture::Texture(const char* fileName) 
{
	stbi_set_flip_vertically_on_load(true);
	imageData = stbi_load(fileName,&width,&height,&numColorChannels,0);

	if (!imageData) {
		std::cout << "could not load image: " << fileName << std::endl;
	}
	glGenTextures(1, &ID);

	glBindTexture(GL_TEXTURE_2D,ID);//bind to change settings.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);//s for x axis
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);//t for y axis
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);//when image is squished
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);//when image is enlarged
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	
	switch (numColorChannels) {
	case 1:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, imageData);
		break;
	case 2:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RG, width, height, 0, GL_RG, GL_UNSIGNED_BYTE, imageData);
		break;
	case 3:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
		break;
	case 4:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
		break;
	default:
		break;
	}

	glGenerateMipmap(GL_TEXTURE_2D);
}

Texture::Texture(unsigned char* imgData, int w, int h,int c) {
<<<<<<< Updated upstream:engine/Model/Graphics/Texture.cpp
=======
	GenTexture(imgData,w,h,c);
	
}

Texture::~Texture() {

	stbi_image_free(imageData);
	glDeleteTextures(1,&ID);
}

void Texture::Bind(GLuint tUnit) {
	glActiveTexture(tUnit);
	glBindTexture(GL_TEXTURE_2D,ID);
	glEnable(GL_TEXTURE_2D);
}

unsigned char Texture::GetPixelValue(int x, int y, int index) {
	if (index > numColorChannels - 1) {
		return (unsigned char)0.0f;
	}
	return imageData[(y * width + x) * numColorChannels];
}

int Texture::GetChannelCount() {
	return numColorChannels;
}

int Texture::GetWidth() { return width; }

int Texture::GetHeight() { return height; }

void Texture::GenTexture(unsigned char* imgData, int w, int h, int c) {
>>>>>>> Stashed changes:engine/View/Graphics/OpenGL/Texture.cpp

	if (!imgData)
		std::cout << "could not load image data" << std::endl;

	width = w;
	height = h;
	numColorChannels = c;

	glGenTextures(1, &ID);
	
	glBindTexture(GL_TEXTURE_2D, ID);//bind to change settings.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);//s for x axis
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);//t for y axis
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);//when image is squished
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);//when image is enlarged
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	switch (numColorChannels) {
	case 1:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, imgData);
		break;
	case 2:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RG, width, height, 0, GL_RG, GL_UNSIGNED_BYTE, imgData);
		break;
	case 3:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imgData);
		break;
	case 4:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData);
		break;
	default:
		break;
	}

	imageData = imgData;
	glGenerateMipmap(GL_TEXTURE_2D);
}

Texture::~Texture() {

	stbi_image_free(imageData);
	glDeleteTextures(1,&ID);
}

void Texture::Bind(GLuint tUnit) {
	glActiveTexture(tUnit);
	glBindTexture(GL_TEXTURE_2D,ID);
	glEnable(GL_TEXTURE_2D);
}

unsigned char Texture::GetPixelValue(int x, int y, int index) {
	if (index > numColorChannels - 1) {
		//return (unsigned char)0.0f;
	}

	return imageData[(numColorChannels * (y * width + x))];
}

int Texture::GetChannelCount() {
	return numColorChannels;
}
