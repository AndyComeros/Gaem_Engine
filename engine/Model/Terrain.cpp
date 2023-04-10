#include "Terrain.h"

Terrain::Terrain()
{
	
}

Terrain::Terrain(const std::string& nHeightMap, float xScale, float yScale, float zScale) {
	scaleX = xScale;
	scaleY = yScale;
	scaleZ = zScale;
	LoadHeightMap(nHeightMap);
}

Terrain::Terrain(Texture* nHeightMap, float xScale, float yScale, float zScale){
	scaleX = xScale;
	scaleY = yScale;
	scaleZ = zScale;
	LoadHeightMap(nHeightMap);
}

Terrain::Terrain(std::vector<float> nHeights) {

	LoadHeightMap(nHeights);
}

Terrain::~Terrain()
{
	
}

float Terrain::GetHeight(float x, float z) {

	if (x >= (terrainSize - 1) || z >= (terrainSize - 1) || x < 0 || z < 0)
		return 0;

	int xDown = (int)x;
	int zDown = (int)z;

	int xUp = xDown + 1;
	int zUp = zDown + 1;

	float triZ0 = (heightArray[(xDown * terrainSize) + zDown]);
	float triZ1 = (heightArray[(xUp * terrainSize) + zDown]);
	float triZ2 = (heightArray[(xDown * terrainSize) + zUp]);
	float triZ3 = (heightArray[(xUp * terrainSize) + zUp]);

	float height = 0.0f;
	float sqX = x - xDown;
	float sqZ = z - zDown;
	if ((sqX + sqZ) < 1)
	{
		height = triZ0;
		height += (triZ1 - triZ0) * sqX;
		height += (triZ2 - triZ0) * sqZ;
	}
	else
	{
		height = triZ3;
		height += (triZ1 - triZ3) * (1.0f - sqZ);
		height += (triZ2 - triZ3) * (1.0f - sqX);
	}
	return height;
}

int Terrain::GetSize() {
	return terrainSize;
}

void Terrain::SetTextures(std::vector<Texture*> textures, Texture* detailMap) {

	if (textures.size() > MAX_TERRAIN_TEXTURES) { 
		std::cout << "ERROR: Max terrain textures is: " << MAX_TERRAIN_TEXTURES << std::endl; 
		return;
	}
		
	std::vector<int> tUnits;
	int tCount = 0;
	int i;
	for (i = 0; i < textures.size(); i++) {
		model_data->SetDiffuseTexture(textures[i]);
		tUnits.push_back(i);
		tCount++;
	}

	model_data->SetDiffuseTexture(detailMap);
	tUnits.push_back(i);

	//need to use all texture units in shader or GLSL will only use one texture
	for (i = tCount; i < MAX_TERRAIN_TEXTURES; i++)
		tUnits.push_back(0);

	shader->SetUniform("textures", tUnits);
	shader->SetUniform("textureCount", tCount);
}

void Terrain::SetTextureHeights(std::vector<float> heights) {

	shader->SetUniform("heights", heights);
	shader->SetUniform("heightCount", (int)heights.size());
}

void Terrain::SetTextureScale(float nScale) {
	if (nScale <= 0)
		return;

	textureScale = nScale;

	//if (heightArray.size() > 0)
		//GenerateModel();

}

void Terrain::LoadHeightMap(const std::string& fileName) {

	heightTexture = new Texture(fileName.c_str());
	CreateHeightArray();
	GenerateModel();
}

void Terrain::LoadHeightMap(Texture* nHeightMap) {
	
	heightTexture = nHeightMap;
	CreateHeightArray();
	GenerateModel();
}

void Terrain::LoadHeightMap(std::vector<float> nHeights) {
	heightArray = nHeights;
	terrainSize = (int)sqrt(nHeights.size());
	GenerateModel();
}

void Terrain::CreateHeightArray() {

	terrainSize = 0;

	if (!heightTexture)
		return;
	if(!heightArray.empty())
		heightArray.clear();

	int tWidth = heightTexture->GetWidth();
	int tHeight = heightTexture->GetHeight();

	if (tWidth != tHeight)
		return;

	terrainSize = tWidth;

	for (int y = 0; y < tHeight; y++)
	{
		for (int x = 0; x < tWidth; x++)
		{
			heightArray.emplace_back(scaleY * ((float)heightTexture->GetPixelValue(x, y, 0)));
		}
	}
}

void Terrain::GenerateModel() {

	if (heightArray.empty()) {
		model_data = new Model();
		return;
	}

	std::vector<vertex> vertexData;
	std::vector<glm::uvec3> elementsIndexes;
	std::vector<glm::vec3> faceNorms;

	vertexData.reserve(terrainSize * terrainSize);
	elementsIndexes.reserve((terrainSize - 1) * (terrainSize - 1) * 2);
	faceNorms.reserve((terrainSize - 1) * (terrainSize - 1) * 2);

	//create vert data
	float texCoordScaleX = (float)textureScale / (float)terrainSize;
	float texCoordScaleY = (float)textureScale / (float)terrainSize;
	for (int y = 0; y < terrainSize; y++)
	{
		for (int x = 0; x < terrainSize; x++)
		{
			vertex nVert;
			nVert.normal = { 0,0,0 };
			nVert.texCoord = { x * texCoordScaleX, y * texCoordScaleY };
			nVert.vertex.x = y * scaleZ;
			nVert.vertex.z = x * scaleX;
			nVert.vertex.y = heightArray[x +  (y * terrainSize)];

			vertexData.emplace_back(nVert);
		}
	}

	//create vert indexes for EBO
	for (int y = 0; y < terrainSize - 1; y++)
	{
		for (int x = 0; x < terrainSize - 1; x++)
		{
			glm::uvec3 nIndex;

			nIndex.x = (y * terrainSize) + x;
			nIndex.y = (y * terrainSize) + x + 1;
			nIndex.z = (y * terrainSize) + x + terrainSize;
			elementsIndexes.emplace_back(nIndex);

			nIndex.x = (y * terrainSize) + x + 1;
			nIndex.y = (y * terrainSize) + x + terrainSize + 1;
			nIndex.z = (y * terrainSize) + x + terrainSize;
			elementsIndexes.emplace_back(nIndex);
		}
	}

	//create norms for faces
	for (int i = 0; i < elementsIndexes.size(); i++)
	{
		glm::vec3 nNorm;
		glm::vec3 e1 = vertexData[elementsIndexes[i].x].vertex - vertexData[elementsIndexes[i].y].vertex;
		glm::vec3 e2 = vertexData[elementsIndexes[i].x].vertex - vertexData[elementsIndexes[i].z].vertex;

		nNorm = glm::cross(e1, e2);
		faceNorms.emplace_back(nNorm);
	}

	//assign vertecies norms
	for (int i = 0; i < elementsIndexes.size(); i++)
	{
		glm::ivec3 curFace = elementsIndexes[i];
		vertexData[curFace.x].normal += faceNorms[i];
		vertexData[curFace.y].normal += faceNorms[i];
		vertexData[curFace.z].normal += faceNorms[i];
	}
	for (int i = 0; i < vertexData.size(); i++)
	{
		vertexData[i].normal = glm::normalize(vertexData[i].normal);
	}

	if (model_data)
		delete model_data;

	model_data = new Model();
	model_data->SetVertexData(&vertexData[0].vertex.x, vertexData.size(), &elementsIndexes[0].x, elementsIndexes.size() * 3);
}	