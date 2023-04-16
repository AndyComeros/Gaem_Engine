
	dofile("resources/scripts/keybinds.lua")

	input:SetMouseLock(false);

	input:BindKey("forward",KEY_W);
	input:BindKey("backward",KEY_S);
	input:BindKey("left",KEY_A);
	input:BindKey("right",KEY_D);


	lastX = input:GetMouseX();
	lastY = input:GetMouseY();

	function MouseMoveFunc(dt)


		
	end

	function TestInputFunc(dt)
	
		camera = scene:GetCamera();

		if(input:GetKeyState("forward"))
		then
			camera.position.z = scene:GetCamera().position.z + dt * 100
		end

		if(input:GetKeyState("backward"))
		then
			camera.position.z = scene:GetCamera().position.z - dt * 100
		end

		if(input:GetKeyState("left"))
		then
			camera.position.x = scene:GetCamera().position.x + dt * 100	
		end

		if(input:GetKeyState("right"))
		then
			camera.position.x = scene:GetCamera().position.x - dt * 100	
		end
	end