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

	virtual void SetUniforms();

	float GetHeight(float x, float z);
	glm::vec3 GetNormal(float x, float z);
	int GetSize();
	float GetMaxHeight();
	float GetMinHeight();
	std::vector<float>* GetHeightArray();

	//texutres
	void SetTextures(std::vector<Texture*> textures, Texture* detailMap);
	void SetTextureHeights(std::vector<float> heights);
	void SetTextureScale(float nScale);

	//Load Either a height map or array of height values
	void LoadHeightMap(const std::string& fileName);
	void LoadHeightMap(Texture* nHeightMap);
	void LoadHeightMap(std::vector<float> nHeights);
	

	float GetScaleX();
	float GetScaleY();
	float GetScaleZ();


private:
	//creates height values from array from heightTexture
	void CreateHeightArray();
	//generates the vertex buffer from height array
	void GenerateModel();

	//how often terrain textures repeat
	float textureScale = 10.0f;

	float scaleX = 1.0f;
	float scaleY = 1.0f;
	float scaleZ = 1.0f;
	int terrainSize;

	const int MAX_TERRAIN_TEXTURES = 11;

	float maxHeight = -100;
	float minHeight = 100;

	//Y values of the vertecies
	std::vector<float> *heightArray;
	//height map texture
	Texture* heightTexture = nullptr;

	std::vector<int> tUnits;
	int tCount = 0;
};
