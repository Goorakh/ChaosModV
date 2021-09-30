/*
	Effect by Last0xygen, modified by Reguas
*/

#include <stdafx.h>
#include "Memory/Hooks/ScriptThreadRunHook.h"
#include "PlayerBlimpStrats.h"

void BlimpStrats_Start(bool isFake)
{
	bool cutscenePlaying = IS_CUTSCENE_PLAYING();

	Hash blimpHash = GET_HASH_KEY("blimp");

	LoadModel(blimpHash);
	
	if (!cutscenePlaying)
	{
		REQUEST_CUTSCENE("fbi_1_int", 8);
	}
	
	if (!isFake)
	{
		Hooks::EnableScriptThreadBlock();
	}

	for (int i = 0; i < g_MetaInfo.m_fChaosMultiplier; i++)
	{
		Vehicle veh = CREATE_VEHICLE(blimpHash, -370.490, 1029.085, 345.090, 53.824, true, false, false);
		SET_VEHICLE_ENGINE_ON(veh, true, true, false);
		Ped player = PLAYER_PED_ID();

		if (!isFake)
		{
			SET_ENTITY_INVINCIBLE(player, true);
		}

		SET_PED_INTO_VEHICLE(player, veh, -1);
		SET_VEHICLE_FORWARD_SPEED(veh, 45);
		TASK_LEAVE_VEHICLE(player, veh, 4160);

		int waited = 0;

		while (!IS_PED_GETTING_UP(player) && waited < 100)
		{
			WAIT(100);
			waited++;
		}

		if (!isFake)
		{
			SET_ENTITY_INVINCIBLE(player, false);
		}

		if (!cutscenePlaying)
		{
			while (!HAS_CUTSCENE_LOADED()) // for proper cutscene play
			{
				WAIT(100);
			}

			REGISTER_ENTITY_FOR_CUTSCENE(player, "MICHAEL", 0, 0, 64);

			START_CUTSCENE(0);
			WAIT(8500);
			STOP_CUTSCENE_IMMEDIATELY();

			if (i + 1 == g_MetaInfo.m_fChaosMultiplier)
			{
				REMOVE_CUTSCENE();
			}
		}

		if (i + 1 < g_MetaInfo.m_fChaosMultiplier)
		{
			WAIT(3000);
		}
	}


	if (!isFake)
	{
		Hooks::DisableScriptThreadBlock();
	}
}

static void OnStart()
{
	BlimpStrats_Start(false);
}

static RegisterEffect registerEffect(EFFECT_PLAYER_BLIMP_STRATS, OnStart, nullptr, nullptr, EffectInfo
    {
        .Name = "Blimp Strats",
        .Id = "player_blimp_strats",
        .EEffectGroupType = EEffectGroupType::Teleport
    }
);
