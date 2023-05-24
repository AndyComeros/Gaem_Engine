--dofile("resources/scripts/inputs.lua")

function init()
	print("init lua");
		
	resources:LoadTexture("grass","resources/textures/terrain/grass.png");
	print("End Init");
end

function update(deltaTime)
	
	GUI:Start(false);
	--GUI:Tab(500);
	--GUIRenderer::Image(const std::string texture, float width, float height, float alignX, float alignY)
		
	GUI:Text("Hello world!",0.5);
	--GUI:SetCursorPosY(0);
	--Button(const std::string label, float alignment, float width, float height)

	if (GUI:Image("grass", 200, 200, 0.5, 0.5))
	then
		print("press!");
	end

	GUI:End();

end


