#include <stdafx.h>

/*
	Effect by Gorakh
*/

#define MIN_ANGLE_DIFF 20.f

static float GetRandomAngleDiff()
{
	return g_Random.GetRandomFloat(MIN_ANGLE_DIFF, 360.f - MIN_ANGLE_DIFF) - 180.f;
}

static void OnStart()
{
	Ped player = PLAYER_PED_ID();

	Entity playerEntity;
	if (IS_PED_IN_ANY_VEHICLE(player, false))
	{
		playerEntity = GET_VEHICLE_PED_IS_IN(player, false);
	}
	else
	{
		playerEntity = player;
	}

	Vector3 playerVelocity = GET_ENTITY_VELOCITY(playerEntity);
	float playerSpeed = playerVelocity.Length();

	float newOrientation = GET_ENTITY_HEADING(playerEntity) + GetRandomAngleDiff();

	if (newOrientation > 180.f)
		newOrientation -= 360.f;
	if (newOrientation < -180.f)
		newOrientation += 360.f;

	SET_ENTITY_HEADING(playerEntity, newOrientation);

	//Vector3 newPlayerVelocity = playerVelocity;
	//newPlayerVelocity.z =
	//SET_ENTITY_VELOCITY(playerEntity, )
}

static RegisterEffect registerEffect(EFFECT_PLAYER_LAUNCH, OnStart, EffectInfo
	{
		.Name = "Redirect Player",
		.Id = "player_redirect"
	}
);