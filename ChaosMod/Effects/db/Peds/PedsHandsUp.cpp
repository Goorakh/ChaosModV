#include <stdafx.h>

/*
 * Effect by Juhana
 */

static void OnStart()
{
	for (Ped ped : GetAllPeds())
	{
		if (!IS_PED_DEAD_OR_DYING(ped, true))
		{
			TASK_HANDS_UP(ped, 5000 * MetaModifiers::m_fChaosMultiplier, 0, -1, true);
			SET_PED_DROPS_WEAPON(ped);
		}
	}
}

static RegisterEffect registerEffect(EFFECT_PEDS_HANDS_UP, OnStart, EffectInfo
	{
		.Name = "Hands Up!",
		.Id = "peds_hands_up"
	}
);
