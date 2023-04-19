
dofile("resources/scripts/keybinds.lua")

input:SetMouseLock(false);

input:BindKey("forward",KEY_W);
input:BindKey("backward",KEY_S);
input:BindKey("left",KEY_A);
input:BindKey("right",KEY_D);
input:BindKey("escape",KEY_ESCAPE);

lastX = input:GetMouseX();
lastY = input:GetMouseY();
mouseSensitivity = 0.1
Distance = 20.0
moveSpeed = 100

thirdPerson = false

function MouseMoveFunc(dt)
	local camera = scene:GetCamera();
	xPos = input:GetMouseX();
	yPos = input:GetMouseY();
	
	xoffset = (xPos - lastX)
	yoffset = (lastY - yPos)

	lastX = xPos
	lastY = yPos
	camDistance();
	ThirdPersonCamera(xoffset,yoffset);
	camera:UpdateCameraVectors();
end

function camDistance()
	scrollOffset = input:GetScrollOffset();
	Distance = Distance - scrollOffset;
	if (Distance < 3.0)
	then
		Distance = 3.0;
	end
	if (Distance > 45.0)
	then
		Distance = 45.0;
	end
end

function FirstPersonCamera( xoffset, yoffset )
	local camera = scene:GetCamera();
	xoffset = xoffset * mouseSensitivity
	yoffset = yoffset * mouseSensitivity

	camera.Yaw =  camera.Yaw + xoffset
	camera.Pitch = camera.Pitch + yoffset

	if(camera.Pitch > 89.0)
	then
		camera.Pitch = 89.0
	end
	if(camera.Pitch < -89.0)
	then
		camera.Pitch = -89.0
	end

end


function ThirdPersonCamera(xoffset, yoffset)
	local camera = scene:GetCamera();
	xoffset = xoffset * mouseSensitivity
	yoffset = yoffset * mouseSensitivity

	camera.Yaw =  camera.Yaw - xoffset
	camera.Pitch = camera.Pitch - yoffset

	if (camera.Pitch < -89.0)
	then
		camera.Pitch = -89.0;
	end
	
	if (camera.Pitch > 0.0)
	then
		camera.Pitch = 0.0;
	end

	CalaulateCamPos();
end


function CalaulateCamPos()
	local camera = scene:GetCamera();
	yaw = camera.Yaw - 90.0;

	pitch = -camera.Pitch;

	x = Distance * math.cos(math.rad(pitch)) * math.sin(math.rad(-yaw));
	y = Distance * math.sin(math.rad(pitch));
	z = Distance * math.cos(math.rad(pitch)) * math.cos(math.rad(yaw));

	local player = scene:GetObject("Player")
	
	camera.position.x = player.position.x + -x;
	camera.position.y = player.position.y + y;
	camera.position.z = player.position.z + -z;
end


function TestInputFunc(dt)

	local player = scene:GetObject("Player");
	local camera = scene:GetCamera();

	velocity = dt * moveSpeed
	
	if(input:GetKeyState("escape"))
	then
		--todo:splash screen
		CloseWindow(true);
	end
	speed = 5;
	if(input:GetKeyState("forward"))
	then
		local dir = vec3:new(1,0,0):multiply(-speed);
		player.rigidBody:ApplyForceLocal(dir)
	end
		
	if(input:GetKeyState("backward"))
	then
		local dir = vec3:new(1,0,0):multiply(speed);
		player.rigidBody:ApplyForceLocal(dir)
	end
		
	if(input:GetKeyState("left"))
	then
		local dir = vec3:new(0,1,0):multiply(speed);
		player.rigidBody:ApplyTorqueLocal(dir)
	end
		
	if(input:GetKeyState("right"))
	then
		local dir = vec3:new(0,1,0):multiply(-speed);
		player.rigidBody:ApplyTorqueLocal(dir)
	end
	
end