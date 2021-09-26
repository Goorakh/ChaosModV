#include <stdafx.h>

static void OnStop()
{
	for (auto veh : GetAllVehs())
	{
		SET_VEHICLE_REDUCE_GRIP(veh, false);
		SET_VEHICLE_FRICTION_OVERRIDE(veh, 1.f);
	}
}

static void OnTick()
{
	for (auto veh : GetAllVehs())
	{
		static int counter = 0;
		static bool toggle = true;

		SET_VEHICLE_REDUCE_GRIP(veh, toggle);
		SET_VEHICLE_FRICTION_OVERRIDE(veh, 0.4f / g_MetaInfo.m_fChaosMultiplier);

		if (++counter > g_MetaInfo.m_fChaosMultiplier)
		{
			toggle = false;
			counter = 0;
		}
		else
		{
			toggle = true;
		}
	}
}

static RegisterEffect registerEffect(EFFECT_SLIPPERY_VEHS, nullptr, OnStop, OnTick, EffectInfo
	{
		.Name = "Slippery Vehicles",
		.Id = "vehs_slippery",
		.IsTimed = true
	}
);