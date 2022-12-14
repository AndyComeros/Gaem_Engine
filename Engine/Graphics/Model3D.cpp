#include "Model3D.h"
#include <vector>

model3D::model3D(void) {
	elementCount = 0;
	diffuseTexture = nullptr;
	specularMap = nullptr;
	emissionMap = nullptr;
	vertCount = 0;
	instanceCount = 1;
}

model3D::model3D(const char* fileName) {
	readOBJ(fileName);
	instanceCount = 1;
}

model3D::~model3D() { 
	freeData();
	
	if (diffuseTexture)
		delete diffuseTexture;
	if (specularMap)
		delete specularMap;
	if (emissionMap)
		delete emissionMap;
	if (modelData)
		delete modelData;

}

model3D::model3D(const char* fileName, std::vector<glm::mat4> nMatrix) {

	freeData();
	modelData = ReadObjFile(fileName);
	vertCount = modelData->vertexData.size();
	elementCount = modelData->elements.size();
	setInstanceMatrix(nMatrix);


}

void model3D::setInstanceMatrix(std::vector<glm::mat4> nMatrix) {
	
	freeData();
	instanceMatrixes = nMatrix;
	instanceCount = nMatrix.size();

	VAO nVAO;
	VBO iVBO(nMatrix);
	VBO nVBO(&modelData->vertexData[0].vertex.x, sizeof(float) * modelData->vertexData.size() * 8);
	EBO nEBO(&modelData->elements[0], sizeof(unsigned int) * modelData->elements.size());

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

void model3D::setDiffuseTexture(Texture* nTexture) {
	diffuseTexture = nTexture;
}
void model3D::setSpecularTexture(Texture* nTexture) {
	specularMap = nTexture;
}
void model3D::setEmissionTexture(Texture* nTexture) {
	emissionMap = nTexture;
}

void model3D::setDiffuseTexture(const char* fileName) {
	diffuseTexture = new Texture(fileName);
}

void model3D::setSpecularTexture(const char* fileName) {
	specularMap = new Texture(fileName);
}

void model3D::setEmissionTexture(const char* fileName) {
	emissionMap = new Texture(fileName);
}

Texture* model3D::getDiffuseTexture()  { return diffuseTexture; }
Texture* model3D::getSpecularTexture() { return specularMap; }
Texture* model3D::getEmissionTexture() { return emissionMap; }

OBJData* model3D::getModelData() { return modelData; }

std::vector<glm::mat4>* model3D::getInstanceMatrix() { return &instanceMatrixes; }

bool model3D::readOBJ(const char* fileName) {
	freeData();
	modelData = ReadObjFile(fileName);

	vertCount = modelData->vertexData.size();
	elementCount = modelData->elements.size();

	VAO nVAO;
	VBO nVBO(&modelData->vertexData[0].vertex.x,sizeof(float) * modelData->vertexData.size() * 8);
	EBO nEBO(&modelData->elements[0], sizeof(unsigned int) * modelData->elements.size());

	//unsigned int* indexes, int size
	nVAO.AddAttribute(nVBO,0,3,GL_FLOAT,8 * sizeof(float),(void*)0);
	nVAO.AddAttribute(nVBO,1,3,GL_FLOAT,8 * sizeof(float),(void*)(3 * sizeof(float)));
	nVAO.AddAttribute(nVBO,2,2,GL_FLOAT,8 * sizeof(float),(void*)(6 * sizeof(float)));
	vbo = nVBO;
	vao = nVAO;
	return true;
}

void model3D::setVertexData(float* nVertexData, int numData, unsigned int* vertIndexes, int numIndex) {
	freeData();
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

void model3D::setVertexData(float* nVertexData, int numData) {
	freeData();
	vertCount = numData;
	VAO nVAO;
	VBO nVBO(nVertexData, sizeof(float) * numData * 8);

	nVAO.AddAttribute(nVBO, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	nVAO.AddAttribute(nVBO, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	nVAO.AddAttribute(nVBO, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	vbo = nVBO;
	vao = nVAO;
}

void model3D::setVertexElemements(unsigned int* vertIndexes, int numIndex) {
	elementCount = numIndex;
	vao.Bind();
	EBO nEBO(vertIndexes, sizeof(unsigned int) * numIndex);
	nEBO.Bind();
}

//isElements specifies if using glDrawElements instead of arrays. 
void model3D::render(Camera* camera, Shader* shader,bool isElements,unsigned int primative) {

	if (diffuseTexture != nullptr) {
		diffuseTexture->Bind(GL_TEXTURE0);
	}else {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	if (specularMap != nullptr) {
		specularMap->Bind(GL_TEXTURE1);
	}else {
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	if (emissionMap != nullptr) {
		emissionMap->Bind(GL_TEXTURE2);
	}else {
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	glm::mat4 view = camera->GetViewMatrix();
	glm::mat4 projection = camera->GetProjectionMatrix();

	//basic postion matricies
	shader->setUniform("view", view);
	shader->setUniform("projection", projection);

	//set textures
	shader->setUniform("material.diffuseTexture", 0);
	shader->setUniform("material.specularMap", 1);
	shader->setUniform("material.emissionMap", 2);
	shader->setUniform("material.alpha", 5.0f);//hmmmmmmmmmmmmm.. why tho, why here?
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


void model3D::freeData() {
	//vao.Bind();
	vbo.Delete();
	ivbo.Delete();
	ebo.Delete();
	vao.Delete();
}

void model3D::freeEBO() {
	ebo.Delete();
}