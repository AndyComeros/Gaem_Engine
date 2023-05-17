#pragma once
#pragma once
#include "Camera.h"
#include <iostream>
#include "OBJReader.h"
#include <lighting.h>
#include <Material.h>
/**
*	@Class DrawItem
*	@brief Shared interface for items that can be drawn using the renderer
*
*	@author Andres Comeros-Ochtman
*	@version 1.0
*	@date 20/04/2023
*/
class DrawItem {

public:
        /*
        *   @brief Render to the current buffer
        *   @param camera perspective being drawn from
        *   @param shader shader to use to draw object
        *   @param isElements if using element buffer
        *   @param primative draw primative used to render
        *   @return void
        */
    virtual  void Render(Camera* camera, Shader* shader, bool isElements, unsigned int primative);
        /*
        *   @brief Generic update method for drawitems that need to change visuals in relation to time
        *   @param deltaTime time since last frame
        *   @return void
        */
    virtual void Update(float deltaTime);
        /*
        *   @brief set Diffuse Texture
        *   @param nTexture, pointer to texture object being used,
        *   @return void
        */
    void SetDiffuseTexture(Texture* nTexture);
        /*
        *   @brief set Specular Texture
        *   @param nTexture, pointer to texture object being used,
        *   @return void
        */
    void SetSpecularTexture(Texture* nTexture);
        /*
        *   @brief set Emission Texture
        *   @param nTexture, pointer to texture object being used,
        *   @return void
        */
    void SetEmissionTexture(Texture* nTexture);
        /*
        *   @brief set Diffuse Texture
        *   @param fileName, pointer to texture file
        *   @return void
        */
    void SetDiffuseTexture(const char* fileName);
        /*
        *   @brief set Specular Texture
        *   @param fileName, pointer to texture file
        *   @return void
        */
    void SetSpecularTexture(const char* fileName);
        /*
        *   @brief set Emission Texture
        *   @param fileName, pointer to texture file
        *   @return void
        */
    void SetEmissionTexture(const char* fileName);

    Texture* GetDiffuseTexture(int index);
    Texture* GetSpecularTexture(int index);
    Texture* GetEmissionTexture(int index);

    bool visible = true;

protected:
        /*
        *   @brief Binds current material
        *   @return void
        */
    void BindMaterial(Shader* shader);

    Material material;
};