#include "TerrainManager.h"

TerrainManager::TerrainManager(int nChunkSize, int nWorldSize) {
	worldSize = nWorldSize;
	chunkSize = nChunkSize;

}
TerrainManager::TerrainManager(int nChunkSize, int nWorldSize, Texture* heightMap) {
	worldSize = nWorldSize;
	chunkSize = nChunkSize;
}

TerrainManager::~TerrainManager()
{

}

std::vector<float> TerrainManager::GenHeightMapFaultFormation(int size, int itterations, float minHeight, float maxHeight, float weight, float yScale) {

	//allocate texture buffer
	int bSize = size * size;
	std::vector<float> heightBuff;

	for (int i = 0; i < bSize; i++)
		heightBuff.push_back(0);

	//fault finding algorithm
	int iterr = itterations;
	float displacement;

	srand(glfwGetTime());

	for (int i = 0; i < iterr; i++)
	{
		displacement = maxHeight - ((maxHeight - minHeight) * ((float)i / itterations));

		int x1, x2, z1, z2;
		x1 = (rand() % (int)size);
		z1 = (rand() % (int)size);

		do
		{
			x2 = (rand() % (int)size);
			z2 = (rand() % (int)size);

		} while (x1 == x2 || z1 == z2);

		for (int z = 0; z < size; z++) {
			for (int x = 0; x < size; x++) {
				int y = (x2 - x1) * (z - z1) - (z2 - z1) * (x - x1);
				if (y > 0) {

					heightBuff[x + (z * size)] += (float)displacement;
				}
			}
		}

		AddFilter(heightBuff, weight, size);

	}

	NormalizeTerrain(heightBuff);

	for (int i = 0; i < bSize; i++)
	{
		heightBuff[i] *= yScale;
	}

	return heightBuff;
}

void TerrainManager::NormalizeTerrain(std::vector<float>& terrainData) {

	int size = terrainData.size();
	float fMin = terrainData[0];
	float fMax = terrainData[0];
	float fHeight;
	int i;
	//find the min and max values of the height terrainData
	for (i = 1; i < size; i++) {
		if (terrainData[i] > fMax)
			fMax = terrainData[i];
		else if (terrainData[i] < fMin)
			fMin = terrainData[i];
	}
	//find the range of the altitude
	if (fMax <= fMin)
		return;
	fHeight = fMax - fMin;
	//scale the values to a range of 0-255
	for (i = 0; i < size; i++)
		terrainData[i] = ((terrainData[i] - fMin) / fHeight) * 255.0f;
}


void filterPass(float* startP, int increment, float weight, int size) {
	float yprev = *startP; // the starting point in the terrain array
	int j = increment; // must be either +1, -1, +size, or -size
	float k = weight;

	for (int i = 1; i < size; i++) {
		// yi = k yi-1 + (1-k) xi
		*(startP + j) = k * yprev + (1 - k) * (*(startP + j));
		yprev = *(startP + j);
		j += increment;
	}
}

void TerrainManager::AddFilter(std::vector<float>& terrainData, float weight, int size) {
	int i;
	//erode left to right, starting from the beginning of each row
	for (i = 0; i < size; i++)
		filterPass(&terrainData[size * i], 1, weight, size);
	//erode right to left, starting from the end of each row
	for (i = 0; i < size; i++)
		filterPass(&terrainData[size * i + size - 1], -1, weight, size);
	//erode top to bottom, starting from the beginning of each column
	for (i = 0; i < size; i++)
		filterPass(&terrainData[i], size, weight, size);
	//erode from bottom to top, starting from the end of each column
	for (i = 0; i < size; i++)
		filterPass(&terrainData[size * (size - 1) + i], -size, weight, size);
}
