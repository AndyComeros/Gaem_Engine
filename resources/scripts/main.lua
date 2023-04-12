

function init()
	print("init lua");

	resources:TestPrint("print!");
	--resources:LoadTexture("resources/textures/tile_specular.png","rock");



	--void LoadTexture(std::string fileName, std::string resName);
	--void LoadModel(std::string fileName, std::string resName);
	--void LoadShader(std::string vertPath, std::string fragPath, std::string geomPath, std::string resName);

	--Texture* GetTexture(std::string resName);
	--Model* GetModel(std::string resName);
	--Shader* GetShader(std::string resName);
	print("End Init");
end

function update(deltaTime)
	--print("Update lua" .. deltaTime);
end


