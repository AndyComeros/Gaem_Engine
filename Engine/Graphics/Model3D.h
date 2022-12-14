#pragma once
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"
#include "Texture.h"
#include "Shader.h"
#include "Camera.h"
#include <iostream>
#include "OBJReader.h"

/**
*	@Class model3D
*	@brief stores mesh and texture data for a model
*
*	@author Andres Comeros-Ochtman
*	@version 2.0
*	@date 30/10/2022
*/
class model3D {
public:
        /**
        *	@brief default constructor
        */
	model3D();
        /*
        *   @brief default destructor, ensures textures and model data is freed
        */
	~model3D();
        /**
        *	@brief constructor with inital obj file
        *   @param fileName file path to OBJ file
        */
	model3D(const char* fileName);
        /**
        *	@brief constructor with inital obj file and model matrix vector for instancing
        *   @param fileName file path to OBJ file
        *   @param nMatrix vector of transforms for instances of this model
        */
    model3D(const char* fileName, std::vector<glm::mat4> nMatrix);
        /*
        *   @brief sets the model data based on obj file
        *   @param fileName file path to obj file
        *   @return bool - if read was a success
        */
	bool readOBJ(const char *fileName);
        /*
        *   @brief Sets vertex data manually, use if data uses an EBO
        *   @param nVertexData pointer to array of verticies for VBO
        *   @param numData size of vertex array
        *   @param vertIndexes  pointer to array of indicies for the EBO
        *   @param numIndex size of vertIndexes
        *   @return void
        */
	void setVertexData(float* nVertexData, int numData,unsigned int *vertIndexes,int numIndex);
        /*
        *   @brief Sets vertex data manually, use if data does not use an EBO
        *   @param nVertexData pointer to array of verticies for VBO
        *   @param numData size of vertex array
        *   @return void
        */
    void setVertexData(float* nVertexData, int numData);
        /*
        *   @brief Sets Index data manually, use if data uses and EBO
        *   @param vertIndexes  pointer to array of indicies for the EBO
        *   @param numIndex size of vertIndexes
        *   @return void
        */
    void setVertexElemements(unsigned int* vertIndexes, int numIndex);
        /*
        *   @brief draw this model using specified camera and shader
        *   @param camera camera data to modify vertecies by in shader
        *   @param shader shader program used to render the geometry
        *   @param isElements whether an EBO is used to render this object
        *   @param primative which openGL primative to draw using the vertecies
        *   @return void
        */
	void render(Camera* camera, Shader* shader, bool isElements, unsigned int primative);
        /*
        *   @brief set instance data
        *   @param nMatrix all transforms for each instance
        *   @return void
        */
    void setInstanceMatrix(std::vector<glm::mat4> nMatrix);
        /*
        *   @brief set Diffuse Texture
        *   @param nTexture, pointer to texture object being used,
        *   @return void
        */
	void setDiffuseTexture (Texture* nTexture);
        /*
        *   @brief set Specular Texture
        *   @param nTexture, pointer to texture object being used,
        *   @return void
        */
	void setSpecularTexture(Texture* nTexture);
        /*
        *   @brief set Emission Texture
        *   @param nTexture, pointer to texture object being used,
        *   @return void
        */
	void setEmissionTexture(Texture* nTexture);
        /*
        *   @brief set Diffuse Texture
        *   @param fileName, pointer to texture file
        *   @return void
        */
    void setDiffuseTexture (const char* fileName);
        /*
        *   @brief set Specular Texture
        *   @param fileName, pointer to texture file
        *   @return void
        */
    void setSpecularTexture(const char* fileName);
        /*
        *   @brief set Emission Texture
        *   @param fileName, pointer to texture file
        *   @return void
        */
    void setEmissionTexture(const char* fileName);
        
    Texture* getDiffuseTexture ();
    Texture* getSpecularTexture();
    Texture* getEmissionTexture();
    OBJData* getModelData();
    std::vector<glm::mat4>* getInstanceMatrix();
    

    //careful using, same EBO and VAO may be used by multiple objects
    void freeData();
    void freeEBO();
private:
	int vertCount;
	int elementCount;
	VAO vao;
    VBO vbo;
    VBO ivbo;
    EBO ebo;
    OBJData* modelData;

	Texture* diffuseTexture;
	Texture* specularMap;
	Texture* emissionMap;

    std::vector<glm::mat4> instanceMatrixes;
    int instanceCount;
};

//generic cube
static float vertices[] = {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};