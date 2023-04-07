#pragma once
#include <Terrain.h>
#include <Scene.h>

class TerrainManager
{
public:
	TerrainManager(int nChunkSize, int nWorldSize);
	TerrainManager(int nChunkSize, int nWorldSize, Texture* heightMap);
	~TerrainManager();

	static std::vector<float> GenHeightMapFaultFormation(int size, int itterations, float minHeight, float maxHeight, float weight,float yScale);
private:

	std::vector<Terrain*> chunks;

	int chunkSize;
	int worldSize;

	float scaleY;

	unsigned int seed;

	static void AddFilter(std::vector<float>&, float weight, int size);
	static void NormalizeTerrain(std::vector<float>& terrainData);
};
