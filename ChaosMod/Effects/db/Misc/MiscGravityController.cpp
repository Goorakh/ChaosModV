#include <stdafx.h>

static void OnStop()
{
	SET_GRAVITY_LEVEL(0);
}

static void OnTickLow()
{
	// Multiplier = 1: GravityLevel = 1
	// Multiplier = 2: GravityLevel = 2
	SET_GRAVITY_LEVEL(min(g_MetaInfo.m_fChaosMultiplier, 3));
}

static RegisterEffect registerEffect1(EFFECT_LOW_GRAV, nullptr, OnStop, OnTickLow, EffectInfo
	{
		.Name = "Low Gravity",
		.Id = "lowgravity",
		.IsTimed = true,
		.IsShortDuration = true,
		.IncompatibleWith = { EFFECT_VERY_LOW_GRAV, EFFECT_INSANE_GRAV, EFFECT_INVERT_GRAV, EFFECT_SIDEWAYS_GRAVITY }
	}
);
static void OnTickVeryLow()
{
	// Multiplier = 1: GravityLevel = 2
	// Multiplier = 2: GravityLevel = 3
	SET_GRAVITY_LEVEL(min(1 + g_MetaInfo.m_fChaosMultiplier, 3));
}

static RegisterEffect registerEffect2(EFFECT_VERY_LOW_GRAV, nullptr, OnStop, OnTickVeryLow, EffectInfo
	{
		.Name = "Very Low Gravity",
		.Id = "verylowgravity",
		.IsTimed = true,
		.IsShortDuration = true,
		.IncompatibleWith = { EFFECT_LOW_GRAV, EFFECT_INSANE_GRAV, EFFECT_INVERT_GRAV, EFFECT_SIDEWAYS_GRAVITY }
	}
);
static void OnTickInsane()
{
	Memory::SetGravityLevel(200.f * g_MetaInfo.m_fChaosMultiplier);

	for (auto ped : GetAllPeds())
	{
		if (!IS_PED_IN_ANY_VEHICLE(ped, false))
		{
			SET_PED_TO_RAGDOLL(ped, 1000, 1000, 0, true, true, false);

			APPLY_FORCE_TO_ENTITY_CENTER_OF_MASS(ped, 0, 0, 0, -75.f * g_MetaInfo.m_fChaosMultiplier, false, false, true, false);
		}
	}

	for (auto object : GetAllProps())
	{
		APPLY_FORCE_TO_ENTITY_CENTER_OF_MASS(object, 0, 0, 0, -200.f * g_MetaInfo.m_fChaosMultiplier, false, false, true, false);
	}
}

static RegisterEffect registerEffect3(EFFECT_INSANE_GRAV, nullptr, OnStop, OnTickInsane, EffectInfo
	{
		.Name = "Insane Gravity",
		.Id = "insanegravity",
		.IsTimed = true,
		.IsShortDuration = true,
		.IncompatibleWith = { EFFECT_LOW_GRAV, EFFECT_VERY_LOW_GRAV, EFFECT_INVERT_GRAV, EFFECT_SIDEWAYS_GRAVITY }
	}
);
static void OnStartInvert()
{
	GIVE_WEAPON_TO_PED(PLAYER_PED_ID(), GET_HASH_KEY("WEAPON_PARACHUTE"), 9999, true, true);
}

static void OnTickInvert()
{
	Memory::SetGravityLevel(-9.8f * g_MetaInfo.m_fChaosMultiplier);

	for (auto ped : GetAllPeds())
	{
		if (!IS_PED_IN_ANY_VEHICLE(ped, false))
		{
			SET_PED_TO_RAGDOLL(ped, 1000, 1000, 0, true, true, false);
		}
	}

	// If this isn't done, the gravity for props and vehicles won't update
	for (auto object : GetAllProps())
	{
		APPLY_FORCE_TO_ENTITY_CENTER_OF_MASS(object, 0, 0, 0, 0.f, false, false, true, false);
	}

	for (auto veh : GetAllVehs())
	{
		APPLY_FORCE_TO_ENTITY_CENTER_OF_MASS(veh, 0, 0, 0, 0.f, false, false, true, false);
	}
}

static RegisterEffect registerEffect4(EFFECT_INVERT_GRAV, OnStartInvert, OnStop, OnTickInvert, EffectInfo
	{
		.Name = "Invert Gravity",
		.Id = "invertgravity",
		.IsTimed = true,
		.IsShortDuration = true,
		.IncompatibleWith = { EFFECT_LOW_GRAV, EFFECT_VERY_LOW_GRAV, EFFECT_INSANE_GRAV, EFFECT_SIDEWAYS_GRAVITY }
	}
);

Vector3 sidewaysGravityForce;
static void OnStartSideways()
{
	// Z is 0 since we don't want any upwards or downwards gravity
	sidewaysGravityForce = Vector3(g_Random.GetRandomFloat(-1, 1), g_Random.GetRandomFloat(-1, 1), 0.f);
	sidewaysGravityForce = sidewaysGravityForce / sidewaysGravityForce.Length(); // Normalize the direction
	sidewaysGravityForce = sidewaysGravityForce * 0.5f;
}

static void OnTickSideways()
{
	Memory::SetGravityLevel(0.f);

	Vector3 gravityForce = sidewaysGravityForce * g_MetaInfo.m_fChaosMultiplier;

	for (auto ped : GetAllPeds())
	{
		if (!IS_PED_IN_ANY_VEHICLE(ped, false))
		{
			SET_PED_TO_RAGDOLL(ped, 1000, 1000, 0, true, true, false);

			APPLY_FORCE_TO_ENTITY_CENTER_OF_MASS(ped, 1, gravityForce.x, gravityForce.y, gravityForce.z, false, false, true, false);
		}
	}

	for (auto object : GetAllProps())
	{
		APPLY_FORCE_TO_ENTITY_CENTER_OF_MASS(object, 1, gravityForce.x, gravityForce.y, gravityForce.z, false, false, true, false);
	}

	for (auto veh : GetAllVehs())
	{
		APPLY_FORCE_TO_ENTITY_CENTER_OF_MASS(veh, 1, gravityForce.x, gravityForce.y, gravityForce.z, false, false, true, false);
	}
}

static RegisterEffect registerEffect5(EFFECT_SIDEWAYS_GRAVITY, OnStartSideways, OnStop, OnTickSideways, EffectInfo
	{
		.Name = "Sideways Gravity",
		.Id = "misc_sideways_gravity",
		.IsTimed = true,
		.IsShortDuration = true,
		.IncompatibleWith = { EFFECT_LOW_GRAV, EFFECT_VERY_LOW_GRAV, EFFECT_INVERT_GRAV, EFFECT_INSANE_GRAV }
	}
);