#include <stdafx.h>

static void OnStartAll()
{
	Ped playerPed = PLAYER_PED_ID();

	for (Hash weapon : Memory::GetAllWeapons())
	{
		Util::GiveWeaponToPed(playerPed, weapon, false);
	}
}

static RegisterEffect registerEffect(EFFECT_GIVE_ALL_WEPS, OnStartAll, EffectInfo
	{
		.Name = "Give All Weapons",
		.Id = "player_allweps",
		.EEffectGroupType = EEffectGroupType::Weapons
	}
);