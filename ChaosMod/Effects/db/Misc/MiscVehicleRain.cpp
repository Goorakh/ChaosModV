#include <stdafx.h>

//Effect by ProfessorBiddle

static void OnTick()
{
	Vector3 playerPos = GET_ENTITY_COORDS(PLAYER_PED_ID(), false);

	static DWORD64 lastTick = 0;
	DWORD64 curTick = GET_GAME_TIMER();

	if (curTick > lastTick + (500 / MetaModifiers::m_fChaosMultiplier))
	{
		lastTick = curTick;

		Vector3 spawnPos;
		spawnPos.x = playerPos.x + g_Random.GetRandomInt(-100, 100);
		spawnPos.y = playerPos.y + g_Random.GetRandomInt(-100, 100);
		spawnPos.z = playerPos.z + g_Random.GetRandomInt(25, 50);


		static std::vector<Hash> vehModels = Memory::GetAllVehModels();

		if (!vehModels.empty())
		{
			Vehicle veh = CreateTempVehicle(vehModels[g_Random.GetRandomInt(0, vehModels.size() - 1)], spawnPos.x, spawnPos.y, spawnPos.z, GET_ENTITY_HEADING(PLAYER_PED_ID()));
			SetVehicleRandomUpgrades(veh);
		}
	}
}

static RegisterEffect registerEffect(EFFECT_MISC_VEHICLE_RAIN, nullptr, nullptr, OnTick, EffectInfo
	{
		.Name = "Vehicle Rain",
		.Id = "misc_vehicle_rain",
		.IsTimed = true,
		.IsShortDuration = true
	}
);