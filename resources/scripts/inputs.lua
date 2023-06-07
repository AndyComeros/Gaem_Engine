
dofile("resources/scripts/keybinds.lua")


--This File Sets up all the player input events

input:BindKey("forward",KEY_W);
input:BindKey("backward",KEY_S);
input:BindKey("left",KEY_A);
input:BindKey("right",KEY_D);
input:BindKey("escape",KEY_ESCAPE);
input:BindKey("drift",KEY_SPACE);
input:BindKey("boost",KEY_LEFT_SHIFT);
input:BindKey("debug",KEY_K);
input:BindKey("toggleControlMenu",KEY_M);

input:BindKey("camF",KEY_UP);
input:BindKey("camB",KEY_DOWN);
input:BindKey("camU",KEY_1);
input:BindKey("camD",KEY_0);
input:BindKey("camL",KEY_LEFT);
input:BindKey("camR",KEY_RIGHT);

lastX = input:GetMouseX();
lastY = input:GetMouseY();
mouseSensitivity = 0.1
Distance = 10
moveSpeed = 100


function MouseMoveFunc(dt)
	local camera = scene:GetCamera();
	xPos = input:GetMouseX();
	yPos = input:GetMouseY();
	
	xoffset = (xPos - lastX)
	yoffset = (lastY - yPos)

	lastX = xPos
	lastY = yPos

	xoffset = xoffset * -mouseSensitivity
	yoffset = yoffset * -mouseSensitivity


	camera.Yaw =  camera.Yaw - xoffset
	camera.Pitch = camera.Pitch - yoffset

	--camDistance();
	CalaulateCamPos();
	camera:UpdateCameraVectors();
end

function camDistance()
	scrollOffset = input:GetScrollOffset();
	Distance = Distance - scrollOffset;
	if (Distance < 3.0)
	then
		Distance = 3.0;
	end
	if (Distance > 300.0)
	then
		Distance = 300.0;
	end
end



function CalaulateCamPos()
	local camera = scene:GetCamera();
	yaw = camera.Yaw - 90.0;

	pitch = -camera.Pitch;
	-- calaulate camera using camera pitch and yaw
	x = math.cos(math.rad(pitch)) * math.sin(math.rad(-yaw));
	y = math.sin(math.rad(pitch)) * -1;
	z = math.cos(math.rad(pitch)) * math.cos(math.rad(yaw));

	local player = scene:GetObject("Player")

end

local debugPress = false;
function KeyPressFunc(dt)

	local player = scene:GetObject("Player")
	local camera = scene:GetCamera();
	local turnspeed = 1500 * dt;
	local movespeed = 4000 * dt;
	local finalMove = movespeed;
	local finalTurn = turnspeed;
	local boostMult = 3;
	local driftMult = 2;
	local playerHeight = player.position.y - terrain:GetHeight(player.position.x,player.position.z);
	--local playerSpeed = Length(player.rigidBody:GetLinearVelocity());

	--print(player.position.x .. " " .. player.position.z);
	if(input:GetKeyState("escape") and  current_menu ~= 1)
	then
		Sound:playSound("pause",camera.position);
		current_menu = 1;
	end


	if(input:GetKeyState("debug") and (not debugPress))
	then
		debugPress = true;
		--renderer:ToggleWireFrame();
		physics:ToggleDebugDisplay();

	elseif(input:GetKeyState("debug"))
	then
		debugPress = true;
	else
		debugPress = false;
	end

	if(input:GetKeyState("toggleControlMenu"))
	then
		controlPress = true;
	end


	local currentBoost = Player:GetData("boost");
	if(input:GetKeyState("boost") and currentBoost > 0)
	then
		Player:AddData("boost", currentBoost - (dt * 20));
	end
	if(math.floor(currentBoost) < 0)
	then
		Player:AddData("boost", 0);
	end

	if(playerHeight  < 1)
	then 
		Player.rigidBody:SetDampeningLinear(0.9);	

		if(input:GetKeyState("boost") and currentBoost > 0)
		then
			finalMove = finalMove * boostMult;
		end

		if(input:GetKeyState("drift") and (input:GetKeyState("forward") or input:GetKeyState("backward")))
		then
			finalTurn = finalTurn * driftMult;
		end	

		if(input:GetKeyState("forward"))
		then
			local dir = vec3:new(1,0,0):multiply(-finalMove);
			player.rigidBody:ApplyForceLocal(dir)
		end
		
		if(input:GetKeyState("backward"))
		then
			local dir = vec3:new(1,0,0):multiply(finalMove);
			player.rigidBody:ApplyForceLocal(dir)
		end
		
		if(input:GetKeyState("left"))
		then
			local dir = vec3:new(0,1,0):multiply(finalTurn);
			player.rigidBody:ApplyTorqueLocal(dir)
		end
		
		if(input:GetKeyState("right"))
		then
			local dir = vec3:new(0,1,0):multiply(-finalTurn);
			player.rigidBody:ApplyTorqueLocal(dir)
		end
	else
		Player.rigidBody:SetDampeningLinear(0);
	end
		up = vec3:new(0,1,0);
		camSpeed = 100 * dt;
		if(input:GetKeyState("camF"))
		then
			camera.position = camera.position +  NormalizeVector(CrossVectors(up,camera.right)):multiply(camSpeed);
		end
		if(input:GetKeyState("camB"))
		then
			camera.position = camera.position -  NormalizeVector(CrossVectors(up,camera.right)):multiply(camSpeed);
			
		end
		if(input:GetKeyState("camU"))
		then
			camera.position = camera.position + up:multiply(camSpeed);
			
		end
		if(input:GetKeyState("camD"))
		then
			camera.position = camera.position - up:multiply(camSpeed);
			
		end
		if(input:GetKeyState("camL"))
		then
			camera.position = camera.position - camera.right:multiply(camSpeed);
		end
		if(input:GetKeyState("camR"))
		then
			camera.position = camera.position + camera.right:multiply(camSpeed);
		end

end