#pragma once

using Hash = unsigned long;

namespace Util
{
	// TODO: Maybe CWeaponInfo has some field which can be checked (instead of hardcoding the weapon hashes)
	inline bool IsWeaponShotgun(Hash ulWepHash)
	{
		switch (ulWepHash)
		{
		case 487013001:
		case 2017895192:
		case -1654528753:
		case -494615257:
		case -1466123874:
		case 984333226:
		case -275439685:
		case 317205821:
			return true;
		}

		return false;
	}

	inline void GiveRandomWeaponComponent(Ped ped, Hash weaponHash, std::vector<Hash> components, bool allowNone = false)
	{
		for (Hash& hash : components)
		{
			REMOVE_WEAPON_COMPONENT_FROM_PED(ped, weaponHash, hash);
		}

		if (!allowNone)
		{
			GIVE_WEAPON_COMPONENT_TO_PED(ped, weaponHash, components.at(g_Random.GetRandomInt(0, components.size() - 1)));
		}
		else
		{
			int index = g_Random.GetRandomInt(0, components.size());
			if (index < components.size())
			{
				GIVE_WEAPON_COMPONENT_TO_PED(ped, weaponHash, components.at(index));
			}
		}
	}

	inline void SetWeaponComponentActive(Ped ped, Hash weaponHash, Hash componentHash, bool active)
	{
		if (active)
		{
			GIVE_WEAPON_COMPONENT_TO_PED(ped, weaponHash, componentHash);
		}
		else
		{
			REMOVE_WEAPON_COMPONENT_FROM_PED(ped, weaponHash, componentHash);
		}
	}

	inline void GiveWeaponToPed(Ped ped, Hash weaponHash, bool equip)
	{
		GIVE_WEAPON_TO_PED(ped, weaponHash, 9999, true, true);

		if (weaponHash == GET_HASH_KEY("WEAPON_KNUCKLE"))
		{
			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_KNUCKLE_VARMOD_BASE"),    // Base Model
					GET_HASH_KEY("COMPONENT_KNUCKLE_VARMOD_PIMP"),    // The Pimp
					GET_HASH_KEY("COMPONENT_KNUCKLE_VARMOD_BALLAS"),  // The Ballas
					GET_HASH_KEY("COMPONENT_KNUCKLE_VARMOD_DOLLAR"),  // The Hustler
					GET_HASH_KEY("COMPONENT_KNUCKLE_VARMOD_DIAMOND"), // The Rock
					GET_HASH_KEY("COMPONENT_KNUCKLE_VARMOD_HATE"),    // The Hater
					GET_HASH_KEY("COMPONENT_KNUCKLE_VARMOD_LOVE"),    // The Lover
					GET_HASH_KEY("COMPONENT_KNUCKLE_VARMOD_PLAYER"),  // The Player
					GET_HASH_KEY("COMPONENT_KNUCKLE_VARMOD_KING"),    // The King
					GET_HASH_KEY("COMPONENT_KNUCKLE_VARMOD_VAGOS")    // The Vagos
				});
		}
		else if (weaponHash == GET_HASH_KEY("WEAPON_SWITCHBLADE"))
		{
			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_SWITCHBLADE_VARMOD_BASE"), // Default Handle
					GET_HASH_KEY("COMPONENT_SWITCHBLADE_VARMOD_VAR1"), // VIP Variant
					GET_HASH_KEY("COMPONENT_SWITCHBLADE_VARMOD_VAR2")  // Bodyguard Variant
				});
		}
		else if (weaponHash == GET_HASH_KEY("WEAPON_PISTOL"))
		{
			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_PISTOL_CLIP_01"), // Default Clip
					GET_HASH_KEY("COMPONENT_PISTOL_CLIP_02")  // Extended Clip
				});

			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_PI_FLSH"), g_Random.GetRandomInt(0, 1)); // Flashlight
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_PI_SUPP_02"), g_Random.GetRandomInt(0, 1)); // Suppressor
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_PISTOL_VARMOD_LUXE"), g_Random.GetRandomInt(0, 1)); // Yusuf Amir Luxury Finish
		}
		else if (weaponHash == GET_HASH_KEY("WEAPON_COMBATPISTOL"))
		{
			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_COMBATPISTOL_CLIP_01"), // Default Clip
					GET_HASH_KEY("COMPONENT_COMBATPISTOL_CLIP_02")  // Extended Clip
				});

			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_PI_FLSH"), g_Random.GetRandomInt(0, 1)); // Flashlight
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_PI_SUPP"), g_Random.GetRandomInt(0, 1)); // Suppressor
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_COMBATPISTOL_VARMOD_LOWRIDER"), g_Random.GetRandomInt(0, 1)); // Yusuf Amir Luxury Finish
		}
		else if (weaponHash == GET_HASH_KEY("WEAPON_APPISTOL"))
		{
			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_APPISTOL_CLIP_01"), // Default Clip
					GET_HASH_KEY("COMPONENT_APPISTOL_CLIP_02")  // Extended Clip
				});

			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_PI_FLSH"), g_Random.GetRandomInt(0, 1)); // Flashlight
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_PI_SUPP"), g_Random.GetRandomInt(0, 1)); // Suppressor
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_APPISTOL_VARMOD_LUXE"), g_Random.GetRandomInt(0, 1)); // Gilded Gun Metal Finish
		}
		else if (weaponHash == GET_HASH_KEY("WEAPON_PISTOL50"))
		{
			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_PISTOL50_CLIP_01"), // Default Clip
					GET_HASH_KEY("COMPONENT_PISTOL50_CLIP_02")  // Extended Clip
				});

			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_PI_FLSH"), g_Random.GetRandomInt(0, 1)); // Flashlight
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_AR_SUPP_02"), g_Random.GetRandomInt(0, 1)); // Suppressor
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_PISTOL50_VARMOD_LUXE"), g_Random.GetRandomInt(0, 1)); // Platinum Pearl Deluxe Finish
		}
		else if (weaponHash == GET_HASH_KEY("WEAPON_REVOLVER"))
		{
			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_REVOLVER_VARMOD_BOSS"), // VIP Variant
					GET_HASH_KEY("COMPONENT_REVOLVER_VARMOD_GOON")  // Bodyguard Variant
				}, true);
		}
		else if (weaponHash == GET_HASH_KEY("WEAPON_SNSPISTOL"))
		{
			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_SNSPISTOL_CLIP_01"), // Default Clip
					GET_HASH_KEY("COMPONENT_SNSPISTOL_CLIP_02")  // Extended Clip
				});

			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_SNSPISTOL_VARMOD_LOWRIDER"), g_Random.GetRandomInt(0, 1)); // Etched Wood Grip Finish
		}
		else if (weaponHash == GET_HASH_KEY("WEAPON_HEAVYPISTOL"))
		{
			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_HEAVYPISTOL_CLIP_01"), // Default Clip
					GET_HASH_KEY("COMPONENT_HEAVYPISTOL_CLIP_02")  // Extended Clip
				});

			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_PI_FLSH"), g_Random.GetRandomInt(0, 1)); // Flashlight
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_PI_SUPP"), g_Random.GetRandomInt(0, 1)); // Suppressor
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_HEAVYPISTOL_VARMOD_LUXE"), g_Random.GetRandomInt(0, 1)); // Etched Wood Grip Finish
		}
		else if (weaponHash == GET_HASH_KEY("WEAPON_REVOLVER_MK2"))
		{
			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_REVOLVER_MK2_CLIP_01"),          // Default Rounds
					GET_HASH_KEY("COMPONENT_REVOLVER_MK2_CLIP_TRACER"),      // Tracer Rounds
					GET_HASH_KEY("COMPONENT_REVOLVER_MK2_CLIP_INCENDIARY"),  // Incendiary Rounds
					GET_HASH_KEY("COMPONENT_REVOLVER_MK2_CLIP_HOLLOWPOINT"), // Hollow Point Rounds
					GET_HASH_KEY("COMPONENT_REVOLVER_MK2_CLIP_FMJ")          // Full Metal Jacket Rounds
				});

			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_REVOLVER_MK2_CAMO"),   	   // Digital Camo
					GET_HASH_KEY("COMPONENT_REVOLVER_MK2_CAMO_02"),	   // Brushstroke Camo
					GET_HASH_KEY("COMPONENT_REVOLVER_MK2_CAMO_03"),	   // Woodland Camo
					GET_HASH_KEY("COMPONENT_REVOLVER_MK2_CAMO_04"),	   // Skull
					GET_HASH_KEY("COMPONENT_REVOLVER_MK2_CAMO_05"),	   // Sessanta Nove
					GET_HASH_KEY("COMPONENT_REVOLVER_MK2_CAMO_06"),	   // Perseus
					GET_HASH_KEY("COMPONENT_REVOLVER_MK2_CAMO_07"),	   // Leopard
					GET_HASH_KEY("COMPONENT_REVOLVER_MK2_CAMO_08"),	   // Zebra
					GET_HASH_KEY("COMPONENT_REVOLVER_MK2_CAMO_09"),	   // Geometric
					GET_HASH_KEY("COMPONENT_REVOLVER_MK2_CAMO_10"),	   // Boom!
					GET_HASH_KEY("COMPONENT_REVOLVER_MK2_CAMO_IND_01") // Patriotic
				}, true);

			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_SIGHTS"), g_Random.GetRandomInt(0, 1)); // Holographic Sight
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_SCOPE_MACRO_MK2"), g_Random.GetRandomInt(0, 1)); // Small Scope
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_PI_FLSH"), g_Random.GetRandomInt(0, 1)); // Flashlight
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_PI_COMP_03"), g_Random.GetRandomInt(0, 1)); // Compensator
		}
		else if (weaponHash == GET_HASH_KEY("WEAPON_SNSPISTOL_MK2"))
		{
			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_SNSPISTOL_MK2_CLIP_01"),          // Default Clip
					GET_HASH_KEY("COMPONENT_SNSPISTOL_MK2_CLIP_02"),          // Extended Clip
					GET_HASH_KEY("COMPONENT_SNSPISTOL_MK2_CLIP_TRACER"),      // Tracer Rounds
					GET_HASH_KEY("COMPONENT_SNSPISTOL_MK2_CLIP_INCENDIARY"),  // Incendiary Rounds
					GET_HASH_KEY("COMPONENT_SNSPISTOL_MK2_CLIP_HOLLOWPOINT"), // Hollow Point Rounds
					GET_HASH_KEY("COMPONENT_SNSPISTOL_MK2_CLIP_FMJ")          // Full Metal Jacket Rounds
				});

			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_SNSPISTOL_MK2_CAMO"),       // Digital Camo
					GET_HASH_KEY("COMPONENT_SNSPISTOL_MK2_CAMO_02"),    // Brushstroke Camo
					GET_HASH_KEY("COMPONENT_SNSPISTOL_MK2_CAMO_03"),    // Woodland Camo
					GET_HASH_KEY("COMPONENT_SNSPISTOL_MK2_CAMO_04"),    // Skull
					GET_HASH_KEY("COMPONENT_SNSPISTOL_MK2_CAMO_05"),    // Sessanta Nove
					GET_HASH_KEY("COMPONENT_SNSPISTOL_MK2_CAMO_06"),    // Perseus
					GET_HASH_KEY("COMPONENT_SNSPISTOL_MK2_CAMO_07"),    // Leopard
					GET_HASH_KEY("COMPONENT_SNSPISTOL_MK2_CAMO_08"),    // Zebra
					GET_HASH_KEY("COMPONENT_SNSPISTOL_MK2_CAMO_09"),    // Geometric
					GET_HASH_KEY("COMPONENT_SNSPISTOL_MK2_CAMO_10"),    // Boom!
					GET_HASH_KEY("COMPONENT_SNSPISTOL_MK2_CAMO_IND_01") // Patriotic
				}, true);

			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_PI_FLSH_03"), g_Random.GetRandomInt(0, 1)); // Flashlight
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_PI_RAIL_02"), g_Random.GetRandomInt(0, 1)); // Mounted Scope
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_PI_SUPP_02"), g_Random.GetRandomInt(0, 1)); // Suppressor
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_PI_COMP_02"), g_Random.GetRandomInt(0, 1)); // Compensator
		}
		else if (weaponHash == GET_HASH_KEY("WEAPON_PISTOL_MK2"))
		{
			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_PISTOL_MK2_CLIP_01"),          // Default Clip
					GET_HASH_KEY("COMPONENT_PISTOL_MK2_CLIP_02"),          // Extended Clip
					GET_HASH_KEY("COMPONENT_PISTOL_MK2_CLIP_TRACER"),      // Tracer Rounds
					GET_HASH_KEY("COMPONENT_PISTOL_MK2_CLIP_INCENDIARY"),  // Incendiary Rounds
					GET_HASH_KEY("COMPONENT_PISTOL_MK2_CLIP_HOLLOWPOINT"), // Hollow Point Rounds
					GET_HASH_KEY("COMPONENT_PISTOL_MK2_CLIP_FMJ")          // Full Metal Jacket Rounds
				});

			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_PISTOL_MK2_CAMO"),       // Digital Camo
					GET_HASH_KEY("COMPONENT_PISTOL_MK2_CAMO_02"),    // Brushstroke Camo
					GET_HASH_KEY("COMPONENT_PISTOL_MK2_CAMO_03"),    // Woodland Camo
					GET_HASH_KEY("COMPONENT_PISTOL_MK2_CAMO_04"),    // Skull
					GET_HASH_KEY("COMPONENT_PISTOL_MK2_CAMO_05"),    // Sessanta Nove
					GET_HASH_KEY("COMPONENT_PISTOL_MK2_CAMO_06"),    // Perseus
					GET_HASH_KEY("COMPONENT_PISTOL_MK2_CAMO_07"),    // Leopard
					GET_HASH_KEY("COMPONENT_PISTOL_MK2_CAMO_08"),    // Zebra
					GET_HASH_KEY("COMPONENT_PISTOL_MK2_CAMO_09"),    // Geometric
					GET_HASH_KEY("COMPONENT_PISTOL_MK2_CAMO_10"),    // Boom!
					GET_HASH_KEY("COMPONENT_PISTOL_MK2_CAMO_IND_01") // Patriotic
				}, true);

			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_AT_PI_SUPP_02"), // Suppressor
					GET_HASH_KEY("COMPONENT_AT_PI_COMP")     // Compensator
				}, true);

			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_PI_FLSH_02"), g_Random.GetRandomInt(0, 1)); // Flashlight
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_PI_RAIL"), g_Random.GetRandomInt(0, 1)); // Mounted Scope
		}
		else if (weaponHash == GET_HASH_KEY("WEAPON_VINTAGEPISTOL"))
		{
			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_VINTAGEPISTOL_CLIP_01"), // Default Clip
					GET_HASH_KEY("COMPONENT_VINTAGEPISTOL_CLIP_02")  // Extended Clip
				});

			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_PI_SUPP"), g_Random.GetRandomInt(0, 1)); // Suppressor
		}
		else if (weaponHash == GET_HASH_KEY("WEAPON_RAYPISTOL"))
		{
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_RAYPISTOL_VARMOD_XMAS18"), g_Random.GetRandomInt(0, 1)); // Festive tint
		}
		else if (weaponHash == GET_HASH_KEY("WEAPON_CERAMICPISTOL"))
		{
			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_CERAMICPISTOL_CLIP_01"), // Default Clip
					GET_HASH_KEY("COMPONENT_CERAMICPISTOL_CLIP_02")  // Extended Clip
				});

			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_CERAMICPISTOL_SUPP"), g_Random.GetRandomInt(0, 1)); // Suppressor
		}
		else if (weaponHash == GET_HASH_KEY("WEAPON_MICROSMG"))
		{
			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_MICROSMG_CLIP_01"), // Default Clip
					GET_HASH_KEY("COMPONENT_MICROSMG_CLIP_02")  // Extended Clip
				});

			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_PI_FLSH"), g_Random.GetRandomInt(0, 1)); // Flashlight
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_SCOPE_MACRO"), g_Random.GetRandomInt(0, 1)); // Scope
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_AR_SUPP_02"), g_Random.GetRandomInt(0, 1)); // Suppressor
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_MICROSMG_VARMOD_LUXE"), g_Random.GetRandomInt(0, 1)); // Yusuf Amir Luxury Finish
		}
		else if (weaponHash == GET_HASH_KEY("WEAPON_SMG"))
		{
			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_SMG_CLIP_01"), // Default Clip
					GET_HASH_KEY("COMPONENT_SMG_CLIP_02"), // Extended Clip
					GET_HASH_KEY("COMPONENT_SMG_CLIP_03")  // Drum Magazine
				});

			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_AR_FLSH"), g_Random.GetRandomInt(0, 1)); // Flashlight
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_SCOPE_MACRO_02"), g_Random.GetRandomInt(0, 1)); // Scope
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_PI_SUPP"), g_Random.GetRandomInt(0, 1)); // Suppressor
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_SMG_VARMOD_LUXE"), g_Random.GetRandomInt(0, 1)); // Yusuf Amir Luxury Finish
		}
		else if (weaponHash == GET_HASH_KEY("WEAPON_ASSAULTSMG"))
		{
			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_ASSAULTSMG_CLIP_01"), // Default Clip
					GET_HASH_KEY("COMPONENT_ASSAULTSMG_CLIP_02")  // Extended Clip
				});

			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_AR_FLSH"), g_Random.GetRandomInt(0, 1)); // Flashlight
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_SCOPE_MACRO"), g_Random.GetRandomInt(0, 1)); // Scope
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_AR_SUPP_02"), g_Random.GetRandomInt(0, 1)); // Suppressor
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_ASSAULTSMG_VARMOD_LOWRIDER"), g_Random.GetRandomInt(0, 1)); // Yusuf Amir Luxury Finish
		}
		else if (weaponHash == GET_HASH_KEY("WEAPON_MINISMG"))
		{
			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_MINISMG_CLIP_01"), // Default Clip
					GET_HASH_KEY("COMPONENT_MINISMG_CLIP_02")  // Extended Clip
				});
		}
		else if (weaponHash == GET_HASH_KEY("WEAPON_SMG_MK2"))
		{
			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_SMG_MK2_CLIP_01"),          // Default Clip
					GET_HASH_KEY("COMPONENT_SMG_MK2_CLIP_02"),          // Extended Clip
					GET_HASH_KEY("COMPONENT_SMG_MK2_CLIP_TRACER"),      // Tracer Rounds
					GET_HASH_KEY("COMPONENT_SMG_MK2_CLIP_INCENDIARY"),  // Incendiary Rounds
					GET_HASH_KEY("COMPONENT_SMG_MK2_CLIP_HOLLOWPOINT"), // Hollow Point Rounds
					GET_HASH_KEY("COMPONENT_SMG_MK2_CLIP_FMJ")          // Full Metal Jacket Rounds
				});

			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_AT_SIGHTS_SMG"),             // Holographic Sight
					GET_HASH_KEY("COMPONENT_AT_SCOPE_MACRO_02_SMG_MK2"), // Small Scope
					GET_HASH_KEY("COMPONENT_AT_SCOPE_SMALL_SMG_MK2")     // Medium Scope
				}, true);

			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_AT_PI_SUPP"),   // Suppressor
					GET_HASH_KEY("COMPONENT_AT_MUZZLE_01"), // Flat Muzzle Brake
					GET_HASH_KEY("COMPONENT_AT_MUZZLE_02"), // Tactical Muzzle Brake
					GET_HASH_KEY("COMPONENT_AT_MUZZLE_03"), // Fat-End Muzzle Brake
					GET_HASH_KEY("COMPONENT_AT_MUZZLE_04"), // Precision Muzzle Brake
					GET_HASH_KEY("COMPONENT_AT_MUZZLE_05"), // Heavy Duty Muzzle Brake
					GET_HASH_KEY("COMPONENT_AT_MUZZLE_06"), // Slanted Muzzle Brake
					GET_HASH_KEY("COMPONENT_AT_MUZZLE_07")  // Split-End Muzzle Brake
				}, true);

			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_AT_SB_BARREL_01"), // Default Barrel
					GET_HASH_KEY("COMPONENT_AT_SB_BARREL_02")  // Heavy Barrel
				});

			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_SMG_MK2_CAMO"),       // Digital Camo
					GET_HASH_KEY("COMPONENT_SMG_MK2_CAMO_02"),    // Brushstroke Camo
					GET_HASH_KEY("COMPONENT_SMG_MK2_CAMO_03"),    // Woodland Camo
					GET_HASH_KEY("COMPONENT_SMG_MK2_CAMO_04"),    // Skull
					GET_HASH_KEY("COMPONENT_SMG_MK2_CAMO_05"),    // Sessanta Nove
					GET_HASH_KEY("COMPONENT_SMG_MK2_CAMO_06"),    // Perseus
					GET_HASH_KEY("COMPONENT_SMG_MK2_CAMO_07"),    // Leopard
					GET_HASH_KEY("COMPONENT_SMG_MK2_CAMO_08"),    // Zebra
					GET_HASH_KEY("COMPONENT_SMG_MK2_CAMO_09"),    // Geometric
					GET_HASH_KEY("COMPONENT_SMG_MK2_CAMO_10"),    // Boom!
					GET_HASH_KEY("COMPONENT_SMG_MK2_CAMO_IND_01") // Patriotic
				}, true);

			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_AR_FLSH"), g_Random.GetRandomInt(0, 1)); // Flashlight
		}
		else if (weaponHash == GET_HASH_KEY("WEAPON_MACHINEPISTOL"))
		{
			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_MACHINEPISTOL_CLIP_01"), // Default Clip
					GET_HASH_KEY("COMPONENT_MACHINEPISTOL_CLIP_02"), // Extended Clip
					GET_HASH_KEY("COMPONENT_MACHINEPISTOL_CLIP_03")  // Drum Magazine
				});

			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_PI_SUPP"), g_Random.GetRandomInt(0, 1)); // Suppressor
		}
		else if (weaponHash == GET_HASH_KEY("WEAPON_COMBATPDW"))
		{
			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_COMBATPDW_CLIP_01"), // Default Clip
					GET_HASH_KEY("COMPONENT_COMBATPDW_CLIP_02"), // Extended Clip
					GET_HASH_KEY("COMPONENT_COMBATPDW_CLIP_03")  // Drum Magazine
				});

			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_AR_FLSH"), g_Random.GetRandomInt(0, 1)); // Flashlight
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_AR_AFGRIP"), g_Random.GetRandomInt(0, 1)); // Grip
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_SCOPE_SMALL"), g_Random.GetRandomInt(0, 1)); // Scope
		}
		else if (weaponHash == GET_HASH_KEY("WEAPON_PUMPSHOTGUN"))
		{
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_AR_FLSH"), g_Random.GetRandomInt(0, 1)); // Flashlight
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_SR_SUPP"), g_Random.GetRandomInt(0, 1)); // Suppressor
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_PUMPSHOTGUN_VARMOD_LOWRIDER"), g_Random.GetRandomInt(0, 1)); // Yusuf Amir Luxury Finish
		}
		else if (weaponHash == GET_HASH_KEY("WEAPON_SAWNOFFSHOTGUN"))
		{
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_SAWNOFFSHOTGUN_VARMOD_LUXE"), g_Random.GetRandomInt(0, 1)); // Gilded Gun Metal Finish
		}
		else if (weaponHash == GET_HASH_KEY("WEAPON_ASSAULTSHOTGUN"))
		{
			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_ASSAULTSHOTGUN_CLIP_01"), // Default Clip
					GET_HASH_KEY("COMPONENT_ASSAULTSHOTGUN_CLIP_02")  // Extended Clip
				});

			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_AR_FLSH"), g_Random.GetRandomInt(0, 1)); // Flashlight
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_AR_SUPP"), g_Random.GetRandomInt(0, 1)); // Suppressor
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_AR_AFGRIP"), g_Random.GetRandomInt(0, 1)); // Grip
		}
		else if (weaponHash == GET_HASH_KEY("WEAPON_BULLPUPSHOTGUN"))
		{
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_AR_FLSH"), g_Random.GetRandomInt(0, 1)); // Flashlight
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_AR_SUPP_02"), g_Random.GetRandomInt(0, 1)); // Suppressor
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_AR_AFGRIP"), g_Random.GetRandomInt(0, 1)); // Grip
		}
		else if (weaponHash == GET_HASH_KEY("WEAPON_PUMPSHOTGUN_MK2"))
		{
			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_PUMPSHOTGUN_MK2_CLIP_01"),            // Default Shells
					GET_HASH_KEY("COMPONENT_PUMPSHOTGUN_MK2_CLIP_INCENDIARY"),    // Dragon's Breath Shells
					GET_HASH_KEY("COMPONENT_PUMPSHOTGUN_MK2_CLIP_ARMORPIERCING"), // Steel Buckshot Shells
					GET_HASH_KEY("COMPONENT_PUMPSHOTGUN_MK2_CLIP_HOLLOWPOINT"),   // Flechette Shells
					GET_HASH_KEY("COMPONENT_PUMPSHOTGUN_MK2_CLIP_EXPLOSIVE")      // Explosive Slugs
				});

			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_AT_SIGHTS"),          // Holographic Sight
					GET_HASH_KEY("COMPONENT_AT_SCOPE_MACRO_MK2"), // Small Scope
					GET_HASH_KEY("COMPONENT_AT_SCOPE_SMALL_MK2")  // Medium Scope
				}, true);

			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_PUMPSHOTGUN_MK2_CAMO"),       // Digital Camo
					GET_HASH_KEY("COMPONENT_PUMPSHOTGUN_MK2_CAMO_02"),    // Brushstroke Camo
					GET_HASH_KEY("COMPONENT_PUMPSHOTGUN_MK2_CAMO_03"),    // Woodland Camo
					GET_HASH_KEY("COMPONENT_PUMPSHOTGUN_MK2_CAMO_04"),    // Skull
					GET_HASH_KEY("COMPONENT_PUMPSHOTGUN_MK2_CAMO_05"),    // Sessanta Nove
					GET_HASH_KEY("COMPONENT_PUMPSHOTGUN_MK2_CAMO_06"),    // Perseus
					GET_HASH_KEY("COMPONENT_PUMPSHOTGUN_MK2_CAMO_07"),    // Leopard
					GET_HASH_KEY("COMPONENT_PUMPSHOTGUN_MK2_CAMO_08"),    // Zebra
					GET_HASH_KEY("COMPONENT_PUMPSHOTGUN_MK2_CAMO_09"),    // Geometric
					GET_HASH_KEY("COMPONENT_PUMPSHOTGUN_MK2_CAMO_10"),    // Boom!
					GET_HASH_KEY("COMPONENT_PUMPSHOTGUN_MK2_CAMO_IND_01") // Patriotic
				}, true);

			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_AR_FLSH"), g_Random.GetRandomInt(0, 1)); // Flashlight
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_SR_SUPP_03"), g_Random.GetRandomInt(0, 1)); // Suppressor
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_MUZZLE_08"), g_Random.GetRandomInt(0, 1)); // Squared Muzzle Brake
		}
		else if (weaponHash == GET_HASH_KEY("WEAPON_HEAVYSHOTGUN"))
		{
			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_HEAVYSHOTGUN_CLIP_01"), // Default Clip
					GET_HASH_KEY("COMPONENT_HEAVYSHOTGUN_CLIP_02"), // Extended Clip
					GET_HASH_KEY("COMPONENT_HEAVYSHOTGUN_CLIP_03")  // Drum Magazine
				});

			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_AR_FLSH"), g_Random.GetRandomInt(0, 1)); // Flashlight
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_AR_SUPP_02"), g_Random.GetRandomInt(0, 1)); // Suppressor
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_AR_AFGRIP"), g_Random.GetRandomInt(0, 1)); // Grip
		}
		else if (weaponHash == GET_HASH_KEY("WEAPON_COMBATSHOTGUN"))
		{
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_AR_FLSH"), g_Random.GetRandomInt(0, 1)); // Flashlight
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_AR_SUPP"), g_Random.GetRandomInt(0, 1)); // Suppressor
		}
		else if (weaponHash == GET_HASH_KEY("WEAPON_ASSAULTRIFLE"))
		{
			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_ASSAULTRIFLE_CLIP_01"), // Default Clip
					GET_HASH_KEY("COMPONENT_ASSAULTRIFLE_CLIP_02"), // Extended Clip
					GET_HASH_KEY("COMPONENT_ASSAULTRIFLE_CLIP_03")  // Drum Magazine
				});

			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_AR_FLSH"), g_Random.GetRandomInt(0, 1)); // Flashlight
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_SCOPE_MACRO"), g_Random.GetRandomInt(0, 1)); // Scope
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_AR_SUPP_02"), g_Random.GetRandomInt(0, 1)); // Suppressor
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_AR_AFGRIP"), g_Random.GetRandomInt(0, 1)); // Grip
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_ASSAULTRIFLE_VARMOD_LUXE"), g_Random.GetRandomInt(0, 1)); // Yusuf Amir Luxury Finish
		}
		else if (weaponHash == GET_HASH_KEY("WEAPON_CARBINERIFLE"))
		{
			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_CARBINERIFLE_CLIP_01"), // Default Clip
					GET_HASH_KEY("COMPONENT_CARBINERIFLE_CLIP_02"), // Extended Clip
					GET_HASH_KEY("COMPONENT_CARBINERIFLE_CLIP_03")  // Box Magazine
				});

			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_AR_FLSH"), g_Random.GetRandomInt(0, 1)); // Flashlight
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_SCOPE_MEDIUM"), g_Random.GetRandomInt(0, 1)); // Scope
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_AR_SUPP"), g_Random.GetRandomInt(0, 1)); // Suppressor
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_AR_AFGRIP"), g_Random.GetRandomInt(0, 1)); // Grip
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_CARBINERIFLE_VARMOD_LUXE"), g_Random.GetRandomInt(0, 1)); // Yusuf Amir Luxury Finish
		}
		else if (weaponHash == GET_HASH_KEY("WEAPON_ADVANCEDRIFLE"))
		{
			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_ADVANCEDRIFLE_CLIP_01"), // Default Clip
					GET_HASH_KEY("COMPONENT_ADVANCEDRIFLE_CLIP_02")  // Extended Clip
				});

			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_AR_FLSH"), g_Random.GetRandomInt(0, 1)); // Flashlight
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_SCOPE_SMALL"), g_Random.GetRandomInt(0, 1)); // Scope
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_AR_SUPP"), g_Random.GetRandomInt(0, 1)); // Suppressor
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_ADVANCEDRIFLE_VARMOD_LUXE"), g_Random.GetRandomInt(0, 1)); // Gilded Gun Metal Finish
		}
		else if (weaponHash == GET_HASH_KEY("WEAPON_SPECIALCARBINE"))
		{
			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_SPECIALCARBINE_CLIP_01"), // Default Clip
					GET_HASH_KEY("COMPONENT_SPECIALCARBINE_CLIP_02"), // Extended Clip
					GET_HASH_KEY("COMPONENT_SPECIALCARBINE_CLIP_03")  // Drum Magazine
				});

			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_AR_FLSH"), g_Random.GetRandomInt(0, 1)); // Flashlight
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_SCOPE_MEDIUM"), g_Random.GetRandomInt(0, 1)); // Scope
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_AR_SUPP_02"), g_Random.GetRandomInt(0, 1)); // Suppressor
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_AR_AFGRIP"), g_Random.GetRandomInt(0, 1)); // Grip
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_SPECIALCARBINE_VARMOD_LOWRIDER"), g_Random.GetRandomInt(0, 1)); // Etched Gun Metal Finish
		}
		else if (weaponHash == GET_HASH_KEY("WEAPON_BULLPUPRIFLE"))
		{
			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_BULLPUPRIFLE_CLIP_01"), // Default Clip
					GET_HASH_KEY("COMPONENT_BULLPUPRIFLE_CLIP_02")  // Extended Clip
				});

			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_AR_FLSH"), g_Random.GetRandomInt(0, 1)); // Flashlight
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_SCOPE_SMALL"), g_Random.GetRandomInt(0, 1)); // Scope
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_AR_SUPP"), g_Random.GetRandomInt(0, 1)); // Suppressor
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_AR_AFGRIP"), g_Random.GetRandomInt(0, 1)); // Grip
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_BULLPUPRIFLE_VARMOD_LOW"), g_Random.GetRandomInt(0, 1)); // Gilded Gun Metal Finish
		}
		else if (weaponHash == GET_HASH_KEY("WEAPON_BULLPUPRIFLE_MK2"))
		{
			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_BULLPUPRIFLE_MK2_CLIP_01"),            // Default Clip
					GET_HASH_KEY("COMPONENT_BULLPUPRIFLE_MK2_CLIP_02"),            // Extended Clip
					GET_HASH_KEY("COMPONENT_BULLPUPRIFLE_MK2_CLIP_TRACER"),        // Tracer Rounds
					GET_HASH_KEY("COMPONENT_BULLPUPRIFLE_MK2_CLIP_INCENDIARY"),    // Incendiary Rounds
					GET_HASH_KEY("COMPONENT_BULLPUPRIFLE_MK2_CLIP_ARMORPIERCING"), // Armor Piercing Rounds
					GET_HASH_KEY("COMPONENT_BULLPUPRIFLE_MK2_CLIP_FMJ")            // Full Metal Jacket Rounds
				});

			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_AT_SIGHTS"),             // Holographic Sight
					GET_HASH_KEY("COMPONENT_AT_SCOPE_MACRO_02_MK2"), // Small Scope
					GET_HASH_KEY("COMPONENT_AT_SCOPE_SMALL_MK2")     // Medium Scope
				}, true);

			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_AT_BP_BARREL_01"), // Default Barrel
					GET_HASH_KEY("COMPONENT_AT_BP_BARREL_02")  // Heavy Barrel
				});

			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_AT_AR_SUPP"),   // Suppressor
					GET_HASH_KEY("COMPONENT_AT_MUZZLE_01"), // Flat Muzzle Brake
					GET_HASH_KEY("COMPONENT_AT_MUZZLE_02"), // Tactical Muzzle Brake
					GET_HASH_KEY("COMPONENT_AT_MUZZLE_03"), // Fat-End Muzzle Brake
					GET_HASH_KEY("COMPONENT_AT_MUZZLE_04"), // Precision Muzzle Brake
					GET_HASH_KEY("COMPONENT_AT_MUZZLE_05"), // Heavy Duty Muzzle Brake
					GET_HASH_KEY("COMPONENT_AT_MUZZLE_06"), // Slanted Muzzle Brake
					GET_HASH_KEY("COMPONENT_AT_MUZZLE_07")  // Split-End Muzzle Brake
				}, true);

			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_BULLPUPRIFLE_MK2_CAMO"),        // Digital Camo
					GET_HASH_KEY("COMPONENT_BULLPUPRIFLE_MK2_CAMO_02"),     // Brushstroke Camo
					GET_HASH_KEY("COMPONENT_BULLPUPRIFLE_MK2_CAMO_03"),     // Woodland Camo
					GET_HASH_KEY("COMPONENT_BULLPUPRIFLE_MK2_CAMO_04"),     // Skull
					GET_HASH_KEY("COMPONENT_BULLPUPRIFLE_MK2_CAMO_05"),     // Sessanta Nove
					GET_HASH_KEY("COMPONENT_BULLPUPRIFLE_MK2_CAMO_06"),     // Perseus
					GET_HASH_KEY("COMPONENT_BULLPUPRIFLE_MK2_CAMO_07"),     // Leopard
					GET_HASH_KEY("COMPONENT_BULLPUPRIFLE_MK2_CAMO_08"),     // Zebra
					GET_HASH_KEY("COMPONENT_BULLPUPRIFLE_MK2_CAMO_09"),     // Geometric
					GET_HASH_KEY("COMPONENT_BULLPUPRIFLE_MK2_CAMO_10"),     // Boom!
					GET_HASH_KEY("COMPONENT_BULLPUPRIFLE_MK2_CAMO_IND_01"), // Patriotic
				}, true);

			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_AR_FLSH"), g_Random.GetRandomInt(0, 1)); // Flashlight
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_AR_AFGRIP_02"), g_Random.GetRandomInt(0, 1)); // Grip
		}
		else if (weaponHash == GET_HASH_KEY("WEAPON_SPECIALCARBINE_MK2"))
		{
			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_SPECIALCARBINE_MK2_CLIP_01"),            // Default Clip
					GET_HASH_KEY("COMPONENT_SPECIALCARBINE_MK2_CLIP_02"),            // Extended Clip
					GET_HASH_KEY("COMPONENT_SPECIALCARBINE_MK2_CLIP_TRACER"),        // Tracer Rounds
					GET_HASH_KEY("COMPONENT_SPECIALCARBINE_MK2_CLIP_INCENDIARY"),    // Incendiary Rounds
					GET_HASH_KEY("COMPONENT_SPECIALCARBINE_MK2_CLIP_ARMORPIERCING"), // Armor Piercing Rounds
					GET_HASH_KEY("COMPONENT_SPECIALCARBINE_MK2_CLIP_FMJ")            // Full Metal Jacket Rounds
				});

			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_AT_SIGHTS"),          // Holographic Sight
					GET_HASH_KEY("COMPONENT_AT_SCOPE_MACRO_MK2"), // Small Scope
					GET_HASH_KEY("COMPONENT_AT_SCOPE_MEDIUM_MK2") // Large Scope
				}, true);

			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_AT_BP_BARREL_01"), // Default Barrel
					GET_HASH_KEY("COMPONENT_AT_BP_BARREL_02")  // Heavy Barrel
				});

			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_AT_AR_SUPP_02"), // Suppressor
					GET_HASH_KEY("COMPONENT_AT_MUZZLE_01"),  // Flat Muzzle Brake
					GET_HASH_KEY("COMPONENT_AT_MUZZLE_02"),  // Tactical Muzzle Brake
					GET_HASH_KEY("COMPONENT_AT_MUZZLE_03"),  // Fat-End Muzzle Brake
					GET_HASH_KEY("COMPONENT_AT_MUZZLE_04"),  // Precision Muzzle Brake
					GET_HASH_KEY("COMPONENT_AT_MUZZLE_05"),  // Heavy Duty Muzzle Brake
					GET_HASH_KEY("COMPONENT_AT_MUZZLE_06"),  // Slanted Muzzle Brake
					GET_HASH_KEY("COMPONENT_AT_MUZZLE_07")   // Split-End Muzzle Brake
				}, true);

			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_AT_SC_BARREL_01"), // Default Barrel
					GET_HASH_KEY("COMPONENT_AT_SC_BARREL_02")  // Heavy Barrel
				});

			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_SPECIALCARBINE_MK2_CAMO"),        // Digital Camo
					GET_HASH_KEY("COMPONENT_SPECIALCARBINE_MK2_CAMO_02"),     // Brushstroke Camo
					GET_HASH_KEY("COMPONENT_SPECIALCARBINE_MK2_CAMO_03"),     // Woodland Camo
					GET_HASH_KEY("COMPONENT_SPECIALCARBINE_MK2_CAMO_04"),     // Skull
					GET_HASH_KEY("COMPONENT_SPECIALCARBINE_MK2_CAMO_05"),     // Sessanta Nove
					GET_HASH_KEY("COMPONENT_SPECIALCARBINE_MK2_CAMO_06"),     // Perseus
					GET_HASH_KEY("COMPONENT_SPECIALCARBINE_MK2_CAMO_07"),     // Leopard
					GET_HASH_KEY("COMPONENT_SPECIALCARBINE_MK2_CAMO_08"),     // Zebra
					GET_HASH_KEY("COMPONENT_SPECIALCARBINE_MK2_CAMO_09"),     // Geometric
					GET_HASH_KEY("COMPONENT_SPECIALCARBINE_MK2_CAMO_10"),     // Boom!
					GET_HASH_KEY("COMPONENT_SPECIALCARBINE_MK2_CAMO_IND_01"), // Patriotic
				}, true);

			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_AR_FLSH"), g_Random.GetRandomInt(0, 1)); // Flashlight
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_AR_AFGRIP_02"), g_Random.GetRandomInt(0, 1)); // Grip
		}
		else if (weaponHash == GET_HASH_KEY("WEAPON_ASSAULTRIFLE_MK2"))
		{
			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_ASSAULTRIFLE_MK2_CLIP_01"),            // Default Clip
					GET_HASH_KEY("COMPONENT_ASSAULTRIFLE_MK2_CLIP_02"),            // Extended Clip
					GET_HASH_KEY("COMPONENT_ASSAULTRIFLE_MK2_CLIP_TRACER"),        // Tracer Rounds
					GET_HASH_KEY("COMPONENT_ASSAULTRIFLE_MK2_CLIP_INCENDIARY"),    // Incendiary Rounds
					GET_HASH_KEY("COMPONENT_ASSAULTRIFLE_MK2_CLIP_ARMORPIERCING"), // Armor Piercing Rounds
					GET_HASH_KEY("COMPONENT_ASSAULTRIFLE_MK2_CLIP_FMJ")            // Full Metal Jacket Rounds
				});

			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_AT_SIGHTS"),          // Holographic Sight
					GET_HASH_KEY("COMPONENT_AT_SCOPE_MACRO_MK2"), // Small Scope
					GET_HASH_KEY("COMPONENT_AT_SCOPE_MEDIUM_MK2") // Large Scope
				}, true);

			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_AT_AR_BARREL_01"), // Default Barrel
					GET_HASH_KEY("COMPONENT_AT_AR_BARREL_02")  // Heavy Barrel
				});

			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_AT_AR_SUPP_02"), // Suppressor
					GET_HASH_KEY("COMPONENT_AT_MUZZLE_01"),  // Flat Muzzle Brake
					GET_HASH_KEY("COMPONENT_AT_MUZZLE_02"),  // Tactical Muzzle Brake
					GET_HASH_KEY("COMPONENT_AT_MUZZLE_03"),  // Fat-End Muzzle Brake
					GET_HASH_KEY("COMPONENT_AT_MUZZLE_04"),  // Precision Muzzle Brake
					GET_HASH_KEY("COMPONENT_AT_MUZZLE_05"),  // Heavy Duty Muzzle Brake
					GET_HASH_KEY("COMPONENT_AT_MUZZLE_06"),  // Slanted Muzzle Brake
					GET_HASH_KEY("COMPONENT_AT_MUZZLE_07")   // Split-End Muzzle Brake
				}, true);

			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_AT_AR_BARREL_01"), // Default Barrel
					GET_HASH_KEY("COMPONENT_AT_AR_BARREL_02")  // Heavy Barrel
				});

			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_ASSAULTRIFLE_MK2_CAMO"),        // Digital Camo
					GET_HASH_KEY("COMPONENT_ASSAULTRIFLE_MK2_CAMO_02"),     // Brushstroke Camo
					GET_HASH_KEY("COMPONENT_ASSAULTRIFLE_MK2_CAMO_03"),     // Woodland Camo
					GET_HASH_KEY("COMPONENT_ASSAULTRIFLE_MK2_CAMO_04"),     // Skull
					GET_HASH_KEY("COMPONENT_ASSAULTRIFLE_MK2_CAMO_05"),     // Sessanta Nove
					GET_HASH_KEY("COMPONENT_ASSAULTRIFLE_MK2_CAMO_06"),     // Perseus
					GET_HASH_KEY("COMPONENT_ASSAULTRIFLE_MK2_CAMO_07"),     // Leopard
					GET_HASH_KEY("COMPONENT_ASSAULTRIFLE_MK2_CAMO_08"),     // Zebra
					GET_HASH_KEY("COMPONENT_ASSAULTRIFLE_MK2_CAMO_09"),     // Geometric
					GET_HASH_KEY("COMPONENT_ASSAULTRIFLE_MK2_CAMO_10"),     // Boom!
					GET_HASH_KEY("COMPONENT_ASSAULTRIFLE_MK2_CAMO_IND_01"), // Patriotic
				}, true);

			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_AR_FLSH"), g_Random.GetRandomInt(0, 1)); // Flashlight
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_AR_AFGRIP_02"), g_Random.GetRandomInt(0, 1)); // Grip
		}
		else if (weaponHash == GET_HASH_KEY("WEAPON_CARBINERIFLE_MK2"))
		{
			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_CARBINERIFLE_MK2_CLIP_01"),            // Default Clip
					GET_HASH_KEY("COMPONENT_CARBINERIFLE_MK2_CLIP_02"),            // Extended Clip
					GET_HASH_KEY("COMPONENT_CARBINERIFLE_MK2_CLIP_TRACER"),        // Tracer Rounds
					GET_HASH_KEY("COMPONENT_CARBINERIFLE_MK2_CLIP_INCENDIARY"),    // Incendiary Rounds
					GET_HASH_KEY("COMPONENT_CARBINERIFLE_MK2_CLIP_ARMORPIERCING"), // Armor Piercing Rounds
					GET_HASH_KEY("COMPONENT_CARBINERIFLE_MK2_CLIP_FMJ")            // Full Metal Jacket Rounds
				});

			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_AT_SIGHTS"),          // Holographic Sight
					GET_HASH_KEY("COMPONENT_AT_SCOPE_MACRO_MK2"), // Small Scope
					GET_HASH_KEY("COMPONENT_AT_SCOPE_MEDIUM_MK2") // Large Scope
				}, true);

			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_AT_CR_BARREL_01"), // Default Barrel
					GET_HASH_KEY("COMPONENT_AT_CR_BARREL_02")  // Heavy Barrel
				});

			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_AT_AR_SUPP"),   // Suppressor
					GET_HASH_KEY("COMPONENT_AT_MUZZLE_01"), // Flat Muzzle Brake
					GET_HASH_KEY("COMPONENT_AT_MUZZLE_02"), // Tactical Muzzle Brake
					GET_HASH_KEY("COMPONENT_AT_MUZZLE_03"), // Fat-End Muzzle Brake
					GET_HASH_KEY("COMPONENT_AT_MUZZLE_04"), // Precision Muzzle Brake
					GET_HASH_KEY("COMPONENT_AT_MUZZLE_05"), // Heavy Duty Muzzle Brake
					GET_HASH_KEY("COMPONENT_AT_MUZZLE_06"), // Slanted Muzzle Brake
					GET_HASH_KEY("COMPONENT_AT_MUZZLE_07")  // Split-End Muzzle Brake
				}, true);

			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_AT_SC_BARREL_01"), // Default Barrel
					GET_HASH_KEY("COMPONENT_AT_SC_BARREL_02")  // Heavy Barrel
				});

			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_CARBINERIFLE_MK2_CAMO"),        // Digital Camo
					GET_HASH_KEY("COMPONENT_CARBINERIFLE_MK2_CAMO_02"),     // Brushstroke Camo
					GET_HASH_KEY("COMPONENT_CARBINERIFLE_MK2_CAMO_03"),     // Woodland Camo
					GET_HASH_KEY("COMPONENT_CARBINERIFLE_MK2_CAMO_04"),     // Skull
					GET_HASH_KEY("COMPONENT_CARBINERIFLE_MK2_CAMO_05"),     // Sessanta Nove
					GET_HASH_KEY("COMPONENT_CARBINERIFLE_MK2_CAMO_06"),     // Perseus
					GET_HASH_KEY("COMPONENT_CARBINERIFLE_MK2_CAMO_07"),     // Leopard
					GET_HASH_KEY("COMPONENT_CARBINERIFLE_MK2_CAMO_08"),     // Zebra
					GET_HASH_KEY("COMPONENT_CARBINERIFLE_MK2_CAMO_09"),     // Geometric
					GET_HASH_KEY("COMPONENT_CARBINERIFLE_MK2_CAMO_10"),     // Boom!
					GET_HASH_KEY("COMPONENT_CARBINERIFLE_MK2_CAMO_IND_01"), // Patriotic
				}, true);

			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_AR_FLSH"), g_Random.GetRandomInt(0, 1)); // Flashlight
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_AR_AFGRIP_02"), g_Random.GetRandomInt(0, 1)); // Grip
		}
		else if (weaponHash == GET_HASH_KEY("WEAPON_COMPACTRIFLE"))
		{
			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_COMPACTRIFLE_CLIP_01"), // Default Clip
					GET_HASH_KEY("COMPONENT_COMPACTRIFLE_CLIP_02"), // Extended Clip
					GET_HASH_KEY("COMPONENT_COMPACTRIFLE_CLIP_03")  // Drum Magazine
				});
		}
		else if (weaponHash == GET_HASH_KEY("WEAPON_MILITARYRIFLE"))
		{
			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_MILITARYRIFLE_CLIP_01"), // Default Clip
					GET_HASH_KEY("COMPONENT_MILITARYRIFLE_CLIP_02")  // Extended Clip
				});

			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_MILITARYRIFLE_SIGHT_01"), // Iron Sights
					GET_HASH_KEY("COMPONENT_AT_SCOPE_SMALL")          // Scope
				}, true);

			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_AR_FLSH"), g_Random.GetRandomInt(0, 1)); // Flashlight
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_AR_SUPP"), g_Random.GetRandomInt(0, 1)); // Suppressor
		}
		else if (weaponHash == GET_HASH_KEY("WEAPON_MG"))
		{
			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_MG_CLIP_01"), // Default Clip
					GET_HASH_KEY("COMPONENT_MG_CLIP_02")  // Extended Clip
				});

			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_SCOPE_SMALL_02"), g_Random.GetRandomInt(0, 1)); // Scope
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_MG_VARMOD_LOWRIDER"), g_Random.GetRandomInt(0, 1)); // Yusuf Amir Luxury Finish
		}
		else if (weaponHash == GET_HASH_KEY("WEAPON_COMBATMG"))
		{
			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_COMBATMG_CLIP_01"), // Default Clip
					GET_HASH_KEY("COMPONENT_COMBATMG_CLIP_02")  // Extended Clip
				});

			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_SCOPE_MEDIUM"), g_Random.GetRandomInt(0, 1)); // Scope
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_AR_AFGRIP"), g_Random.GetRandomInt(0, 1)); // Grip
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_COMBATMG_VARMOD_LOWRIDER"), g_Random.GetRandomInt(0, 1)); // Etched Gun Metal Finish
		}
		else if (weaponHash == GET_HASH_KEY("WEAPON_COMBATMG_MK2"))
		{
			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_COMBATMG_MK2_CLIP_01"),            // Default Clip
					GET_HASH_KEY("COMPONENT_COMBATMG_MK2_CLIP_02"),            // Extended Clip
					GET_HASH_KEY("COMPONENT_COMBATMG_MK2_CLIP_TRACER"),        // Tracer Rounds
					GET_HASH_KEY("COMPONENT_COMBATMG_MK2_CLIP_INCENDIARY"),    // Incendiary Rounds
					GET_HASH_KEY("COMPONENT_COMBATMG_MK2_CLIP_ARMORPIERCING"), // Armor Piercing Rounds
					GET_HASH_KEY("COMPONENT_COMBATMG_MK2_CLIP_FMJ")            // Full Metal Jacket Rounds
				});

			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_AT_SIGHTS"),          // Holographic Sight
					GET_HASH_KEY("COMPONENT_AT_SCOPE_SMALL_MK2"), // Medium Scope
					GET_HASH_KEY("COMPONENT_AT_SCOPE_MEDIUM_MK2") // Large Scope
				}, true);

			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_AT_MUZZLE_01"), // Flat Muzzle Brake
					GET_HASH_KEY("COMPONENT_AT_MUZZLE_02"), // Tactical Muzzle Brake
					GET_HASH_KEY("COMPONENT_AT_MUZZLE_03"), // Fat-End Muzzle Brake
					GET_HASH_KEY("COMPONENT_AT_MUZZLE_04"), // Precision Muzzle Brake
					GET_HASH_KEY("COMPONENT_AT_MUZZLE_05"), // Heavy Duty Muzzle Brake
					GET_HASH_KEY("COMPONENT_AT_MUZZLE_06"), // Slanted Muzzle Brake
					GET_HASH_KEY("COMPONENT_AT_MUZZLE_07")  // Split-End Muzzle Brake
				}, true);

			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_AT_MG_BARREL_01"), // Default Barrel
					GET_HASH_KEY("COMPONENT_AT_MG_BARREL_02")  // Heavy Barrel
				});

			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_COMBATMG_MK2_CAMO"),       // Digital Camo
					GET_HASH_KEY("COMPONENT_COMBATMG_MK2_CAMO_02"),    // Brushstroke Camo
					GET_HASH_KEY("COMPONENT_COMBATMG_MK2_CAMO_03"),    // Woodland Camo
					GET_HASH_KEY("COMPONENT_COMBATMG_MK2_CAMO_04"),    // Skull
					GET_HASH_KEY("COMPONENT_COMBATMG_MK2_CAMO_05"),    // Sessanta Nove
					GET_HASH_KEY("COMPONENT_COMBATMG_MK2_CAMO_06"),    // Perseus
					GET_HASH_KEY("COMPONENT_COMBATMG_MK2_CAMO_07"),    // Leopard
					GET_HASH_KEY("COMPONENT_COMBATMG_MK2_CAMO_08"),    // Zebra
					GET_HASH_KEY("COMPONENT_COMBATMG_MK2_CAMO_09"),    // Geometric
					GET_HASH_KEY("COMPONENT_COMBATMG_MK2_CAMO_10"),    // Boom!
					GET_HASH_KEY("COMPONENT_COMBATMG_MK2_CAMO_IND_01") // Patriotic
				}, true);

			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_AR_AFGRIP_02"), g_Random.GetRandomInt(0, 1)); // Grip
		}
		else if (weaponHash == GET_HASH_KEY("WEAPON_GUSENBERG"))
		{
			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_GUSENBERG_CLIP_01"), // Default Clip
					GET_HASH_KEY("COMPONENT_GUSENBERG_CLIP_02")  // Extended Clip
				});
		}
		else if (weaponHash == GET_HASH_KEY("WEAPON_SNIPERRIFLE"))
		{
			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_AT_SCOPE_LARGE"), // Scope
					GET_HASH_KEY("COMPONENT_AT_SCOPE_MAX")    // Advanced Scope
				});

			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_AR_SUPP_02"), g_Random.GetRandomInt(0, 1)); // Suppressor
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_SNIPERRIFLE_VARMOD_LUXE"), g_Random.GetRandomInt(0, 1)); // Etched Wood Grip Finish
		}
		else if (weaponHash == GET_HASH_KEY("WEAPON_HEAVYSNIPER"))
		{
			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_AT_SCOPE_LARGE"), // Scope
					GET_HASH_KEY("COMPONENT_AT_SCOPE_MAX")    // Advanced Scope
				});
		}
		else if (weaponHash == GET_HASH_KEY("WEAPON_MARKSMANRIFLE_MK2"))
		{
			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_MARKSMANRIFLE_MK2_CLIP_01"),            // Default Clip
					GET_HASH_KEY("COMPONENT_MARKSMANRIFLE_MK2_CLIP_02"),            // Extended Clip
					GET_HASH_KEY("COMPONENT_MARKSMANRIFLE_MK2_CLIP_TRACER"),        // Tracer Rounds
					GET_HASH_KEY("COMPONENT_MARKSMANRIFLE_MK2_CLIP_INCENDIARY"),    // Incendiary Rounds
					GET_HASH_KEY("COMPONENT_MARKSMANRIFLE_MK2_CLIP_ARMORPIERCING"), // Armor Piercing Rounds
					GET_HASH_KEY("COMPONENT_MARKSMANRIFLE_MK2_CLIP_FMJ")            // Full Metal Jacket Rounds
				});

			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_AT_SIGHTS"),                    // Holographic Sight
					GET_HASH_KEY("COMPONENT_AT_SCOPE_MEDIUM_MK2"),          // Large Scope
					GET_HASH_KEY("COMPONENT_AT_SCOPE_LARGE_FIXED_ZOOM_MK2") // Zoom Scope
				}, true);

			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_AT_AR_SUPP"),   // Suppressor
					GET_HASH_KEY("COMPONENT_AT_MUZZLE_01"), // Flat Muzzle Brake
					GET_HASH_KEY("COMPONENT_AT_MUZZLE_02"), // Tactical Muzzle Brake
					GET_HASH_KEY("COMPONENT_AT_MUZZLE_03"), // Fat-End Muzzle Brake
					GET_HASH_KEY("COMPONENT_AT_MUZZLE_04"), // Precision Muzzle Brake
					GET_HASH_KEY("COMPONENT_AT_MUZZLE_05"), // Heavy Duty Muzzle Brake
					GET_HASH_KEY("COMPONENT_AT_MUZZLE_06"), // Slanted Muzzle Brake
					GET_HASH_KEY("COMPONENT_AT_MUZZLE_07")  // Split-End Muzzle Brake
				}, true);

			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_AT_MRFL_BARREL_01"), // Default Barrel
					GET_HASH_KEY("COMPONENT_AT_MRFL_BARREL_02")  // Heavy Barrel
				});

			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_MARKSMANRIFLE_MK2_CAMO"),       // Digital Camo
					GET_HASH_KEY("COMPONENT_MARKSMANRIFLE_MK2_CAMO_02"),    // Brushstroke Camo
					GET_HASH_KEY("COMPONENT_MARKSMANRIFLE_MK2_CAMO_03"),    // Woodland Camo
					GET_HASH_KEY("COMPONENT_MARKSMANRIFLE_MK2_CAMO_04"),    // Skull
					GET_HASH_KEY("COMPONENT_MARKSMANRIFLE_MK2_CAMO_05"),    // Sessanta Nove
					GET_HASH_KEY("COMPONENT_MARKSMANRIFLE_MK2_CAMO_06"),    // Perseus
					GET_HASH_KEY("COMPONENT_MARKSMANRIFLE_MK2_CAMO_07"),    // Leopard
					GET_HASH_KEY("COMPONENT_MARKSMANRIFLE_MK2_CAMO_08"),    // Zebra
					GET_HASH_KEY("COMPONENT_MARKSMANRIFLE_MK2_CAMO_09"),    // Geometric
					GET_HASH_KEY("COMPONENT_MARKSMANRIFLE_MK2_CAMO_10"),    // Boom!
					GET_HASH_KEY("COMPONENT_MARKSMANRIFLE_MK2_CAMO_IND_01") // Patriotic
				}, true);

			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_AR_FLSH"), g_Random.GetRandomInt(0, 1)); // Flashlight
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_AR_AFGRIP_02"), g_Random.GetRandomInt(0, 1)); // Grip
		}
		else if (weaponHash == GET_HASH_KEY("WEAPON_HEAVYSNIPER_MK2"))
		{
			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_HEAVYSNIPER_MK2_CLIP_01"),            // Default Clip
					GET_HASH_KEY("COMPONENT_HEAVYSNIPER_MK2_CLIP_02"),            // Extended Clip
					GET_HASH_KEY("COMPONENT_HEAVYSNIPER_MK2_CLIP_INCENDIARY"),    // Incendiary Rounds
					GET_HASH_KEY("COMPONENT_HEAVYSNIPER_MK2_CLIP_ARMORPIERCING"), // Armor Piercing Rounds
					GET_HASH_KEY("COMPONENT_HEAVYSNIPER_MK2_CLIP_FMJ"),           // Full Metal Jacket Rounds
					GET_HASH_KEY("COMPONENT_HEAVYSNIPER_MK2_CLIP_EXPLOSIVE")      // Explosive Rounds
				});

			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_AT_SCOPE_LARGE_MK2"), // Zoom Scope
					GET_HASH_KEY("COMPONENT_AT_SCOPE_MAX"),       // Advanced Scope
					GET_HASH_KEY("COMPONENT_AT_SCOPE_NV"),        // Night Vision Scope
					GET_HASH_KEY("COMPONENT_AT_SCOPE_THERMAL")    // Thermal Scope
				});

			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_AT_SR_SUPP_03"), // Suppressor
					GET_HASH_KEY("COMPONENT_AT_MUZZLE_08"),  // Squared Muzzle Brake
					GET_HASH_KEY("COMPONENT_AT_MUZZLE_09")   // Bell-End Muzzle Brake
				}, true);

			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_AT_SR_BARREL_01"), // Default Barrel
					GET_HASH_KEY("COMPONENT_AT_SR_BARREL_02")  // Heavy Barrel
				});

			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_HEAVYSNIPER_MK2_CAMO"),       // Digital Camo
					GET_HASH_KEY("COMPONENT_HEAVYSNIPER_MK2_CAMO_02"),    // Brushstroke Camo
					GET_HASH_KEY("COMPONENT_HEAVYSNIPER_MK2_CAMO_03"),    // Woodland Camo
					GET_HASH_KEY("COMPONENT_HEAVYSNIPER_MK2_CAMO_04"),    // Skull
					GET_HASH_KEY("COMPONENT_HEAVYSNIPER_MK2_CAMO_05"),    // Sessanta Nove
					GET_HASH_KEY("COMPONENT_HEAVYSNIPER_MK2_CAMO_06"),    // Perseus
					GET_HASH_KEY("COMPONENT_HEAVYSNIPER_MK2_CAMO_07"),    // Leopard
					GET_HASH_KEY("COMPONENT_HEAVYSNIPER_MK2_CAMO_08"),    // Zebra
					GET_HASH_KEY("COMPONENT_HEAVYSNIPER_MK2_CAMO_09"),    // Geometric
					GET_HASH_KEY("COMPONENT_HEAVYSNIPER_MK2_CAMO_10"),    // Boom!
					GET_HASH_KEY("COMPONENT_HEAVYSNIPER_MK2_CAMO_IND_01") // Patriotic
				}, true);
		}
		else if (weaponHash == GET_HASH_KEY("WEAPON_MARKSMANRIFLE"))
		{
			GiveRandomWeaponComponent(ped, weaponHash,
				{
					GET_HASH_KEY("COMPONENT_MARKSMANRIFLE_CLIP_01"), // Default Clip
					GET_HASH_KEY("COMPONENT_MARKSMANRIFLE_CLIP_02")  // Extended Clip
				});

			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_SCOPE_LARGE_FIXED_ZOOM"), g_Random.GetRandomInt(0, 1)); // Scope
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_AR_FLSH"), g_Random.GetRandomInt(0, 1)); // Flashlight
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_AR_SUPP"), g_Random.GetRandomInt(0, 1)); // Suppressor
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_AR_AFGRIP"), g_Random.GetRandomInt(0, 1)); // Grip
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_MARKSMANRIFLE_VARMOD_LUXE"), g_Random.GetRandomInt(0, 1)); // Yusuf Amir Luxury Finish
		}
		else if (weaponHash == GET_HASH_KEY("WEAPON_GRENADELAUNCHER"))
		{
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_AR_FLSH"), g_Random.GetRandomInt(0, 1)); // Flashlight
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_AR_AFGRIP"), g_Random.GetRandomInt(0, 1)); // Grip
			SetWeaponComponentActive(ped, weaponHash, GET_HASH_KEY("COMPONENT_AT_SCOPE_SMALL"), g_Random.GetRandomInt(0, 1)); // Scope
		}

		SET_PED_WEAPON_TINT_INDEX(ped, weaponHash, g_Random.GetRandomInt(0, 7));

		if (equip)
		{
			SET_CURRENT_PED_WEAPON(ped, weaponHash, true);
		}
	}
}