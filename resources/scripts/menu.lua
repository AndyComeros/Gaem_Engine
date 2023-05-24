
--current menu in use
current_menu = 1;

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

	if(GUI:Button("Start Game",0.5, 200, 40))
	then
		current_menu = 4;
	end

	if(GUI:Button("Load Game",0.5, 200, 40))
	then
		current_menu = 2;
	end

	if(GUI:Button("Options",0.5, 200, 40))
	then
		current_menu = 3;
	end

	if(GUI:Button("Exit",0.5, 200, 40))
	then
		engine:Shutdown();
	end

	GUI:End();
end


function draw_save_menu()

	GUI:Start(true);

	GUI:Tab(300);
	GUI:Text("Choose a save to load:",0.5);
	GUI:Tab(10);

	saves = loader:GetSaves("resources/saves");

	if(GUI:Button("Save Current Game",0.5, 200, 40))
	then
		loader:SaveScene(engine.scene,"resources/saves/save"..(#saves + 1)..".json");
	end

	
	for i, v in ipairs(saves)
	do
		if(GUI:Button(v, 0.5, 200, 40))
		then
			print(v);
		end
    end
	GUI:Tab(30);

	if(GUI:Button("Back",0.5, 200, 40))
	then
		current_menu = 1;
	end

	GUI:End();
end

function draw_options_menu()

	GUI:Start(true);

	GUI:Tab(300);
	GUI:Text("Options",0.5);

	if(GUI:Button("Back",0.5, 200, 40))
	then
		current_menu = 1;
	end

	GUI:End();
end

function draw_ingame()

	GUI:Start(false);

	GUI:Text("in-game",0.5);
	local fps = math.floor(renderer:GetFPS() + 0.5); 
	GUI:Text((fps.."fps"),0.5);

	GUI:End();
end
