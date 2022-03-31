/*
	Effect by Gorakh
*/

#include <stdafx.h>

static void OnTick()
{
	for (Vehicle veh : GetAllVehs())
	{
		_0x5B91B229243351A8(veh, true);
	}
}

static void OnStop()
{
	for (Vehicle veh : GetAllVehs())
	{
		_0x5B91B229243351A8(veh, false);
	}
}

static RegisterEffect registerEffect(EFFECT_VEHS_INVERT_CONTROLS, nullptr, OnStop, OnTick, EffectInfo
	{
		.Name = "Invert Vehicle Controls",
		.Id = "vehs_invert_controls",
		.IsTimed = true
	}
);