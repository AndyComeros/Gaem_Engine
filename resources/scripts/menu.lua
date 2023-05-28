
--load menu texutres
resources:LoadTexture("driver"	,"resources/textures/GUI/DRIVE.png");
resources:LoadTexture("exlr8"	,"resources/textures/GUI/exlr8.png");
resources:LoadTexture("friction","resources/textures/GUI/friction.png");
resources:LoadTexture("gas"		,"resources/textures/GUI/GAS.png");

resources:LoadTexture("exit"		,"resources/textures/exit.png");



--current menu in use
current_menu = 1;

--gui aesthetics
buttonWidth = 300;
buttonHeight = 50;

--array each menu with assigned index
local cases = {
	[1] = function()
		input:SetMouseLock(true);
		engine:SetSimulation(false);
		draw_main_menu();
	end,
	[2] = function()
		input:SetMouseLock(true);
		engine:SetSimulation(false);
		draw_save_menu();
	end,
	[3] = function()
		input:SetMouseLock(true);
		engine:SetSimulation(false);
		draw_options_menu();
	end,
	[4] = function()
		input:SetMouseLock(false);
		engine:SetSimulation(true);
		draw_ingame();
	end,
	[5] = function()
		input:SetMouseLock(true);
		engine:SetSimulation(false);
		draw_window_option();
	end,
	[6] = function()
		input:SetMouseLock(true);
		engine:SetSimulation(false);
		draw_exit();
	end,
	[7] = function()
		input:SetMouseLock(true);
		engine:SetSimulation(false);
		draw_lose();
	end
}

--called every update, renders current menu
function draw_menu()
	if(cases[current_menu])
	then
		cases[current_menu]();
	end;	
end


function draw_main_menu()

	GUI:Start(true);
	GUI:Tab(300);
	GUI:Text("Main Menu",0.5);

	GUI:Tab(10);

	if(GUI:Button("Start Game",0.5, buttonWidth, buttonHeight))
	then
		Sound:playSound("click",camera.position);
		current_menu = 4;
	end

	if(GUI:Button("Load Game",0.5, buttonWidth, buttonHeight))
	then
		Sound:playSound("click",camera.position);
		current_menu = 2;
	end

	if(GUI:Button("Options",0.5, buttonWidth, buttonHeight))
	then
		Sound:playSound("click",camera.position);
		current_menu = 3;
	end

	if(GUI:Button("Exit",0.5, buttonWidth, buttonHeight))
	then
		Sound:playSound("click",camera.position);
		current_menu = 6
	end

	GUI:End();
end


function draw_save_menu()

	GUI:Start(true);

	GUI:Tab(300);
	GUI:Text("Save Current Game",0.5);
	GUI:Tab(20);

	saves = loader:GetSaves("resources/saves");

	if(GUI:Button("--Save--",0.5, buttonWidth, buttonHeight))
	then
		Sound:playSound("click",camera.position);
		loader:SaveScene(engine.scene,"resources/saves/save"..(#saves + 1)..".json");
	end
	GUI:Tab(20);
	GUI:Text("Choose a save to load:",0.5);
	GUI:Tab(10);
	for i, v in ipairs(saves)
	do
		if(GUI:Button(v, 0.5, buttonWidth, buttonHeight))
		then
			Sound:playSound("click",camera.position);
			nscene = loader:LoadScene("resources/saves/"..v);
			engine:SwitchScenes(nscene);
		end
    end
	GUI:Tab(30);

	if(GUI:Button("Back",0.5, buttonWidth, buttonHeight))
	then
		Sound:playSound("click",camera.position);
		current_menu = 1;
	end

	GUI:End();
end

function draw_options_menu()

	GUI:Start(true);

	GUI:Tab(300);
	GUI:Text("Options",0.5);
	GUI:Tab(10);
	if(GUI:Button("Window Options",0.5, buttonWidth, buttonHeight))
	then
		Sound:playSound("click",camera.position);
		current_menu = 5;
	end

	if(GUI:Button("Back",0.5, buttonWidth, buttonHeight))
	then
		Sound:playSound("click",camera.position);
		current_menu = 1;
	end

	GUI:End();
end

function draw_ingame()

	GUI:Start(false);

	GUI:Image("gas",300,300,0.9,0)
	
	GUI:Text("Health: " .. math.floor(Player:GetData("health")), 0.9);
	GUI:Text("Score: " ..  math.floor(Player:GetData("score")), 0.9);
	GUI:Text("Boost: " ..  math.floor(Player:GetData("boost") + 1), 0.9);

	
	GUI:SetCursorPosX(0)
	GUI:SetCursorPosY(0)
	GUI:Text("in-game",0.5);
	local fps = math.floor(renderer:GetFPS() + 0.5); 
	GUI:Text((fps.."fps"),0.5);

	GUI:End();
end

function draw_window_option()

	GUI:Start(true);
	GUI:Tab(300);
	GUI:Text("Change Window Mode",0.5);
	GUI:Tab(10);


	if(GUI:Button("Windowed",0.5, buttonWidth, buttonHeight))
	then
		Sound:playSound("click",camera.position);
		engine:SetWindowType(1);
	end
	if(GUI:Button("Borderless",0.5, buttonWidth, buttonHeight))
	then
		Sound:playSound("click",camera.position);
		engine:SetWindowType(2);
	end
	if(GUI:Button("Full Screen",0.5, buttonWidth, buttonHeight))
	then
		Sound:playSound("click",camera.position);
		engine:SetWindowType(3);
	end

	if(GUI:Button("Back",0.5, buttonWidth, buttonHeight))
	then
		Sound:playSound("click",camera.position);
		current_menu = 3;
	end

	GUI:End();
end

function draw_exit()

	GUI:Start(true);

	if(GUI:ImageButton("exit",500,500,0.5,0.5))
	then
		engine:Shutdown();
	end
	
	GUI:Tab(10);

	if(GUI:Button("Back",0.5, buttonWidth, buttonHeight))
	then
		Sound:playSound("click",camera.position);
		current_menu = 1;
	end

	GUI:End();
end

function draw_lose()

	GUI:Start(true);

	GUI:Tab(300);
	GUI:Text("YOU DIED",0.5);

	if(GUI:Button("Back",0.5, buttonWidth, buttonHeight))
	then
		Sound:playSound("click",camera.position);
		current_menu = 1;
	end

	GUI:End();
end