


----------------------------------------------------------
				--ATTACK STATE FUNCTIONS--
----------------------------------------------------------
attackDelay = 0.5;
function attack_enter(ent, dt)
	ent:GetDrawItem():Animate("attack");

	Sound:playSound("grunt",camera.position);

	if(not ent:HasData("lastAttack"))
	then
		ent:AddData("lastAttack",0);
	end
end

function attack_update(ent, dt)

	local playerDist = Length(Player.position - ent.position);
	local newLAttack = ent:GetData("lastAttack") + dt;
	ent:AddData("lastAttack",newLAttack);

	if(newLAttack > attackDelay and playerDist < 10)
	then
		Sound:playSound("hitcar",camera.position);
		ent:AddData("lastAttack",0);
		Player:AddData("health", Player:GetData("health") - 1);
		print(Player:GetData("health"));
	end

	ent:LookAt(Player.position);

end

function attack_exit(ent, dt)
	
end

function attack_message(ent, dt)
	
end
----------------------------------------------------------


----------------------------------------------------------
				--GLOBAL ENEMY STATE FUNCTIONS--
----------------------------------------------------------
atkrange = 10;

function global_enter(ent, dt)
	
end

function global_update(ent, dt)
	
	local playerDist = Length(Player.position - ent.position);
	if(playerDist < atkrange)
	then
		ent.stateMachine:ChangeState(attack_state);
	else
		ent.stateMachine:ChangeState(state_chase);
	end
		
end

function global_exit(ent, dt)
	
end

function global_message(ent, dt)
	
end
----------------------------------------------------------

print("end script states");