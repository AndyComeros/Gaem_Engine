
dofile("resources/scripts/keybinds.lua")

input:SetMouseLock(false);

input:BindKey("forward",KEY_W);
input:BindKey("backward",KEY_S);
input:BindKey("left",KEY_A);
input:BindKey("right",KEY_D);


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

	if(thirdPerson)
	then
		ThirdPersonCamera(xoffset,yoffset)
	else
		FirstPersonCamera(xoffset,yoffset)
	end

	camera:UpdateCameraVectors();
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
	
	if(thirdPerson)
	then
		if(input:GetKeyState("forward"))
		then
			player.position.z = player.position.z + velocity
			player.rotation.y = 90.0
		end
		
		if(input:GetKeyState("backward"))
		then
			player.position.z = player.position.z - velocity
			player.rotation.y = -90.0
		end
		
		if(input:GetKeyState("left"))
		then
			player.position.x = player.position.x + velocity
			player.rotation.y = 180.0
		end
		
		if(input:GetKeyState("right"))
		then
			player.position.x = player.position.x - velocity
			player.rotation.y = 0.0
		end
	else
		if(input:GetKeyState("forward"))
		then
			camera.position.x =  camera.position.x + (camera.front.x * velocity);
			camera.position.y =  camera.position.y + (camera.front.y * velocity);
			camera.position.z =  camera.position.z + (camera.front.z * velocity);										   
		end															   
																	   
		if(input:GetKeyState("backward"))							   
		then														   
			camera.position.x =  camera.position.x - (camera.front.x * velocity);
			camera.position.y =  camera.position.y - (camera.front.y * velocity);
			camera.position.z =  camera.position.z - (camera.front.z * velocity);
		end															   
																	   
		if(input:GetKeyState("left"))								   
		then				
			print(camera.right.x);
			camera.position.x =  camera.position.x - (camera.right.x * velocity);
			print("test");	
			camera.position.y =  camera.position.y - (camera.right.y * velocity);
			camera.position.z =  camera.position.z - (camera.right.z * velocity);
		end															   
																	   
		if(input:GetKeyState("right"))								   
		then														   
			camera.position.x =  camera.position.x + (camera.right.x * velocity);
			camera.position.y =  camera.position.y + (camera.right.y * velocity);
			camera.position.z =  camera.position.z + (camera.right.z * velocity);
		end
	end
end