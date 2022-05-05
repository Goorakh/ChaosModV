/*
	Effect by Gorakh
*/

#include <stdafx.h>

#define GetAlphaFor(ent) (((sin((ent * 20.f) + (GET_GAME_TIMER() / (125.f / MetaModifiers::m_fChaosMultiplier))) + 1.f) / 2.f) * 255.f)

static void OnTick()
{
	for (Ped ped : GetAllPeds())
	{
		SET_ENTITY_ALPHA(ped, GetAlphaFor(ped), false);
	}

	for (Vehicle veh : GetAllVehs())
	{
		SET_ENTITY_ALPHA(veh, GetAlphaFor(veh), false);
	}

	for (Entity prop : GetAllProps())
	{
		SET_ENTITY_ALPHA(prop, GetAlphaFor(prop), false);
	}
}

static void OnStop()
{
	for (Ped ped : GetAllPeds())
	{
		RESET_ENTITY_ALPHA(ped);
	}

	for (Vehicle veh : GetAllVehs())
	{
		RESET_ENTITY_ALPHA(veh);
	}

	for (Entity prop : GetAllProps())
	{
		RESET_ENTITY_ALPHA(prop);
	}
}

static RegisterEffect registerEffect(EFFECT_MISC_GHOST_WORLD, nullptr, OnStop, OnTick, EffectInfo
	{
		.Name = "Ghost Town",
		.Id = "misc_ghost_world",
		.IsTimed = true,
		.IncompatibleWith = { EFFECT_PEDS_INVISIBLE, EFFECT_VEHS_INVISIBLE }
	}
);
