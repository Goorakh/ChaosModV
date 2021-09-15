/*
	Effect by Gorakh
*/

#include <stdafx.h>
#include <Memory\Hooks\HandleToEntityStructHook.h>
#include <Memory\Hooks\ScriptThreadRunHook.h>

static void OnStart()
{
	Ped player = PLAYER_PED_ID();

	Hash playerWeapon;
	if (!GET_CURRENT_PED_WEAPON(player, &playerWeapon, 1))
	{
		playerWeapon = 0;
	}

	Hash playerModel = GET_ENTITY_MODEL(player);
	int playerPedType = GET_PED_TYPE(player);

	int count = 5;
	for (Ped ped : GetAllPeds())
	{
		if (ped != player)
		{
			bool isMissionEntity = IS_ENTITY_A_MISSION_ENTITY(ped);

			Ped newPed = CREATE_PED(playerPedType, playerModel, 0.f, 0.f, 0.f, 0.f, 1, 0);
			CLONE_PED_TO_TARGET(player, newPed);

			SET_PED_RELATIONSHIP_GROUP_HASH(newPed, GET_PED_RELATIONSHIP_GROUP_HASH(ped));

			SET_ENTITY_ALPHA(newPed, GET_ENTITY_ALPHA(ped), false);
			SET_ENTITY_HEALTH(newPed, GET_ENTITY_HEALTH(ped), 0);

			if (IS_PED_IN_ANY_VEHICLE(ped, false))
			{
				Vehicle pedVeh = GET_VEHICLE_PED_IS_IN(ped, false);
				int numSeats = GET_VEHICLE_MODEL_NUMBER_OF_SEATS(GET_ENTITY_MODEL(pedVeh));

				int seatIndex = -2;
				for (int i = -1; i < numSeats - 1; i++)
				{
					if (!IS_VEHICLE_SEAT_FREE(pedVeh, i, 0) && GET_PED_IN_VEHICLE_SEAT(pedVeh, i, 0) == ped)
					{
						seatIndex = i;
						break;
					}
				}

				TASK_LEAVE_VEHICLE(ped, pedVeh, 16);
				SET_PED_INTO_VEHICLE(newPed, pedVeh, seatIndex);

				if (seatIndex == -1 && !isMissionEntity)
				{
					TASK_VEHICLE_DRIVE_WANDER(newPed, pedVeh, 9999.f, 786603);
				}
			}
			else
			{
				Vector3 pedCoords = GET_ENTITY_COORDS(ped, 0);
				SET_ENTITY_COORDS(newPed, pedCoords.x, pedCoords.y, pedCoords.z, 0, 0, 0, 0);

				Vector3 pedRot = GET_ENTITY_ROTATION(ped, 2);
				SET_ENTITY_ROTATION(newPed, pedRot.x, pedRot.y, pedRot.z, 2, 1);

				if (!isMissionEntity)
				{
					TASK_WANDER_STANDARD(newPed, 10.f, 10);
				}
			}

			if (playerWeapon)
			{
				GIVE_WEAPON_TO_PED(ped, playerWeapon, 9999, false, true);
				SET_CURRENT_PED_WEAPON(ped, playerWeapon, true);
			}

			// ==== From VehsReplaceVehicle.cpp ====
			Entity copy = ped;
			SET_ENTITY_AS_MISSION_ENTITY(copy, true, true);

			if (isMissionEntity)
			{
				Hooks::EnableScriptThreadBlock();
			}
			DELETE_PED(&copy);
			if (isMissionEntity)
			{
				Hooks::ProxyEntityHandle(ped, newPed);
				Hooks::DisableScriptThreadBlock();
			}
			// ==== From VehsReplaceVehicle.cpp ====

			if (--count == 0)
			{
				WAIT(0);
				count = 5;
			}
		}
	}

	if (IS_PED_IN_ANY_VEHICLE(player, false))
	{
		Vehicle playerVeh = GET_VEHICLE_PED_IS_IN(player, false);
		std::vector<Vehicle> spawnedVehs = SetSurroundingPedsInVehicles(GET_ENTITY_MODEL(playerVeh), -1);

		int count = 5;
		for (Vehicle veh : spawnedVehs)
		{
			COPY_VEHICLE_DAMAGES(playerVeh, veh);

			// ======= Copy vehicle mods ======= //
			SET_VEHICLE_MOD_KIT(veh, 0);
			for (int i = 0; i < 50; i++)
			{
				int modIndex = GET_VEHICLE_MOD(playerVeh, i);
				if (modIndex > 0)
				{
					SET_VEHICLE_MOD(veh, i, modIndex, true);
				}

				TOGGLE_VEHICLE_MOD(veh, i, true);
			}

			SET_VEHICLE_TYRES_CAN_BURST(veh, GET_VEHICLE_TYRES_CAN_BURST(playerVeh));
			SET_VEHICLE_WINDOW_TINT(veh, GET_VEHICLE_WINDOW_TINT(playerVeh));

			if (GET_IS_VEHICLE_PRIMARY_COLOUR_CUSTOM(playerVeh))
			{
				int r, g, b;
				GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(playerVeh, &r, &g, &b);
				SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, r, g, b);
			}
			else
			{
				int primary, secondary;
				GET_VEHICLE_COLOURS(playerVeh, &primary, &secondary);
				SET_VEHICLE_COLOURS(veh, primary, secondary);
			}

			if (GET_IS_VEHICLE_SECONDARY_COLOUR_CUSTOM(playerVeh))
			{
				int r, g, b;
				GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(playerVeh, &r, &g, &b);
				SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, r, g, b);
			}
			else
			{
				int primary, secondary;
				GET_VEHICLE_COLOURS(playerVeh, &primary, &secondary);
				SET_VEHICLE_COLOURS(veh, primary, secondary);
			}

			bool hasNeonLights = false;
			for (int i = 0; i < 4; i++)
			{
				if (_IS_VEHICLE_NEON_LIGHT_ENABLED(playerVeh, i))
				{
					hasNeonLights = true;
				}

				_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, i, _IS_VEHICLE_NEON_LIGHT_ENABLED(playerVeh, i));
			}

			if (hasNeonLights)
			{
				int r, g, b;
				_GET_VEHICLE_NEON_LIGHTS_COLOUR(playerVeh, &r, &g, &b);
				_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, r, g, b);
			}

			_SET_VEHICLE_XENON_LIGHTS_COLOR(veh, _GET_VEHICLE_XENON_LIGHTS_COLOR(playerVeh));
			// ======= Copy vehicle mods ======= //

			if (--count == 0)
			{
				WAIT(0);
				count = 5;
			}
		}
	}
}

static RegisterEffect registerEffect(EFFECT_MISC_EVERYONE_IS_PLAYER, OnStart, EffectInfo
	{
		.Name = "Hey That's Me!",
		.Id = "misc_everyone_is_player"
	}
);
