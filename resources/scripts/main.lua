dofile("resources/scripts/inputs.lua")

function init()
print("intit")	

	resources:LoadTexture("RAT", "resources/models/RAT.jpg");
	resources:LoadModel	 ("RAT", "resources/models/RAT.obj","RAT","","");

	lighting = scene:GetLights();
	lighting:SetAmbient(0.1,0.1,0.1);
	lighting:AddDirectionLight(NormalizeVector(vec3.new( -1,0.5,0)),vec3.new( 0.6,0.6,0.6),vec3.new(1,0,0));

	
	RAT = resources:CreateGameObject("Player","RAT","");

	scene:AddObject(RAT);

print("end init")
end

function update(deltaTime)
	
	local Player = scene:GetObject("Player");
	Player:SetRotation(vec3:new(Player.rotation.x,Player.rotation.y + deltaTime * 20 ,Player.rotation.z));

	KeyPressFunc(deltaTime);
	MouseMoveFunc(deltaTime);
end


