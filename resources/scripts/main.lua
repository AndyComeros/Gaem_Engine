dofile("resources/scripts/menu.lua")
dofile("resources/scripts/inputs.lua")
dofile("resources/scripts/load_resources.lua")
dofile("resources/scripts/load_scene.lua")
dofile("resources/scripts/ai_states.lua")

function init()
	print("init lua");

	-- set window properties
	engine:SetWindowIcon("resources/textures/icon.png");
	engine:SetWindowName("InitalZ");
	GUI:SetFont("resources/fonts/Excluded-z8XrX.ttf");

	--load resources
	load_resources();
	
	--load scene
	load_scene();
	
	--setup camera 
	camera = scene:GetCamera();
	camera.farPlane = 10000;
	scene:SetSkybox(resources:GetCubeMap("skybox"));

	print("End Init");
end

function update(deltaTime)

	Player = scene:GetNPC("Player");
	Player.rigidBody:ApplyForce(vec3:new(0,-300 * deltaTime,0));
	draw_menu();
	KeyPressFunc(deltaTime);
	MouseMoveFunc(deltaTime);
	Sound:setListenerPos(camera.position);
	Sound:setMusicPos(camera.position);
	lock_player_terrain();
	check_hazard_collide();
	inscrease_boost(deltaTime);
end

function lock_player_terrain()
	t_Height = terrain:GetHeight(Player.position.x,Player.position.z);

	if(Player.position.y < t_Height - 1)
	then
		local player = scene:GetObject("Player")
		player:SetPosition(vec3:new(player.position.x,t_Height + 1,player.position.z));
	end
end

function check_hazard_collide()
	t_Height = terrain:GetHeight(Player.position.x,Player.position.z);

	if(Player.position.y <= waterHeight)
	then
		current_menu = 7;
	end
end

function inscrease_boost(dt)
	local rechargeRate = 5;
	local maxBoost = 99;
	local currentBoost = Player:GetData("boost");

	if(math.floor(currentBoost) == maxBoost)
	then
		Player:AddData("boost", maxBoost);
	end

	if(currentBoost < maxBoost)
	then
		Player:AddData("boost", currentBoost + (dt * rechargeRate));
	end
end

