#pragma once

#include "Natives.h"
#include "Memory/Hooks/ScriptThreadRunHook.h"
#include "Memory/Hooks/HandleToEntityStructHook.h"
#include "Random.h"

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

inline void SetSurroundingPedsInVehicles(Hash vehicleHash, int maxDistance)
{
	Ped playerPed = PLAYER_PED_ID();
	Vector3 playerPos = GET_ENTITY_COORDS(playerPed, true);

	for (Ped ped : GetAllPeds())
	{
		if (!IS_PED_A_PLAYER(ped) && !IS_PED_DEAD_OR_DYING(ped, false))
		{
			Vector3 pedPos = GET_ENTITY_COORDS(ped, true);
			//check if player is far away from entity
			if (maxDistance <= 0 || pedPos.DistanceTo(playerPos) <= maxDistance)
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

				SET_PED_INTO_VEHICLE(ped, veh, -1);

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

				SET_VEHICLE_ENGINE_ON(veh, true, true, true);
				SET_ENTITY_VELOCITY(veh, vel.x, vel.y, vel.z);

				TASK_VEHICLE_MISSION_PED_TARGET(ped, veh, playerPed, 13, 9999.f, 4176732, .0f, .0f, false);
			}
		}
	}
}

inline void SetVehicleRandomUpgrades(Vehicle veh)
{
	SET_VEHICLE_MOD_KIT(veh, 0);

	SET_VEHICLE_WHEEL_TYPE(veh, g_Random.GetRandomInt(0, 7));

	for (int i = 0; i < 50; i++)
	{
		int max = GET_NUM_VEHICLE_MODS(veh, i);
		if (max > 0)
		{
			SET_VEHICLE_MOD(veh, i, g_Random.GetRandomInt(0, max - 1), g_Random.GetRandomInt(0, 1));
		}

		TOGGLE_VEHICLE_MOD(veh, i, g_Random.GetRandomInt(0, 1));
	}

	SET_VEHICLE_TYRES_CAN_BURST(veh, g_Random.GetRandomInt(0, 1));
	SET_VEHICLE_WINDOW_TINT(veh, g_Random.GetRandomInt(0, 6));

	float customColorChance = 1.f;
	if (g_Random.GetRandomInt(1, 3) <= 2)
	{
		SET_VEHICLE_COLOURS(veh, g_Random.GetRandomInt(0, 160), g_Random.GetRandomInt(0, 160));

		customColorChance = .5f;
	}

	if (g_Random.GetRandomFloat(0.f, 1.f) <= customColorChance)
	{
		SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, g_Random.GetRandomInt(0, 255), g_Random.GetRandomInt(0, 255), g_Random.GetRandomInt(0, 255));
		SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, g_Random.GetRandomInt(0, 255), g_Random.GetRandomInt(0, 255), g_Random.GetRandomInt(0, 255));
	}
	else
	{
		CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh);
		CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh);
	}

	SET_VEHICLE_EXTRA_COLOURS(veh, g_Random.GetRandomInt(0, 160), g_Random.GetRandomInt(0, 160));

	for (int i = 0; i < 25; i++)
	{
		if (DOES_EXTRA_EXIST(veh, i))
		{
			SET_VEHICLE_EXTRA(veh, i, g_Random.GetRandomInt(0, 1));
		}
	}

	_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, g_Random.GetRandomInt(0, 255), g_Random.GetRandomInt(0, 255), g_Random.GetRandomInt(0, 255));
	for (int i = 0; i < 4; i++)
	{
		_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, i, true);
	}

	_SET_VEHICLE_XENON_LIGHTS_COLOR(veh, g_Random.GetRandomInt(0, 12));

	SET_VEHICLE_TYRE_SMOKE_COLOR(veh, g_Random.GetRandomInt(0, 255), g_Random.GetRandomInt(0, 255), g_Random.GetRandomInt(0, 255));

	int liveryCount = GET_VEHICLE_LIVERY_COUNT(veh);
	if (liveryCount > 0)
	{
		SET_VEHICLE_LIVERY(veh, g_Random.GetRandomInt(0, liveryCount - 1));
	}

	int roofLiveryCount = _GET_VEHICLE_ROOF_LIVERY_COUNT(veh);
	if (roofLiveryCount > 0)
	{
		_SET_VEHICLE_ROOF_LIVERY(veh, g_Random.GetRandomInt(0, roofLiveryCount - 1));
	}
}

struct SeatPed
{
	Ped ped;
	int seatIndex;
};

inline Vehicle CreateRandomVehicleWithPeds(Vehicle oldHandle, std::vector<SeatPed> seatPeds, bool addToPool, Vector3 coords, float heading, bool engineRunning, Vector3 velocity, float forwardSpeed)
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

		newVehicle = CreatePoolVehicle(newVehModel, coords.x, coords.y, coords.z, heading);
	}
	else
	{
		LoadModel(newVehModel);
		newVehicle = CREATE_VEHICLE(newVehModel, coords.x, coords.y, coords.z, heading, true, true, true);
		SET_MODEL_AS_NO_LONGER_NEEDED(newVehModel);

		SET_ENTITY_AS_MISSION_ENTITY(newVehicle, false, true);
	}

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
	SET_VEHICLE_FORWARD_SPEED(newVehicle, forwardSpeed);

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

	float heading = GET_ENTITY_HEADING(veh);
	Vector3 vehCoords = GET_ENTITY_COORDS(veh, 0);
	bool engineRunning = GET_IS_VEHICLE_ENGINE_RUNNING(veh);
	Vector3 velocity = GET_ENTITY_VELOCITY(veh);
	float forwardSpeed = GET_ENTITY_SPEED(veh);

	return CreateRandomVehicleWithPeds(veh, vehPeds, addToPool, vehCoords, heading, engineRunning, velocity, forwardSpeed);
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
		float heading = GET_ENTITY_HEADING(player);
		Vector3 velocity = GET_ENTITY_VELOCITY(player);
		float forwardSpeed = GET_ENTITY_SPEED(player);

		return CreateRandomVehicleWithPeds(0, peds, false, coords, heading, false, velocity, forwardSpeed);
	}
}