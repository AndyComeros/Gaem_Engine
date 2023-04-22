dofile("resources/scripts/inputs.lua")

function init()
	print("init lua");

	--load textures
	resources:LoadTexture("grass","resources/textures/terrain/grass.png");
	resources:LoadTexture("rock","resources/textures/terrain/rock.png");
	resources:LoadTexture("dirt","resources/textures/terrain/dirt.png");
	resources:LoadTexture("arcade","resources/models/untitled2022/Arcade.png");
	resources:LoadTexture("heightMap","resources/textures/heightmap/heightmap256.png");
	resources:LoadTexture("specular","resources/textures/tile_Specular2.png");
	resources:LoadTexture("detailMap","resources/textures/terrain/detail.png");
	resources:LoadTexture("AE86Diff","resources/textures/AE86.png");
	resources:LoadTexture("AE86Emis","resources/textures/AE86Emissive.png");
	resources:LoadTexture("AE86Spec","resources/textures/AE86Specular.png");
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
	resources:LoadModel("building2", "resources/models/untitled2022/CyberBuilding2.obj","buildingDiff","buildingEmiss","");
	resources:LoadModel("building3", "resources/models/untitled2022/CyberBuilding3.obj","buildingDiff","buildingEmiss","");
	resources:LoadModel("building4", "resources/models/untitled2022/CyberBuilding4.obj","buildingDiff","buildingEmiss","");
	resources:LoadModel("building5", "resources/models/untitled2022/CyberBuilding5.obj","buildingDiff","buildingEmiss","");
	resources:LoadModel("building6", "resources/models/untitled2022/CyberBuilding6.obj","buildingDiff","buildingEmiss","");
	resources:LoadModel("AE86", "resources/models/Toyota Sprinter Trueno AE86.obj", "AE86Diff", "AE86Emis", "AE86Spec");

	--setup lighting
	lighting = scene:GetLights();
	lighting:SetAmbient(0.1,0.1,0.1);
	lighting:AddDirectionLight(NormalizeVector(vec3.new( -1,0.5,0)),vec3.new( 0.4,0.4,0.4),vec3.new(1,1,1));


	--Load terrain
	terrain = resources:CreateTerrain("coolTerrain","heightMap",{"dirt","grass","rock"},"detailMap","detailMap","", 50 , 10.0,0.6,10.0);

	terrain:SetTextureScale(50);
	terrain:SetTextureHeights({-30,-5,40});
	physics:AddRigidBody(terrain,2);
	physics:AddRigidBodyColliderHeightMap(terrain);
	scene:AddObject(terrain);

	--Setup Player
	Player = resources:CreateGameObject("Player", "AE86", "");
	Player.position = vec3:new(0,5,0);
	physics:AddRigidBody(Player,3);
	local scale = vec3:new(1.5,0.2,0.7)
	local mass = 500;
	local bounce = 0.2;
	local friction = 0.5;
	physics:AddRigidBodyColliderBox(Player,scale, mass,bounce,friction);

	--Player.rigidBody:SetMass(500);
	Player.rigidBody:SetCenterOfMass(vec3:new(0,-2,0));
	Player.rigidBody:SetDampeningAngle(10);
	Player.rigidBody:SetDampeningLinear(1);
	
	scene:AddObject(Player);

	--buildings
	for i = 1,6,1
	do
		Building1 = resources:CreateGameObject("building"..i, "building1","");
		Building1:SetPosition(vec3:new(50 * i, 10, -500));
		Building1.scale = vec3:new(10,10,10);
		local scale = vec3:new(10,60,10)
		physics:AddRigidBody(Building1,2);
		physics:AddRigidBodyColliderBox(Building1,scale, mass,bounce,friction);
		scene:AddObject(Building1);
	end

	for i = 1,6,1
	do
		Building2 = resources:CreateGameObject("building"..i+6, "building3","");
		Building2:SetPosition(vec3:new(50 * i, 12, -400));
		Building2.scale = vec3:new(10,10,10);
		local scale = vec3:new(10,60,10)
		physics:AddRigidBody(Building2,2);
		physics:AddRigidBodyColliderBox(Building2,scale, mass,bounce,friction);
		scene:AddObject(Building2);
	end
	

	--NPC spawning
	math.randomseed(os.time());
	local tSize = terrain:GetSize() * 10;
	for i = 1,100,1
	do
		
		local xpos = math.random(1,tSize) - tSize/2;
		local zpos = math.random(1,tSize) - tSize/2;
		local ypos = terrain:GetHeight(xpos,zpos) + 5;
		
		Arcade = resources:CreateGameObject("arcade"..i, "arcade","");

		Arcade:SetPosition(vec3:new(xpos,ypos,zpos));
		Arcade.scale = vec3:new(5,5,5);
		local scale = vec3:new(0.5,1,0.5):multiply(3);
		physics:AddRigidBody(Arcade,3);
		physics:AddRigidBodyColliderBox(Arcade,scale, 1,0.3,0.5);
		Arcade.rigidBody:SetMass(1);
		scene:AddObject(Arcade);
	end
	
	--setup camera 
	camera = scene:GetCamera();
	camera.farPlane = 10000;
	scene:SetSkybox(resources:GetCubeMap("skybox"));
	
	print("End Init");
end

function update(deltaTime)
	local Player = scene:GetObject("Player");
	local height = terrain:GetHeight(Player.position.x,Player.position.z);

	Player.rigidBody:ApplyForce(vec3:new(0,-300 * deltaTime,0));

	KeyPressFunc(deltaTime);
	MouseMoveFunc(deltaTime);
end


