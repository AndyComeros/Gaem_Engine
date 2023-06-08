dofile("resources/scripts/menu.lua")
dofile("resources/scripts/inputs.lua")
dofile("resources/scripts/load_resources.lua")
dofile("resources/scripts/load_scene.lua")
dofile("resources/scripts/ai_states.lua")

--main init function, called once before update
function init()

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

end

--main update function, called every frame
function update(deltaTime)
	
	Player = scene:GetNPC("Player");
	Player.rigidBody:ApplyForce(vec3:new(0,-300 * deltaTime,0));
	DynamicFOV();
	KeyPressFunc(deltaTime);
	MouseMoveFunc(deltaTime);
	draw_menu();
	Sound:setListenerPos(camera.position);
	Sound:setMusicPos(camera.position);
	lock_player_terrain();
	check_hazard_collide();
	inscrease_boost(deltaTime);
	check_player_death();
	
end

--check if player is dead
function check_player_death()
	if(Player:GetData("health") <= 0)
	then
		Sound:playSound("explode",camera.position);
		current_menu = 7;
		Player:AddData("health", 1);
	end

end

--Stop player from fallnig through the ground
function lock_player_terrain()
	t_Height = terrain:GetHeight(Player.position.x,Player.position.z);

	if(Player.position.y < t_Height - 1)
	then
		local player = scene:GetObject("Player")
		player:SetPosition(vec3:new(player.position.x,t_Height + 1,player.position.z));
	end
end

--Check if player has hit a danger zone
function check_hazard_collide()
	t_Height = terrain:GetHeight(Player.position.x,Player.position.z);

	if(Player.position.y <= waterHeight)
	then
		if(Player:GetData("isAlive") == 1)
		then
			Sound:playSound("splash",camera.position);
		end
		Player:AddData("isAlive", 0);
		current_menu = 7;
	end
end


--increase players boost
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

--modify camera FOV based on player speed
DefaultFOV = 45.0;
FOVChange = 5;
function DynamicFOV()
	local camera = scene:GetCamera();
	velocity = Player.rigidBody:GetLinearVelocity();
	
	test = vec3:new(velocity.x,0,velocity.z);
	length = Length(test);
	
	mod = 0;

	mod = FOVChange * (length/10);

	camera.FOV = DefaultFOV + mod;
	
end