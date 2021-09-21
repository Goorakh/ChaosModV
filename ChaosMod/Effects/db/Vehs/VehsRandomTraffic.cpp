#include <stdafx.h>
//effect by ProfessorBiddle, this is a bit clunky but it works well.

static Vehicle ReplaceVehicle(Vehicle veh)
{
	Vehicle newVeh = ReplaceVehicle(veh, true);

	// Way to know if vehicle is modified
	SET_VEHICLE_WINDOW_TINT(newVeh, 3);

	Ped driver = GET_PED_IN_VEHICLE_SEAT(newVeh, -1, 0);
	if (driver && DOES_ENTITY_EXIST(driver) && !IS_PED_A_PLAYER(driver))
	{
		TASK_VEHICLE_DRIVE_WANDER(driver, newVeh, 40, 786603);
	}

	return newVeh;
}

static void OnTick()
{
	std::vector<Vehicle> replacedVehicles;

	for (auto veh : GetAllVehs())
	{
		if (DOES_ENTITY_EXIST(veh))
		{
			// Detect if vehicle already randomized
			if (GET_VEHICLE_WINDOW_TINT(veh) != 3)
			{
				replacedVehicles.push_back(ReplaceVehicle(veh));

				WAIT(10);
			}
		}
	}

	for (int i = 0; i < g_MetaInfo.m_fChaosMultiplier - 1; i++)
	{
		WAIT(3000);

		for (Vehicle veh : replacedVehicles)
		{
			if (veh && DOES_ENTITY_EXIST(veh) && GET_ENTITY_HEALTH(veh) > 0)
			{
				ReplaceVehicle(veh);
			}
		}
	}
}

static RegisterEffect registerEffect(EFFECT_VEH_RANDTRAFFIC, nullptr, nullptr, OnTick, EffectInfo
	{
		.Name = "Random Traffic",
		.Id = "veh_randtraffic",
		.IsTimed = true
	}
);