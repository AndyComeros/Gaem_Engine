

function init()
	print("init lua");
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

	--setup lighting
	lighting = scene:GetLights();
	lighting:SetAmbient(0.3,0.3,0.3);
	lighting:AddDirectionLight(vec3.new( -0.7,0.5,-1),vec3.new( 0.7,0.1,0.5),vec3.new(0.5,0.3,0.05));

	--populate scene
	go = resources:CreateGameObject("bobbithy", "arcade", "");
	go2 = resources:CreateGameObject("bobbithy2", "arcade", "");

	terrain = resources:CreateTerrain("coolTerrain","heightMap",{"dirt","grass","rock"},"black",5.0,0.2,5.0);
	terrain:SetTextureHeights({0,60,80});

	camera = scene:GetCamera();
	camera.position = vec3.new(terrain:GetSize()/2,0,terrain:GetSize()/2);
	camera.position.y = terrain:GetHeight(terrain:GetSize()/2,terrain:GetSize()/2) + 5;

	scene:SetSkybox(resources:GetCubeMap("skybox"));
	scene:AddObject(terrain);
	scene:AddObject(go);
	scene:AddObject(go2);	
	
	print("End Init");
end

function update(deltaTime)
	print("Update lua" .. deltaTime);
end


