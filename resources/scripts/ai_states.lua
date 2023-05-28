
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
hitRange = 5;
hitVelocity = 20;

function global_enter(ent, dt)
	ent.rigidBody:SetLinearVelocity(vec3:new(0,0,0));
	ent.rigidBody:SetAngularVelocity(vec3:new(0,0,0));
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

	--make sure physics dont go wild
	--ent.rigidBody:SetLinearVelocity(vec3:new(0,0,0));
	--ent.rigidBody:SetAngularVelocity(vec3:new(0,0,0));

end

function global_exit(ent, dt)

end

function global_message(ent, dt)
	
end
----------------------------------------------------------


----------------------------------------------------------
				--DEAD ENEMY STATE FUNCTIONS--
----------------------------------------------------------
respawnTime = 10;

function dead_enter(ent, dt)
	Sound:playSound("carhit",camera.position);
	ent:GetDrawItem():Animate("stand");
	ent:AddData("timeToRespawn",respawnTime);
	ent.rigidBody:ModType(1);
--#define KINE 1
--#define STAT 2
--#define DYNA 3

	local force = Player.rigidBody:GetLinearVelocity():multiply(math.random(1,3) + math.random());
	force.y = force.y + 20;
	--ent.rigidBody:ApplyForce(force);
	--ent.rigidBody:ApplyTorqueLocal(vec3:new(100,100,100));
	ent.rigidBody:SetLinearVelocity(force.x,force.y,force.z);


	math.random(-10,10)
	ent.rigidBody:SetAngularVelocity(math.random(-10,10),math.random(-10,10),math.random(-10,10));


end

function dead_update(ent, dt)
	ent:AddData("timeToRespawn",ent:GetData("timeToRespawn") - dt);
	if(ent:GetData("timeToRespawn") < 0)
	then
		ent.stateMachine:ChangeGlobalState(global_state);
	end

	--simulate gravity for kinematic body
	gravity = vec3:new(0, -9.81, 0)
	gravityForce = gravity:multiply(0.0167);
	newVelocity = ent.rigidBody:GetLinearVelocity() + gravityForce;
	ent.rigidBody:SetLinearVelocity(newVelocity.x,newVelocity.y,newVelocity.z);

	--temp animation
	--ent:SetPosition(vec3:new(ent.position.x,ent.position.y + (dt * 100),ent.position.z));
end

function dead_exit(ent, dt)
	--ent.rigidBody:SetLinearVelocity (0,0,0);
	--ent.rigidBody:SetAngularVelocity(0,0,0);
	--ent:SetRotation(0,0,0);
	--ent.rigidBody:ModType(1);
end

function dead_message(ent, dt)
	
end
----------------------------------------------------------
print("end script states");