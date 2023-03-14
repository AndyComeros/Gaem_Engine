#pragma once

#include <vector>
#include <iostream>
#include <stdlib.h>
#include "Asset.h"
#ifndef readFile_H
#define readFile_H

class readFile
{
public:
	void LoadAssetsFromFile(const char* dir, std::vector<Asset>& vector);
	
	void LoadModelsFromFile(const char* dir, std::vector<Model3D>& vector);

	void LoadShadersFromFile(const char* dir, std::vector<Shader>& vector);
};

//reads spreadsheet to create a vector of the game assets
inline void readFile::LoadAssetsFromFile(const char* dir, std::vector<Asset>& vector)
{
	std::vector<std::string> headers;
	std::ifstream assets(dir);
	std::string str = "test\n";

	//read heading of files
	std::getline(assets, str);
	std::stringstream ss(str);

	while (std::getline(ss, str, ','))
	{
		headers.push_back(str);
	}

	ss.clear();

	while (assets.good())
	{
		std::getline(assets, str);
		ss << str;
		Asset input;
		std::string token;
		std::string shader[3];
		int i = 0;
		while (std::getline(ss, token, ','))
		{
			
			if (headers[i].compare("ID") == 0)
			{
				if (token.empty())
					break;
				input.id = token;
			}
			if (headers[i].compare("Name") == 0)
			{
				input.name = token;
			}
			if (headers[i].compare("Model") == 0)
			{
				if (!token.empty())
					input.model = new Model3D(token.c_str());
				else
					continue;
			}
			if (headers[i].compare("DiffuseTexture") == 0)
			{
				if (!token.empty())
					input.Diffuse = new Texture(token.c_str());
				else
					continue;
			}
			if (headers[i].compare("EmissionTexture") == 0)
			{
				if (token.empty())
					continue;
				input.Emission = new Texture(token.c_str());
			}
			if (headers[i].compare("VertShader") == 0)
			{
				if (token.empty())
					continue;
				shader[0] = token;
			}
			if (headers[i].compare("FragShader") == 0)
			{
				if (token.empty())
					continue;
				shader[1] = token;
			}
			if (headers[i].compare("GeomShader") == 0)
			{
				if (token.empty())
					continue;
				shader[2] = token;
			}
			i++;
		}
		ss.clear();

		if (!shader[0].empty() && !shader[1].empty() && !shader[2].empty())
		{
			input.Shader = new Shader(shader[0].c_str(), shader[1].c_str(), shader[2].c_str());
		}
		else
			input.Shader = nullptr;

		if(!input.id.empty())
			vector.push_back(input);
	}
}

//reads a file to create a vector of models
//todo:change to spread sheet format if still needec
void readFile::loadModelsFromFile(const char* dir, std::vector<Model3D>& vector)
{
	std::ifstream models(dir);
	std::string str = "test\n";

	while (models.good())
	{

		std::getline(models, str);
		std::string firstTwo = str.substr(0, 2);

		if (firstTwo.compare("//") || str.empty())
		{
			continue;
		}
		std::string data[3];

		for (int i = 0; i < 3; i++)
		{
			std::getline(models, str);
			data[i] = str;
		}

		Model3D* model = new Model3D(data[0].c_str());
		model->setDiffuseTexture(data[1].c_str());
		model->setEmissionTexture(data[2].c_str());
		vector.push_back(*model);
	}
}

//reads a file to create a vector of shaders
//todo:change to spread sheet format if still needed
void readFile::loadShadersFromFile(const char* dir, std::vector<Shader>& vector)
{
	std::ifstream shaders(dir);
	std::string str = "test\n";

	while (shaders.good())
	{

		std::getline(shaders, str);
		std::string firstTwo = str.substr(0, 2);

		if (firstTwo.compare("//") || str.empty())
		{
			continue;
		}
		std::string data[3];

		for (int i = 0; i < 3; i++)
		{
			std::getline(shaders, str);
			data[i] = str;
		}

		Shader* shader = new Shader(data[0].c_str(), data[1].c_str(), data[2].c_str());
		vector.push_back(*shader);
	}
}
#endif