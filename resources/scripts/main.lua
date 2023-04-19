

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
	resources:LoadTexture("buildingDiff","resources/textures/Untitled2022/buildingDiffuse.png");
	resources:LoadTexture("buildingEmiss","resources/textures/Untitled2022/buildingEmissive.png");
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
	resources:LoadModel("building1", "resources/models/untitled2022/CyberBuilding1.obj","buildingDiff","buildingEmiss","");
	resources:LoadModel("AE86", "resources/models/Toyota Sprinter Trueno AE86.obj", "AE86", "", "");

	--setup lighting
	lighting = scene:GetLights();
	lighting:SetAmbient(0.0,0.0,0.0);
	lighting:AddDirectionLight(vec3.new( -0.7,0.5,-1),vec3.new( 0.7,0.1,0.5),vec3.new(0.5,0.3,0.05));

	--populate scene
	terrain = resources:CreateTerrain("coolTerrain","heightMap",{"dirt","grass","rock"},"specular", 50 , 10.0,0.6,10.0);
	terrain:SetTextureScale(20);
	terrain:SetTextureHeights({-30,-5,40});
	physics:AddRigidBody(terrain,2);
	physics:AddRigidBodyColliderHeightMap(terrain);

	--Player
	Player = resources:CreateGameObject("Player", "AE86", "");
	Player.position = vec3:new(0,5,0);
	physics:AddRigidBody(Player,3);
	local scale = vec3:new(1.5,0.2,0.6)
	local mass = 500;
	local bounce = 0.0;
	local friction = 0.4;
	physics:AddRigidBodyColliderBox(Player,scale, mass,bounce,friction);

	--buildings
	Building1 = resources:CreateGameObject("building1", "building1","");
	Building1:SetPosition(vec3:new(50, 20, -500));
	Building1.scale = vec3:new(10,10,10);
	scene:AddObject(Building1);
	
	--setup camera
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
	
	print(Player.position.x.." "..Player.position.y.." "..Player.position.z);

	TestInputFunc(deltaTime);
	MouseMoveFunc(deltaTime);
end


