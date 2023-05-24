

local cases = {
	[1] = function()
		draw_main_menu();
	end,
	[2] = function()
		draw_save_menu();
	end,
	[3] = function()
		draw_options_menu();
	end,
	[4] = function()
		draw_ingame();
	end
}

local current_menu = 1;


function draw_menu()

	GUI:Start(false);
	--print("start");
	if(cases[current_menu])
	then
		cases[current_menu]();
	end;
	GUI:End();
	--print("end");
end


function draw_main_menu()
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
end


function draw_save_menu()
	
	GUI:Tab(300);
	GUI:Text("Choose a save to load:",0.5);
	GUI:Tab(10);

	if(GUI:Button("Save Current Game",0.5, 200, 40))
	then
		print("Save!");
	end

	saves = loader:GetSaves("resources/saves");
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

end

function draw_options_menu()

	GUI:Tab(300);
	GUI:Text("Options",0.5);

	if(GUI:Button("Back",0.5, 200, 40))
	then
		current_menu = 1;
	end
end

function draw_ingame()
	GUI:Text("in-game",0.5);
end
