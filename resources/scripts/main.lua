

dofile("resources/scripts/inputs.lua")

function init()
	print("init lua");

	--load textures
	resources:LoadTexture("grass","resources/textures/terrain/grass.png");
	resources:LoadTexture("rock","resources/textures/terrain/rock.png");
	resources:LoadTexture("dirt","resources/textures/terrain/dirt.png");
	resources:LoadTexture("arcade","resources/models/untitled2022/Arcade.png");
	resources:LoadTexture("heightMap","resources/textures/heightmap/heightmap256.png");
	resources:LoadTexture("specular","resources/textures/tile_Specular.png");
	resources:LoadTexture("black","resources/textures/terrain/black.png");
	resources:LoadTexture("AE86","resources/textures/AE86.png");



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
	resources:LoadModel("AE86", "resources/models/Toyota Sprinter Trueno AE86.obj", "AE86", "", "");

	--setup lighting
	lighting = scene:GetLights();
	lighting:SetAmbient(0.2,0.2,0.2);
	lighting:AddDirectionLight(vec3.new( -0.7,0.5,-1),vec3.new( 0.7,0.1,0.5),vec3.new(0.5,0.3,0.05));

	--populate scene
	terrain = resources:CreateTerrain("coolTerrain","heightMap",{"dirt","grass","rock"},"specular",10.0,0.6,10.0);
	terrain:SetTextureScale(50);
	terrain:SetTextureHeights({-30,-5,40});
	physics:AddRigidBody(terrain,2);
	physics:AddRigidBodyColliderHeightMap(terrain);

	Player = resources:CreateGameObject("Player", "AE86", "");
	Player.position = vec3:new(0,10,0);
	physics:AddRigidBody(Player,3);
	local scale = vec3:new(1.5,0.2,0.6)

	local mass = 500;
	local bounce = 0.0;
	local friction = 0.4;
	--physics:AddRigidBodyColliderSphere(Player,0.3,vec3:new(1,0,0.5)	,  mass,bounce,friction);
	--physics:AddRigidBodyColliderSphere(Player,0.3,vec3:new(1,0,-0.5),  mass,bounce,friction);
	--physics:AddRigidBodyColliderSphere(Player,0.3,vec3:new(-1,0,0.5),  mass,bounce,friction);
	--physics:AddRigidBodyColliderSphere(Player,0.3,vec3:new(-1,0,-0.5), mass,bounce,friction);
	physics:AddRigidBodyColliderBox(Player,scale, mass,bounce,friction);


	--for i = 0, 9, 1 
	--do
	--	local name = "arcade"..i;
	--	go = resources:CreateGameObject(name, "arcade", "");
	--	go.position.y = i * 3;
	--	go.position.x = 3;
	--	physics:AddRigidBody(go,3);
	--	local scale = vec3:new(0.5,0.8,0.5)
	--	physics:AddRigidBodyColliderBox(go,scale,mass,bounce,friction);
	--	
	--	scene:AddObject(go);
	--end

	 --#define KINE 1
	 --#define STAT 2
	 --#define DYNA 3
	camera = scene:GetCamera();
	camera.farPlane = 10000;
	camera.position.x = 0;
	camera.position.y = 5;

	scene:SetSkybox(resources:GetCubeMap("skybox"));
	scene:AddObject(terrain);
	scene:AddObject(Player);

	--turn on debug mesh
	--physics:ToggleDebugDisplay();
	print("End Init");
end

function update(deltaTime)
	local Player = scene:GetObject("Player");
	local height = terrain:GetHeight(Player.position.x,Player.position.z);
	--Player:SetPosition(vec3:new(Player.position.x,height +5,Player.position.z));
	TestInputFunc(deltaTime);
	MouseMoveFunc(deltaTime);
end


