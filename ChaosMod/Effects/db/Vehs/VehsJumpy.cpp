#include <stdafx.h>

static void OnTick()
{
	static int lastTick = GET_GAME_TIMER();
	int curTick = GET_GAME_TIMER();

	Vehicle playerVeh = GET_VEHICLE_PED_IS_IN(PLAYER_PED_ID(), false);
	if (lastTick < curTick - 50)
	{
		lastTick = curTick;

		for (Vehicle veh : GetAllVehs())
		{
			if (veh != playerVeh && !IS_ENTITY_IN_AIR(veh))
			{
				Memory::ApplyForceToEntity(veh, 0, .0f, .0f, 500.f * g_MetaInfo.m_fChaosMultiplier, 0.f, 0.f, 0.f, 0, true, false, true, true, true);
			}
		}
	}
}

static RegisterEffect registerEffect(EFFECT_JUMPY_VEHS, nullptr, nullptr, OnTick, EffectInfo
	{
		.Name = "Jumpy Vehicles",
		.Id = "vehs_jumpy",
		.IsTimed = true,
		.IsShortDuration = true
	}
);