#include "Model.h"
#include <vector>

Model::Model(void) {
	elementCount = 0;
	vertCount = 0;
	instanceCount = 1;
	modelData = nullptr;
}

Model::Model(const char* fileName) {

	ReadOBJ(fileName);
	instanceCount = 1;
}

Model::~Model() {
	FreeData();
}

Model::Model(const char* fileName, std::vector<glm::mat4> nMatrix) {

	FreeData();
	modelData = ReadObjFile(fileName);
	vertCount = (int)modelData->vertexData.size();
	elementCount = (int)modelData->elements.size();
	SetInstanceMatrix(nMatrix);
}

void Model::SetInstanceMatrix(std::vector<glm::mat4> nMatrix) {
	
	FreeData();
	instanceMatrixes = nMatrix;
	instanceCount = (int)nMatrix.size();

	VAO nVAO;
	VBO iVBO(nMatrix);
	VBO nVBO(&modelData->vertexData[0].vertex.x, sizeof(float) * (int)modelData->vertexData.size() * 8);
	EBO nEBO(&modelData->elements[0], sizeof(unsigned int) * (int)modelData->elements.size());

	//normal vert data
	nVAO.AddAttribute(nVBO, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	nVAO.AddAttribute(nVBO, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	nVAO.AddAttribute(nVBO, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	//instance data
	iVBO.Bind();
	nVAO.AddAttribute(iVBO, 3, 4, GL_FLOAT, sizeof(glm::mat4), (void*)0);
	nVAO.AddAttribute(iVBO, 4, 4, GL_FLOAT, sizeof(glm::mat4), (void*)(1 * sizeof(glm::vec4)));
	nVAO.AddAttribute(iVBO, 5, 4, GL_FLOAT, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
	nVAO.AddAttribute(iVBO, 6, 4, GL_FLOAT, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));
	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);
	glVertexAttribDivisor(6, 1);

	ebo = nEBO;
	vao = nVAO;
	vbo = nVBO;
	ivbo = iVBO;

	vao.UnBind();
	vbo.UnBind();
	ivbo.UnBind();
	ivbo.Delete();
}

void Model::SetDiffuseTexture(Texture* nTexture) {
	material.diffuseTexture.push_back(nTexture);
}
void Model::SetSpecularTexture(Texture* nTexture) {
	material.specularMap.push_back(nTexture);
}
void Model::SetEmissionTexture(Texture* nTexture) {
	material.emissionMap.push_back(nTexture);
}

void Model::SetDiffuseTexture(const char* fileName) {
	material.diffuseTexture.push_back(new Texture(fileName));
}

void Model::SetSpecularTexture(const char* fileName) {
	material.specularMap.push_back(new Texture(fileName));
}

void Model::SetEmissionTexture(const char* fileName) {
	material.emissionMap.push_back(new Texture(fileName));
}

Texture* Model::GetDiffuseTexture(int index)  { return material.diffuseTexture[index]; }
Texture* Model::GetSpecularTexture(int index) { return material.specularMap[index]; }
Texture* Model::GetEmissionTexture(int index) { return material.emissionMap[index]; }

OBJData* Model::GetModelData() { return modelData; }

std::vector<glm::mat4>* Model::getInstanceMatrix() { return &instanceMatrixes; }

void Model::ReadOBJ(const char* fileName) {

	FreeData();
	modelData = ReadObjFile(fileName);
	SetVertexData(&modelData->vertexData[0].vertex.x, (int)modelData->vertexData.size(), &modelData->elements[0], (int)modelData->elements.size());

}

void Model::SetVertexData(float* nVertexData, int numData, unsigned int* vertIndexes, int numIndex) {
	FreeData();
	vertCount = numData;
	elementCount = numIndex;
	VAO nVAO;
	VBO nVBO(nVertexData, sizeof(float) * numData * 8);
	EBO nEBO(vertIndexes, sizeof(unsigned int) * numIndex);

	nVAO.AddAttribute(nVBO, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	nVAO.AddAttribute(nVBO, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	nVAO.AddAttribute(nVBO, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	vbo = nVBO;
	vao = nVAO;
}

void Model::SetVertexData(float* nVertexData, int numData) {
	FreeData();
	vertCount = numData;
	VAO nVAO;
	VBO nVBO(nVertexData, sizeof(float) * numData * 8);

	nVAO.AddAttribute(nVBO, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	nVAO.AddAttribute(nVBO, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	nVAO.AddAttribute(nVBO, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	vbo = nVBO;
	vao = nVAO;
}

void Model::SetVertexElements(unsigned int* vertIndexes, int numIndex) {
	elementCount = numIndex;
	vao.Bind();
	EBO nEBO(vertIndexes, sizeof(unsigned int) * numIndex);
	nEBO.Bind();
}

//isElements specifies if using glDrawElements instead of arrays. 
void Model::Render(Camera* camera, Shader* shader,bool isElements = true,unsigned int primative = GL_TRIANGLES) {

	unsigned int curTexture = GL_TEXTURE0;
	int diff = 0;
	int spec = 0;
	int emis = 0;
	if (!material.diffuseTexture.empty()) {
		diff = curTexture;
		for (int i = 0; i < material.diffuseTexture.size(); i++)
		{
			material.diffuseTexture[i]->Bind(curTexture);
			curTexture++;
		}
	}else {
		glActiveTexture(curTexture);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	if (!material.specularMap.empty()) {
		spec = curTexture;
		for (int i = 0; i < material.specularMap.size(); i++)
		{
			material.specularMap[i]->Bind(curTexture);
			curTexture++;
		}
	}else {
		glActiveTexture(curTexture);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	if (!material.emissionMap.empty()) {
		emis = curTexture;
		for (int i = 0; i < material.emissionMap.size(); i++)
		{
			material.emissionMap[i]->Bind(curTexture);
			curTexture++;
		}
	}else {
		glActiveTexture(curTexture);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	glm::mat4 view = camera->GetView();
	glm::mat4 projection = camera->GetProjection();

	//camera pos
	shader->SetUniform("cameraPos", camera->position);

	//basic postion matricies
	shader->SetUniform("view", view);
	shader->SetUniform("projection", projection);

	//set shader texture unit numbers
	shader->SetUniform("material.diffuseTexture", diff);
	shader->SetUniform("material.specularMap", spec);
	shader->SetUniform("material.emissionMap", emis);
	shader->SetUniform("material.alpha", material.shine);
	vao.Bind();

	if (instanceCount == 1) {
		if (isElements) {
			
			glDrawElements(primative, elementCount, GL_UNSIGNED_INT, 0);
		}
		else {
			
			glDrawArrays(primative, 0, vertCount);
		}
	}
	else {
		glDrawElementsInstanced(primative, elementCount, GL_UNSIGNED_INT, 0, instanceCount);
	}
	
	shader->Use();
	vao.UnBind();
}

void Model::FreeData() {
	vbo.Delete();
	ivbo.Delete();
	ebo.Delete();
	vao.Delete();
}

void Model::FreeEBO() {
	ebo.Delete();
}

