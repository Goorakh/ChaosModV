/*
	Effect by Gorakh
*/

#include <stdafx.h>
#include "../vendor/scripthookv/inc/enums.h"

static constexpr float MOVE_SPEED = 50.f;

static std::vector<int> forwardControls = { eControl::ControlVehicleAccelerate };
static std::vector<int> backwardControls = { eControl::ControlVehicleBrake };

static std::vector<int> upControls = { eControl::ControlJump };
static std::vector<int> downControls = { eControl::ControlDuck };

static std::vector<int> rightControls = { eControl::ControlMoveRightOnly };
static std::vector<int> leftControls = { eControl::ControlMoveLeftOnly };

static Entity lastPlayer;

static void OnStart()
{
	lastPlayer = 0;
}

static float GetMovement(std::vector<int> positiveControls, std::vector<int> negativeControls)
{
	float movement = 0.f;
	for (size_t i = 0; i < positiveControls.size(); i++)
	{
		if (IS_CONTROL_PRESSED(0, positiveControls[i]))
		{
			movement += 1.f;
			break;
		}
	}

	for (size_t i = 0; i < negativeControls.size(); i++)
	{
		if (IS_CONTROL_PRESSED(0, negativeControls[i]))
		{
			movement -= 1.f;
			break;
		}
	}

	return movement;
}

static void SetEntityInNoclipMode(Entity entity, bool enable)
{
	SET_ENTITY_COLLISION(entity, !enable, !enable);
	SET_ENTITY_COMPLETELY_DISABLE_COLLISION(entity, !enable, !enable);
	SET_ENTITY_HAS_GRAVITY(entity, !enable);

	// Nugde object so it "wakes up" and doesn't just keep floating in the air
	Memory::ApplyForceToEntityCenterOfMass(entity, 0, 0.f, 0.f, 0.f, false, false, false, false);
}

static void OnTick()
{
	Entity player = PLAYER_PED_ID();
	if (IS_PED_IN_ANY_VEHICLE(player, false))
	{
		player = GET_VEHICLE_PED_IS_IN(player, false);
	}

	SetEntityInNoclipMode(player, true);

	if (lastPlayer && DOES_ENTITY_EXIST(lastPlayer) && player != lastPlayer)
	{
		SetEntityInNoclipMode(lastPlayer, false);
	}
	
	Vector3 forward, right, up;
	Util::GetGameplayCamMatrix(&forward, &right, &up);

	Vector3 velocity = (right * GetMovement(rightControls, leftControls)) + (forward * GetMovement(forwardControls, backwardControls)) + (up * GetMovement(upControls, downControls));

	velocity = (velocity / velocity.Length()) * (IS_ENTITY_A_VEHICLE(player) ? GET_VEHICLE_ESTIMATED_MAX_SPEED(player) : MOVE_SPEED) * (IS_CONTROL_PRESSED(0, eControl::ControlSprint) ? 2 : 1);
	SET_ENTITY_VELOCITY(player, velocity.x, velocity.y, velocity.z);

	if (IS_ENTITY_A_VEHICLE(player))
	{
		Vector3 rotation = GET_GAMEPLAY_CAM_ROT(2);
		SET_ENTITY_ROTATION(player, rotation.x, rotation.y, rotation.z, 2, true);
	}

	invoke<Void>(0x8339643499D1222E, player, 0.f, 0.f, 0.f); // _SET_ENTITY_ANGULAR_VELOCITY

	lastPlayer = player;
}

static void OnStop()
{
	SetEntityInNoclipMode(lastPlayer, false);

	//Vector3 coords = GET_ENTITY_COORDS(lastPlayer, 0);
	//SET_ENTITY_COORDS(lastPlayer, coords.x, coords.y, coords.z, false, false, false, false);
}

static RegisterEffect registerEffect(EFFECT_PLAYER_NOCLIP, OnStart, OnStop, OnTick, EffectInfo
	{
		.Name = "Noclip",
		.Id = "player_noclip",
		.IsTimed = true
	}
);