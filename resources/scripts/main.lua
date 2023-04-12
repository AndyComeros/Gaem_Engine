

function init()
	print("init lua");


	--load textures
	resources:LoadTexture("grass","resources/textures/terrain/grass.png");
	resources:LoadTexture("rock","resources/textures/terrain/rock.png");
	resources:LoadTexture("dirt","resources/textures/terrain/dirt.png");
	resources:LoadTexture("arcade","resources/models/untitled2022/Arcade.png");
	resources:LoadTexture("heightMap","resources/textures/heightmap/heightMap128.png");
	resources:LoadTexture("specular","resources/textures/tile_Specular.png");
	
	--load skybox
	resources:LoadCubemap("skybox",
		"resources/textures/skybox/Synthwave2/Right.png",
		"resources/textures/skybox/Synthwave2/Left.png",
		"resources/textures/skybox/Synthwave2/Top.png",
		"resources/textures/skybox/Synthwave2/Bottom.png",
		"resources/textures/skybox/Synthwave2/Front.png",
		"resources/textures/skybox/Synthwave2/Back.png"
	);

	--load models
	resources:LoadModel("arcade", "resources/models/untitled2022/Arcade.obj","arcade","","");
	
	--load custom shaders
	
	--setup terrain
	terrain = resources:CreateTerrain("coolTerrain","heightMap",{"dirt","rock", "grass"},"specular",1.0,0.1,1.0);
	terrain:SetTextureHeights({1,2,3});

	--populate scene
	scene:SetSkybox(resources:GetCubeMap("skybox"));

	go = resources:CreateGameObject("bobbithy", "arcade", "");
	go2 = resources:CreateGameObject("bobbithy2", "arcade", "");
	go.position.y = 3;
	scene:AddObject(terrain);
	scene:AddObject(go);
	scene:AddObject(go2);	
	
	print("End Init");
end

function update(deltaTime)
	--print("Update lua" .. deltaTime);
end


