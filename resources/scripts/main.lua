--dofile("resources/scripts/inputs.lua")
dofile("resources/scripts/menu.lua")

function init()
	print("init lua");


	resources:LoadTexture("grass","resources/textures/terrain/grass.png");
	print("End Init");
end

function update(deltaTime)
	

	draw_menu();
	

end


