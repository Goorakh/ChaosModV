#include <stdafx.h>

static void OnStart()
{
	static const Hash playerGroup = GET_HASH_KEY("PLAYER");
	static const Hash model = GET_HASH_KEY("cs_bradcadaver");
	static const Hash weapon = GET_HASH_KEY("WEAPON_DOUBLEACTION");

	Ped playerPed = PLAYER_PED_ID();
	Vector3 playerPos = GET_ENTITY_COORDS(playerPed, false);

	Hash relationshipGroup;
	ADD_RELATIONSHIP_GROUP("_ZOMBIE_BRAD", &relationshipGroup);
	SET_RELATIONSHIP_BETWEEN_GROUPS(5, relationshipGroup, playerGroup);

	Ped ped = CreatePoolPed(4, model, playerPos.x, playerPos.y, playerPos.z, 0.f);
	if (IS_PED_IN_ANY_VEHICLE(playerPed, false))
	{
		SET_PED_INTO_VEHICLE(ped, GET_VEHICLE_PED_IS_IN(playerPed, false), -2);
	}

	SET_PED_RELATIONSHIP_GROUP_HASH(ped, relationshipGroup);
	SET_PED_HEARING_RANGE(ped, 9999.f);
	SET_PED_CONFIG_FLAG(ped, 281, true);

	SET_PED_COMBAT_ATTRIBUTES(ped, 5, true);
	SET_PED_COMBAT_ATTRIBUTES(ped, 46, true);

	SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(ped, false);
	SET_RAGDOLL_BLOCKING_FLAGS(ped, 5);
	SET_PED_SUFFERS_CRITICAL_HITS(ped, false);

	GIVE_WEAPON_TO_PED(ped, weapon, 9999, true, true);
	TASK_COMBAT_PED(ped, playerPed, 0, 16);

	SET_PED_ACCURACY(ped, 50);
	SET_PED_FIRING_PATTERN(ped, 0xC6EE6B4C);

	SET_PED_COMPONENT_VARIATION(ped, 3, 0, 0, 0); // 0-5
	SET_PED_COMPONENT_VARIATION(ped, 4, 0, 2, 0); // 0-5

	for (int i = 0; i < 12; i++)
	{
		int drawableAmount = GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(ped, i);
		LOG(i << ": " << drawableAmount);

		for (int j = 0; j < drawableAmount; j++)
		{
			int textureAmount = GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(playerPed, i, drawableAmount);
			LOG("    " << j << ": " << textureAmount);
		}

		//int drawable = drawableAmount == 0 ? 0 : g_Random.GetRandomInt(0, drawableAmount - 1);
		//
		//int textureAmount = GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(playerPed, i, drawable);
		//int texture = textureAmount == 0 ? 0 : g_Random.GetRandomInt(0, textureAmount - 1);
		//
		//SET_PED_COMPONENT_VARIATION(playerPed, i, drawable, texture, g_Random.GetRandomInt(0, 3));
		//
		//if (i < 4)
		//{
		//	int propDrawableAmount = GET_NUMBER_OF_PED_PROP_DRAWABLE_VARIATIONS(playerPed, i);
		//	int propDrawable = propDrawableAmount == 0 ? 0 : g_Random.GetRandomInt(0, propDrawableAmount - 1);
		//
		//	int propTextureAmount = GET_NUMBER_OF_PED_PROP_TEXTURE_VARIATIONS(playerPed, i, drawable);
		//	int propTexture = propTextureAmount == 0 ? 0 : g_Random.GetRandomInt(0, propTextureAmount - 1);
		//
		//	SET_PED_PROP_INDEX(playerPed, i, propDrawable, propTexture, true);
		//}
	}
}

static RegisterEffect registerEffect(EFFECT_SPAWN_ZOMBIE_BRAD, OnStart, EffectInfo
	{
		.Name = "Spawn Zombie Brad",
		.Id = "spawn_zombie_brad",
		.EEffectGroupType = EEffectGroupType::SpawnEnemy
	}
);