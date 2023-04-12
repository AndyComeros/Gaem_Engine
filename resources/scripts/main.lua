

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

	--load models
	resources:LoadModel("arcade", "resources/models/untitled2022/Arcade.obj","arcade","","");
	
	--load custom shaders
	resources:LoadShader("mainShader","resources/shaders/Default.vert","resources/shaders/Default.frag","");

	
	--populate scene
	terrain = resources:CreateTerrain("coolTerrain","heightMap",{"dirt","rock", "grass"},"specular",1.0,0.1,1.0);

	go = resources:CreateGameObject("bobbithy", "arcade", "");
	go2 = resources:CreateGameObject("bobbithy2", "arcade", "");
	go.position.y = 3;
	scene:AddObject(terrain);
	scene:AddObject(go);
	scene:AddObject(go2);
	



	print()
	
	
	
	print("End Init");
end

function update(deltaTime)
	--print("Update lua" .. deltaTime);
end


