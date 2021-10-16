#pragma once

#include "Natives.h"
#include "Memory/Hooks/ScriptThreadRunHook.h"
#include "Memory/Hooks/HandleToEntityStructHook.h"
#include "Random.h"

struct VehicleUpgradeCollection
{
	struct VehicleMod
	{
		int modIndex;
		BOOL customTyres;
		BOOL enabled;
	};

	static constexpr int NUM_VEH_MODS = 50;
	static constexpr int NUM_VEH_EXTRAS = 25;

	VehicleUpgradeCollection()
	{
	}

	VehicleUpgradeCollection(Vehicle veh, BOOL random)
	{
		if (random)
		{
			wheelType = g_Random.GetRandomInt(0, 7);

			for (int i = 0; i < NUM_VEH_MODS; i++)
			{
				VehicleMod mod{};

				int max = GET_NUM_VEHICLE_MODS(veh, i);
				if (max > 0)
				{
					mod.modIndex = g_Random.GetRandomInt(0, max - 1);
					mod.customTyres = g_Random.GetRandomInt(0, 1);
				}

				mod.enabled = g_Random.GetRandomInt(0, 1);

				vehModValues[i] = mod;
			}

			tyresCanBurst = g_Random.GetRandomInt(0, 1);

			windowTint = g_Random.GetRandomInt(0, 6);

			float customColourChance = 1.f;
			if (g_Random.GetRandomInt(1, 3) <= 2)
			{
				primaryColour = g_Random.GetRandomInt(0, 160);
				secondaryColour = g_Random.GetRandomInt(0, 160);

				colourMode |= 0b1;

				customColourChance = .5f;
			}

			if (g_Random.GetRandomFloat(0.f, 1.f) <= customColourChance)
			{
				customPrimaryColour[0] = g_Random.GetRandomInt(0, 255); // r
				customPrimaryColour[1] = g_Random.GetRandomInt(0, 255); // g
				customPrimaryColour[2] = g_Random.GetRandomInt(0, 255); // b

				customSecondaryColour[0] = g_Random.GetRandomInt(0, 255); // r
				customSecondaryColour[1] = g_Random.GetRandomInt(0, 255); // g
				customSecondaryColour[2] = g_Random.GetRandomInt(0, 255); // b

				colourMode |= 0b10;
			}

			pearlescentColour = g_Random.GetRandomInt(0, 160);
			wheelColour = g_Random.GetRandomInt(0, 160);

			for (int i = 0; i < NUM_VEH_EXTRAS; i++)
			{
				if (DOES_EXTRA_EXIST(veh, i))
				{
					extras[i] = g_Random.GetRandomInt(0, 1);
				}
			}

			neonLightsColour[0] = g_Random.GetRandomInt(0, 255); // r
			neonLightsColour[1] = g_Random.GetRandomInt(0, 255); // g
			neonLightsColour[2] = g_Random.GetRandomInt(0, 255); // b

			xenonLightsColour = g_Random.GetRandomInt(0, 12);

			tyreSmokeColour[0] = g_Random.GetRandomInt(0, 255); // r
			tyreSmokeColour[1] = g_Random.GetRandomInt(0, 255); // g
			tyreSmokeColour[2] = g_Random.GetRandomInt(0, 255); // b

			int liveryCount = GET_VEHICLE_LIVERY_COUNT(veh);
			if (liveryCount > 0)
			{
				livery = g_Random.GetRandomInt(0, liveryCount - 1);
			}
			else
			{
				livery = -1;
			}

			int roofLiveryCount = _GET_VEHICLE_ROOF_LIVERY_COUNT(veh);
			if (roofLiveryCount > 0)
			{
				roofLivery = g_Random.GetRandomInt(0, roofLiveryCount - 1);
			}
			else
			{
				roofLivery = -1;
			}
		}
		else
		{
			// NOT IMPLEMENTED
		}
	}

	int wheelType;

	VehicleMod vehModValues[NUM_VEH_MODS];

	BOOL tyresCanBurst;

	int windowTint;

	// 01b: colour index, 10b: custom colour, 11b: index and custom
	int colourMode;

	int primaryColour;
	int customPrimaryColour[3]; // 0: r, 1: g, 2: b

	int secondaryColour;
	int customSecondaryColour[3]; // 0: r, 1: g, 2: b

	int pearlescentColour;
	int wheelColour;

	BOOL extras[NUM_VEH_EXTRAS];

	int neonLightsColour[3]; // 0: r, 1: g, 2: b

	int xenonLightsColour;

	int tyreSmokeColour[3]; // 0: r, 1: g, 2: b

	int livery;
	int roofLivery;
};

inline void SetVehicleUpgrades(Vehicle veh, VehicleUpgradeCollection upgrades)
{
	SET_VEHICLE_MOD_KIT(veh, 0);

	SET_VEHICLE_WHEEL_TYPE(veh, upgrades.wheelType);

	for (int i = 0; i < VehicleUpgradeCollection::NUM_VEH_MODS; i++)
	{
		int max = GET_NUM_VEHICLE_MODS(veh, i);
		if (max > 0)
		{
			SET_VEHICLE_MOD(veh, i, upgrades.vehModValues[i].modIndex, upgrades.vehModValues[i].customTyres);
		}

		TOGGLE_VEHICLE_MOD(veh, i, upgrades.vehModValues[i].enabled);
	}

	SET_VEHICLE_TYRES_CAN_BURST(veh, upgrades.tyresCanBurst);
	SET_VEHICLE_WINDOW_TINT(veh, upgrades.windowTint);

	if ((upgrades.colourMode & 0b10) != 0) // No custom colour
	{
		CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh);
		CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh);
	}

	if (upgrades.colourMode & 0b01) // Colour index
	{
		SET_VEHICLE_COLOURS(veh, upgrades.primaryColour, upgrades.secondaryColour);
	}

	if (upgrades.colourMode & 0b10) // Custom colour
	{
		SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, upgrades.customPrimaryColour[0], upgrades.customPrimaryColour[1], upgrades.customPrimaryColour[2]);
		SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, upgrades.customSecondaryColour[0], upgrades.customSecondaryColour[1], upgrades.customSecondaryColour[2]);
	}

	SET_VEHICLE_EXTRA_COLOURS(veh, upgrades.pearlescentColour, upgrades.wheelColour);

	for (int i = 0; i < VehicleUpgradeCollection::NUM_VEH_EXTRAS; i++)
	{
		if (DOES_EXTRA_EXIST(veh, i))
		{
			SET_VEHICLE_EXTRA(veh, i, upgrades.extras[i]);
		}
	}

	_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, upgrades.neonLightsColour[0], upgrades.neonLightsColour[1], upgrades.neonLightsColour[2]);
	for (int i = 0; i < 4; i++)
	{
		_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, i, true);
	}

	_SET_VEHICLE_XENON_LIGHTS_COLOR(veh, upgrades.xenonLightsColour);

	SET_VEHICLE_TYRE_SMOKE_COLOR(veh, upgrades.tyreSmokeColour[0], upgrades.tyreSmokeColour[1], upgrades.tyreSmokeColour[2]);

	if (upgrades.livery > 0)
	{
		SET_VEHICLE_LIVERY(veh, upgrades.livery);
	}

	if (upgrades.roofLivery > 0)
	{
		_SET_VEHICLE_ROOF_LIVERY(veh, upgrades.roofLivery);
	}
}

inline void SetVehicleRandomUpgrades(Vehicle veh)
{
	SetVehicleUpgrades(veh, VehicleUpgradeCollection(veh, true));
}

inline Vehicle CreateTempVehicle(Hash ulModel, float fPosX, float fPosY, float fPosZ, float fHeading)
{
	LoadModel(ulModel);

	Vehicle veh = CREATE_VEHICLE(ulModel, fPosX, fPosY, fPosZ, fHeading, true, false, false);
	SET_MODEL_AS_NO_LONGER_NEEDED(ulModel);

	Vehicle dummy = veh;
	SET_VEHICLE_AS_NO_LONGER_NEEDED(&dummy);

	return veh;
}

inline Vehicle CreateTempVehicleOnPlayerPos(Hash ulModel, float fHeading)
{
	LoadModel(ulModel);

	Vector3 playerPos = GET_ENTITY_COORDS(PLAYER_PED_ID(), false);

	Vehicle veh = CREATE_VEHICLE(ulModel, playerPos.x, playerPos.y, playerPos.z, fHeading, true, false, false);
	SET_MODEL_AS_NO_LONGER_NEEDED(ulModel);

	Vehicle dummy = veh;
	SET_VEHICLE_AS_NO_LONGER_NEEDED(&dummy);

	return veh;
}

inline void SetSurroundingPedsInVehicles(Hash vehicleHash, float maxDistance, float maxCloneDistance)
{
	Ped playerPed = PLAYER_PED_ID();
	Vector3 playerPos = GET_ENTITY_COORDS(playerPed, true);

	BOOL hasUpgrades = false;
	VehicleUpgradeCollection upgrades;

	for (Ped ped : GetAllPeds())
	{
		if (!IS_PED_A_PLAYER(ped) && !IS_PED_DEAD_OR_DYING(ped, false))
		{
			Vector3 pedPos = GET_ENTITY_COORDS(ped, true);
			float distance = pedPos.DistanceTo(playerPos);
			//check if player is far away from entity
			if (maxDistance <= 0 || distance <= maxDistance)
			{
				if (IS_PED_IN_ANY_VEHICLE(ped, false))
				{
					Vehicle veh = GET_VEHICLE_PED_IS_IN(ped, false);

					if (GET_ENTITY_MODEL(veh) == vehicleHash)
					{
						continue;
					}
				}

				float pedHeading = GET_ENTITY_HEADING(ped);
				Vector3 vel = GET_ENTITY_VELOCITY(ped);

				SET_ENTITY_COORDS(ped, pedPos.x, pedPos.y, pedPos.z + 10.f, false, false, false, false);

				SET_PED_COMBAT_ATTRIBUTES(ped, 3, false); // Don't allow them to leave vehicle by themselves

				SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(ped, true);

				Vehicle veh = CreateTempVehicle(vehicleHash, pedPos.x, pedPos.y, pedPos.z, pedHeading);
				if (!hasUpgrades)
				{
					upgrades = VehicleUpgradeCollection(veh, true);
					hasUpgrades = true;
				}

				SetVehicleUpgrades(veh, upgrades);

				SET_PED_INTO_VEHICLE(ped, veh, -1);

				if (distance <= maxCloneDistance)
				{
					int pedType = GET_PED_TYPE(ped);
					Hash pedModel = GET_ENTITY_MODEL(ped);
					for (int i = 0; i < g_MetaInfo.m_fChaosMultiplier - 1; i++)
					{
						if (!ARE_ANY_VEHICLE_SEATS_FREE(veh))
							break;

						Ped clone = CreatePoolPed(pedType, pedModel, 0.f, 0.f, 0.f, 0.f);
						SET_PED_INTO_VEHICLE(clone, veh, -2);
						CLONE_PED_TO_TARGET(ped, clone);
						SET_PED_COMBAT_ATTRIBUTES(clone, 3, false); // Don't allow them to leave vehicle by themselves

						SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(clone, true);
					}
				}

				SET_VEHICLE_ENGINE_ON(veh, true, true, true);
				SET_ENTITY_VELOCITY(veh, vel.x, vel.y, vel.z);

				TASK_VEHICLE_MISSION_PED_TARGET(ped, veh, playerPed, 13, 9999.f, 4176732, .0f, .0f, false);

				WAIT(0);
			}
		}
	}
}

struct SeatPed
{
	Ped ped;
	int seatIndex;
};

inline Vehicle CreateRandomVehicleWithPeds(Vehicle oldHandle, std::vector<SeatPed> seatPeds, bool addToPool, Vector3 coords, Vector3 rotation, bool engineRunning, Vector3 velocity)
{
	static const std::vector<Hash>& vehicleModels = Memory::GetAllVehModels();
	if (vehicleModels.empty())
		return oldHandle;

	Hash newVehModel = 0;
	do
	{
		newVehModel = vehicleModels[g_Random.GetRandomInt(0, vehicleModels.size() - 1)];
	} while (GET_VEHICLE_MODEL_NUMBER_OF_SEATS(newVehModel) < seatPeds.size() || IS_THIS_MODEL_A_TRAIN(newVehModel) || GET_VEHICLE_MODEL_ACCELERATION(newVehModel) <= 0);

	if (!newVehModel)
		return oldHandle;

	int numberOfSeats = GET_VEHICLE_MODEL_NUMBER_OF_SEATS(newVehModel);

	Vehicle newVehicle;
	if (addToPool)
	{
		for (int i = 0; i < seatPeds.size(); i++)
		{
			Ped seatPed = seatPeds[i].ped;
			SET_ENTITY_COORDS(seatPed, coords.x, coords.y, coords.z + 5.f, 0, 0, 0, 0);
		}

		WAIT(100);

		newVehicle = CreatePoolVehicle(newVehModel, coords.x, coords.y, coords.z, 0.f);
	}
	else
	{
		LoadModel(newVehModel);
		newVehicle = CREATE_VEHICLE(newVehModel, coords.x, coords.y, coords.z, 0.f, true, true, true);
		SET_MODEL_AS_NO_LONGER_NEEDED(newVehModel);

		SET_ENTITY_AS_MISSION_ENTITY(newVehicle, false, true);
	}

	SET_ENTITY_ROTATION(newVehicle, rotation.x, rotation.y, rotation.z, 2, true);

	for (int i = 0; i < seatPeds.size(); i++)
	{
		SeatPed seatPed = seatPeds.at(i);
		int seatIndex = seatPed.seatIndex;
		if (seatIndex >= numberOfSeats || !IS_VEHICLE_SEAT_FREE(newVehicle, seatIndex, 0))
		{
			seatIndex = -2;
		}

		SET_PED_INTO_VEHICLE(seatPed.ped, newVehicle, seatIndex);
	}

	if (engineRunning)
	{
		SET_VEHICLE_ENGINE_ON(newVehicle, true, true, false);
	}

	SET_ENTITY_VELOCITY(newVehicle, velocity.x, velocity.y, velocity.z);

	if (oldHandle)
	{
		bool shouldUseHook = IS_ENTITY_A_MISSION_ENTITY(oldHandle);
		Entity copy = oldHandle;
		SET_ENTITY_AS_MISSION_ENTITY(copy, true, true);

		if (shouldUseHook)
		{
			Hooks::EnableScriptThreadBlock();
		}
		DELETE_VEHICLE(&copy);
		if (shouldUseHook)
		{
			Hooks::ProxyEntityHandle(oldHandle, newVehicle);
			Hooks::DisableScriptThreadBlock();
		}
	}

	SetVehicleRandomUpgrades(newVehicle);

	return newVehicle;
}

inline Vehicle ReplaceVehicle(Vehicle veh, bool addToPool)
{
	static const std::vector<Hash>& vehicleModels = Memory::GetAllVehModels();
	if (vehicleModels.empty())
		return veh;

	std::vector<SeatPed> vehPeds;
	int numberOfSeats = GET_VEHICLE_MODEL_NUMBER_OF_SEATS(GET_ENTITY_MODEL(veh));
	for (int i = -1; i < numberOfSeats - 1; i++)
	{
		if (!IS_VEHICLE_SEAT_FREE(veh, i, false))
		{
			Ped ped = GET_PED_IN_VEHICLE_SEAT(veh, i, false);
			SeatPed seatPed = { ped, i };
			vehPeds.push_back(seatPed);
		}
	}

	Vector3 rotation = GET_ENTITY_ROTATION(veh, 2);
	Vector3 vehCoords = GET_ENTITY_COORDS(veh, 0);
	bool engineRunning = GET_IS_VEHICLE_ENGINE_RUNNING(veh);
	Vector3 velocity = GET_ENTITY_VELOCITY(veh);

	return CreateRandomVehicleWithPeds(veh, vehPeds, addToPool, vehCoords, rotation, engineRunning, velocity);
}

inline Vehicle ReplacePlayerVehicle()
{
	Ped player = PLAYER_PED_ID();
	if (IS_PED_IN_ANY_VEHICLE(player, false))
	{
		return ReplaceVehicle(GET_VEHICLE_PED_IS_IN(player, false), false);
	}
	else
	{
		std::vector<SeatPed> peds = { { player, -1 } };
		Vector3 coords = GET_ENTITY_COORDS(player, 0);
		Vector3 rotation = GET_ENTITY_ROTATION(player, 2);
		Vector3 velocity = GET_ENTITY_VELOCITY(player);

		return CreateRandomVehicleWithPeds(0, peds, false, coords, rotation, false, velocity);
	}
}