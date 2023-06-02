
----------------------------------------------------------
				--EMPTY STATE FUNCTIONS--
----------------------------------------------------------

function empty_enter(ent, dt)
end

function empty_update(ent, dt)
end

function empty_exit(ent, dt)
end

function empty_message(ent, dt)
end
----------------------------------------------------------


----------------------------------------------------------
				--PLAYER STATE FUNCTIONS--
----------------------------------------------------------

function player_enter(ent, dt)
	
end

function player_update(ent, dt)
		
end

function player_exit(ent, dt)
	
end

function player_message(ent, dt)
	
end
----------------------------------------------------------


----------------------------------------------------------
			-- ENEMY ATTACK STATE FUNCTIONS--
----------------------------------------------------------

attackDelay = 0.5;
function attack_enter(ent, dt)

	ent:GetDrawItem():Animate("attack");
	ent.rigidBody:SetLinearVelocity(0,0,0);
	ent.rigidBody:SetAngularVelocity(0,0,0);
	ent.rigidBody:ModType(1);
	--Sound:playSound("grunt",camera.position);

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
		--Sound:playSound("hitcar",camera.position);
		ent:AddData("lastAttack",0);
		Player:AddData("health", Player:GetData("health") - 1);
	end
		
	ent:SetPosition(vec3:new(ent.position.x,terrain:GetHeight(ent.position.x,ent.position.z) - 1,ent.position.z));
	ent:LookAt(Player.position);

end

function attack_exit(ent, dt)

	ent.rigidBody:ModType(3);

end

function attack_message(ent, dt)
	
end
----------------------------------------------------------


----------------------------------------------------------
			--GLOBAL ENEMY STATE FUNCTIONS--
----------------------------------------------------------
atkrange = 6;
hitRange = 5;
hitVelocity = 20;

function global_enter(ent, dt)
	ent:SetPosition(vec3:new(ent.position.x,terrain:GetHeight(ent.position.x,ent.position.z) - 1,ent.position.z));
	ent.rigidBody:SetLinearVelocity(0,0,0);
	ent.rigidBody:SetAngularVelocity(0,0,0);
	ent.rigidBody:ModType(3);
end

function global_update(ent, dt)
	local playerDist = Length(Player.position - ent.position);

	if(playerDist < hitRange and Length(Player.rigidBody:GetLinearVelocity()) > hitVelocity)
	then
		ent.stateMachine:ChangeState(dead_state);
		ent.stateMachine:ChangeGlobalState(empty_state);
		Player:AddData("score", Player:GetData("score") + 1);
	else
		if(playerDist < atkrange)
		then
			ent.stateMachine:ChangeState(attack_state);
		else
			ent.stateMachine:ChangeState(state_chase);
		end
	end

end

function global_exit(ent, dt)
	
end

function global_message(ent, dt)
	
end
----------------------------------------------------------


----------------------------------------------------------
				--DEAD ENEMY STATE FUNCTIONS--
----------------------------------------------------------
respawnTimeMin = 5;
respawnTimeMax = 10;
respawnRadius = 100;
function dead_enter(ent, dt)
	
	ent:StopMoving();

	Sound:playSound("carhit",camera.position);
	ent:GetDrawItem():Animate("fall");

	local respawnTime = math.random(respawnTimeMin, respawnTimeMax) + math.random() 
	ent:AddData("timeToRespawn",respawnTime);

	--modify physics to prevent collisions with other objects
	ent.rigidBody:SetDampeningLinear(0.5);
	ent.rigidBody:ModType(1);

	--Fly away from player in random position
	local force = Player.rigidBody:GetLinearVelocity():multiply(math.random(1,3) + math.random());
	force.y = force.y + 20;
	ent.rigidBody:SetLinearVelocity(force.x,force.y,force.z);
	ent.rigidBody:SetAngularVelocity(math.random(-10,10),math.random(-10,10),math.random(-10,10));

end

function dead_update(ent, dt)

	--simulate gravity for kinematic body
	gravity = vec3:new(0, -9.81, 0)
	gravityForce = gravity:multiply(0.0167);
	newVelocity = ent.rigidBody:GetLinearVelocity() + gravityForce;
	ent.rigidBody:SetLinearVelocity(newVelocity.x,newVelocity.y,newVelocity.z);

	local timeToRespawn = ent:GetData("timeToRespawn");
	ent:AddData("timeToRespawn",ent:GetData("timeToRespawn") - dt);

	if(ent:GetData("timeToRespawn") < 0)
	then
		ent.stateMachine:ChangeGlobalState(global_state);
	end

end

function dead_exit(ent, dt)

	--spawn in random position respawnRadius meters away from playera
	math.randomseed(os.time() * ent:GetID());
	local theta = math.rad(math.random(0,360));
	local xPos = Player.position.x + (respawnRadius * math.cos(theta));
	local zPos = Player.position.z + (respawnRadius * math.sin(theta));
	ent:SetPosition(vec3:new(xPos,0,zPos));

	--return physics properties to normal
	ent.rigidBody:SetDampeningLinear(10);
	ent.rigidBody:ModType(3);
	ent:GetDrawItem():Animate("idle");
end

function dead_message(ent, dt)
	
end
----------------------------------------------------------
print("end script states");