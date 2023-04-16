
	dofile("resources/scripts/keybinds.lua")

	input:BindKey("forward",KEY_W);
	input:BindKey("backward",KEY_S);
	input:BindKey("left",KEY_A);
	input:BindKey("right",KEY_D);

	function TestInputFunc()
		
		if(input:GetKeyState("forward"))
		then
			print("FORWARDS!")	
		end

		if(input:GetKeyState("backward"))
		then
			print("BACKWARDS!")	
		end

		if(input:GetKeyState("left"))
		then
			print("LEFT!")	
		end

		if(input:GetKeyState("right"))
		then
			print("RIGHT!")	
		end
	end