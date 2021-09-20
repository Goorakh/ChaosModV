/*
	Effect by Last0xygen, modified
*/

#include <stdafx.h>

static void OnStart()
{
	for (int i = 0; i < g_MetaInfo.m_fChaosMultiplier; i++)
	{
		ReplacePlayerVehicle();

		if ((i + 1) < g_MetaInfo.m_fChaosMultiplier)
		{
			WAIT(4000);
		}
	}
}

static RegisterEffect registerEffect(EFFECT_VEH_REPLACEVEHICLE, OnStart, EffectInfo
	{
		.Name = "Replace Current Vehicle",
		.Id = "misc_replacevehicle"
	}
);