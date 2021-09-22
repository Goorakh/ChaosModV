/*
	Effect by Moxi
*/

#include <stdafx.h>

static Object monsterHead = 0;

static void OnTick()
{
	Ped player = PLAYER_PED_ID();

	if (!monsterHead)
	{
		static const Hash monsterHash = GET_HASH_KEY("sum_prop_ac_monstermask_01a");
		LoadModel(monsterHash);

		int bone = GET_PED_BONE_INDEX(player, 0x60F2);
		Vector3 playerPos = GET_ENTITY_COORDS(player, false);

		monsterHead = CREATE_OBJECT(monsterHash, playerPos.x, playerPos.y + 2, playerPos.z, true, false, false);
		ATTACH_ENTITY_TO_ENTITY(monsterHead, player, bone, 0.36, 0.1, -0.01, 180, -90, 0, true, false, false, false, 0, true);
		SET_MODEL_AS_NO_LONGER_NEEDED(monsterHash);
	}
	else if (!IS_ENTITY_ATTACHED_TO_ENTITY(monsterHead, player))
	{
		int bone = GET_PED_BONE_INDEX(player, 0x60F2);
		ATTACH_ENTITY_TO_ENTITY(monsterHead, player, bone, 0.36, 0.1, -0.01, 180, -90, 0, true, false, false, false, 0, true);
	}
}

static void OnStop()
{
	if (monsterHead)
	{
		DELETE_ENTITY(&monsterHead);
	}

	monsterHead = 0;
}

static RegisterEffect registerEffect(EFFECT_PLAYER_MONSTER_HEAD, nullptr, OnStop, OnTick, EffectInfo
	{
		.Name = "Monster Head",
		.Id = "player_monster_head",
		.IsTimed = true
	}
);