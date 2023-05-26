


----------------------------------------------------------
				--ATTACK STATE FUNCTIONS--
----------------------------------------------------------
function attack_enter(ent)
	ent:GetDrawItem():Animate("attack");
	
end

function attack_update(ent)
	
	ent:LookAt(Player.position);
	print(Player:GetData("health"));
	
end

function attack_exit(ent)
	
end

function attack_message(ent)
	
end
----------------------------------------------------------


----------------------------------------------------------
				--GLOBAL ENEMY STATE FUNCTIONS--
----------------------------------------------------------
atkrange = 10;

function global_enter(ent)
	
end

function global_update(ent)

	local playerDist = Length(Player.position - ent.position);
	if(playerDist < atkrange)
	then
		ent.stateMachine:ChangeState(attack_state);
	else
		ent.stateMachine:ChangeState(state_chase);
	end
		
end

function global_exit(ent)
	
end

function global_message(ent)
	
end
----------------------------------------------------------

print("end script states");