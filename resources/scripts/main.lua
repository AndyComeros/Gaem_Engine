

function init()
	print("init lua");


	--load textures
	resources:LoadTexture("grass","resources/textures/terrain/grass.png");
	resources:LoadTexture("rock","resources/textures/terrain/rock.png");
	resources:LoadTexture("dirt","resources/textures/terrain/dirt.png");
	resources:LoadTexture("arcade","resources/models/untitled2022/Arcade.png");
	
	--load models
	resources:LoadModel("arcade", "resources/models/untitled2022/Arcade.obj","arcade","","");
	
	--load custom shaders
	resources:LoadShader("mainShader","resources/shaders/Default.vert","resources/shaders/Default.frag","");

	
	--populate scene
	scene:AddObject(resources:CreateGameObject("bobbithy", "arcade", ""));

	
	print("End Init");
end

function update(deltaTime)
	--print("Update lua" .. deltaTime);
end


