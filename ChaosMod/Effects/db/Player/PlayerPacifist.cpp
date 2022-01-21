#include <stdafx.h>
//Effect by ProfessorBiddle, requested thousands of times on discord

static int lastPlayerKills;

static void OnStart()
{
	lastPlayerKills = -1;
}

static void OnTick()
{
	Ped playerPed = PLAYER_PED_ID();

	Hash playerHash = GET_ENTITY_MODEL(playerPed);

	int allPlayerKills = 0;
	int curKills = 0;
	for (Hash hash : { GET_HASH_KEY("SP0_KILLS"), GET_HASH_KEY("SP1_KILLS"), GET_HASH_KEY("SP2_KILLS")})
	{
		STAT_GET_INT(hash, &curKills, -1);
		allPlayerKills += curKills;
	}

	//check if stat this tick is larger than stat last tick
	if ((g_MetaInfo.m_fChaosMultiplier > 1 && /*78 = is aiming weapon*/ GET_PED_CONFIG_FLAG(playerPed, 78, 1)) || (lastPlayerHits >= 0 && playerHits > lastPlayerHits))
	{
		START_ENTITY_FIRE(playerPed);
		SET_ENTITY_HEALTH(playerPed, 0, 0);
	}
	lastPlayerKills = allPlayerKills;
}
static RegisterEffect registerEffect(EFFECT_PLAYER_PACIFIST, OnStart, nullptr, OnTick, EffectInfo
	{
		.Name = "Pacifist",
		.Id = "player_pacifist",
		.IsTimed = true
	}
);