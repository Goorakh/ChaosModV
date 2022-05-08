/*
	Effect by Last0xygen, modified
*/

#include <stdafx.h>
#include "Memory/Hooks/ScriptThreadRunHook.h"

static void OnStart()
{
	
	Hooks::EnableScriptThreadBlock();
	bool cutscenePlaying = IS_CUTSCENE_PLAYING();

	static Hash blimpHash = GET_HASH_KEY("blimp");
	static Hash daveHash = GET_HASH_KEY("ig_davenorton");

	LoadModel(blimpHash);
	
	if (!cutscenePlaying)
	{
		REQUEST_CUTSCENE("fbi_1_int", 8);
	}
	
	Ped player = PLAYER_PED_ID();

	Ped pedDave = 0;
	for (size_t i = 0; i < MetaModifiers::m_fChaosMultiplier; i++)
	{
		Vehicle veh = CREATE_VEHICLE(blimpHash, -370.490f, 1029.085f, 345.090f, 53.824f, true, false, false);
		SET_VEHICLE_ENGINE_ON(veh, true, true, false);
		SET_ENTITY_INVINCIBLE(player, true);
		SET_PED_INTO_VEHICLE(player, veh, -1);
		SET_VEHICLE_FORWARD_SPEED(veh, 45);
		TASK_LEAVE_VEHICLE(player, veh, 4160);

		int waited = 0;

		while (!IS_PED_GETTING_UP(player) && waited < 100)
		{
			WAIT(100);
			waited++;
		}

		if (!cutscenePlaying)
		{
			REQUEST_ANIM_DICT("missfbi1leadinout");
			REQUEST_MODEL(daveHash);

			while (!HAS_CUTSCENE_LOADED()) // for proper cutscene play
			{
				WAIT(0);
			}

			REGISTER_ENTITY_FOR_CUTSCENE(player, "MICHAEL", 0, 0, 64);

			START_CUTSCENE(0);
			WAIT(6500);
			STOP_CUTSCENE_IMMEDIATELY();

			REMOVE_CUTSCENE();

			if (i == 0)
			{
				pedDave = CREATE_PED(4, daveHash, -442.2f, 1059.25f, 326.66f, 180.6f, true, false);

				TASK_PLAY_ANIM(pedDave, "missfbi1leadinout", "fbi_1_int_leadin_loop_daven", 8.0f, 1.0f, -1, 1, 0.0f, false, false, false);
				SET_PED_KEEP_TASK(pedDave, true);
			}

			if (i == MetaModifiers::m_fChaosMultiplier - 1)
			{
				SET_PED_AS_NO_LONGER_NEEDED(&pedDave);
			}
		}
	}
	
	SET_ENTITY_INVINCIBLE(player, false);
	Hooks::DisableScriptThreadBlock();
}

static RegisterEffect registerEffect(EFFECT_PLAYER_BLIMP_STRATS, OnStart, nullptr, nullptr, EffectInfo
    {
        .Name = "Blimp Strats",
        .Id = "player_blimp_strats",
        .EEffectGroupType = EEffectGroupType::Teleport
    }
);
