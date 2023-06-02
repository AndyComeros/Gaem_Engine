
function load_scene()
	
	lighting = scene:GetLights();
	--lighting:SetAmbient(0.1,0.0,0.1);
	lighting:SetAmbient(0.1,0.1,0.1);
	--lighting:SetAmbient(0.01,0.01,0.01);
	--lighting:SetAmbient(0,0,0);
	--lighting:AddDirectionLight(NormalizeVector(vec3.new( -1,0.5,0)),vec3.new( 0.0,0.6,0.6),vec3.new(1,1,1));
	--lighting:AddDirectionLight(NormalizeVector(vec3.new( 0,0.3,-1)):multiply(0.2),vec3.new( 0.98,0.8789,0.695),vec3.new(1,1,1):multiply(1));

	--lighting:AddPointLight( vec3:new(1140,30,640),
	--						vec3.new( 1,0,1),
	--						vec3.new( 0.98,0.8789,0.695),
	--						1.0,0.007,0.0002);
	--	vec3:new(1140,50,640)

		--void AddPointLight(const glm::vec3& position, const glm::vec3& diffuse, const glm::vec3& specular,
		--float constant, float linear, float quadratic) 

	
	--Load terrain
	terrain = resources:CreateTerrain("Terrain","heightMap",{"dirt","grass","rock"},"detailMap","detailMap","", 500 , 12,0.5,12);
	terrain:SetTextureHeights({-30,-5,40});
	physics:AddRigidBody(terrain,2);
	physics:AddRigidBodyColliderHeightMap(terrain);
	scene:AddObject(terrain);

	--load Water
	waterHeight = -50;
	water = resources:CreateWater( "watertest", 256, { "water", "flowMap", "DerivHeightMap" }, 50, 100, 1, 100);
	water.position = vec3:new(0,waterHeight,0);
	scene:AddObject(water);

	--Setup Player
	Player = resources:CreateNPCObject("Player", "AE86", "");
	Player.position = vec3:new(800,35,500);
	physics:AddRigidBody(Player,3);
	local scale = vec3:new(1.5,0.2,0.7)
	local mass = 500;
	local bounce = 0;
	local friction = 0.5;
	physics:AddRigidBodyColliderBox(Player,scale,vec3:new(0,0,0), mass,bounce,friction);
	Player.rigidBody:SetCenterOfMass(vec3:new(0,-2,0));
	Player.rigidBody:SetDampeningAngle(10);
	Player.rigidBody:SetDampeningLinear(1);
	Player.rigidBody:ToggleColliderListener();
	
	--player stats/health
	Player:AddData("health", 1000);
	Player:AddData("score", 0);
	Player:AddData("boost", 99);

	scene:AddObject(Player);

	--City
	math.randomseed(os.time());
	resources:LoadShader("holo","resources/shaders/Default.vert", "resources/shaders/hologram/Holo.frag", "");
	hologram = resources:CreateGameObject("zdancer", "dancer","holo");
	hologram.position = vec3:new(1140,50,640);
	hologram.scale = vec3:new(1,1,1):multiply(100);
	scene:AddObject(hologram);
	count = 0;
	rots = {0,90,180,270};

	for i = 0,22,1
	do
		for j = 0, 12, 1
		do
			if(math.random(1,10) < 5)
			then
				Building1 = resources:CreateGameObject("building"..count, "building"..math.random(1,6),"");
				Building1:SetPosition(vec3:new(700 + i * 40, 15, 350 + j * 50));
				Building1.scale = vec3:new(10,10,10);
				
				local scale = vec3:new(10,60,10)
				physics:AddRigidBody(Building1,2);
				physics:AddRigidBodyColliderBox(Building1,scale,vec3:new(0,0,0), mass,bounce,friction);

				m_rot = rots[math.random(1,4)];
				Building1:SetRotation(vec3:new(0,m_rot,0));
				scene:AddObject(Building1);
			end
	
			count = count + 1;
		end
	end

	
	--NPC spawning
	math.randomseed(os.time());
	local tSize = terrain:GetSize() * terrain.scaleX;

	attack_state  = ScriptableState:new(attack_enter, attack_update, attack_exit, attack_message);
	dead_state    = ScriptableState:new(dead_enter, dead_update, dead_exit, dead_message);
	global_state  = ScriptableState:new(global_enter, global_update, global_exit, global_message);
	empty_state   = ScriptableState:new(empty_enter, empty_update, empty_exit, empty_message);
	aimanager:AddState("attack_state",attack_state);
	aimanager:AddState("dead_state",dead_state);
	aimanager:AddState("global_state",global_state);
	aimanager:AddState("empty_state",empty_state);

	--// RigidBody type
	--#define KINE 1
	--#define STAT 2
	--#define DYNA 3
	for i = 1,100,1
	do
		
		local xpos = math.random(1,tSize) - tSize/2;
		local zpos = math.random(1,tSize) - tSize/2;
		local ypos = terrain:GetHeight(xpos,zpos) + 5;
		
		Robot = resources:CreateNPCObject("robot"..i, "robot","");

		physics:AddRigidBody(Robot,1);
		local scale = vec3:new(1,1,1)
		local offset = vec3:new(0,2,0);
		local mass = 100;
		local bounce = 0;
		local friction = 1;
		physics:AddRigidBodyColliderBox(Robot,scale,offset, mass,bounce,friction);
		Robot.rigidBody:SetCenterOfMass(vec3:new(0,2,0));
		Robot.rigidBody:SetDampeningAngle(0.5);
		Robot.rigidBody:SetDampeningLinear(10);
		--Robot.rigidBody:ToggleColliderListener();

		Robot:SetPosition(vec3:new(xpos,ypos,zpos));
		Robot.scale = vec3:new(2,2,2);
		Robot.stateMachine:ChangeGlobalState(global_state);

		scene:AddObject(Robot);
	end
end
