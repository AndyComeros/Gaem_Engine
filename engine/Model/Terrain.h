#pragma once
#include "GameObject.h"

class Terrain : public GameObject
{
public:
	Terrain();
	Terrain(const std::string& nHeightMap,float xScale, float yScale, float zScale);
	Terrain(Texture* nHeightMap, float xScale, float yScale, float zScale);
	Terrain(std::vector<float> nHeights);
	~Terrain();

	float GetHeight(float x, float z);
	int GetSize();

	//texutres
	void SetTextures(std::vector<Texture*> textures, Texture* detailMap);
	void SetTextureHeights(std::vector<float> heights);
	void SetTextureScale(float nScale);

	//Load Either a height map or array of height values
	void LoadHeightMap(const std::string& fileName);
	void LoadHeightMap(Texture* nHeightMap);
	void LoadHeightMap(std::vector<float> nHeights);

private:
	//creates height values from array from heightTexture
	void CreateHeightArray();
	//generates the vertex buffer from height array
	void GenerateModel();

	//how often terrain textures repeat
	float textureScale = 1.0f;

	float scaleX = 1.0f;
	float scaleY = 1.0f;
	float scaleZ = 1.0f;
	int terrainSize;

	const int MAX_TERRAIN_TEXTURES = 11;

	//Y values of the vertecies
	std::vector<float> heightArray;
	//height map texture
	Texture* heightTexture = nullptr;
};
