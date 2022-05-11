/*
	Effect by Gorakh
*/

#include <stdafx.h>

struct DeadlineVehicle
{
	Vehicle veh;
	int ptfxHandle;
};

static std::map<Vehicle, DeadlineVehicle> deadlineVehs = {};

static void OnTick()
{
	USE_PARTICLE_FX_ASSET("core");

	for (Vehicle veh : GetAllVehs())
	{
		if (deadlineVehs.find(veh) == deadlineVehs.end())
		{
			int ptfxHandle = START_PARTICLE_FX_LOOPED_ON_ENTITY_BONE("veh_light_red_trail", veh, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, GET_ENTITY_BONE_INDEX_BY_NAME(veh, "chassis"), 1.f, true, true, true);
			SET_PARTICLE_FX_LOOPED_EVOLUTION(ptfxHandle, "speed", 1.f, false);
			SET_PARTICLE_FX_LOOPED_COLOUR(ptfxHandle, 1.f, 0.f, 0.f, false);
			SET_PARTICLE_FX_LOOPED_ALPHA(ptfxHandle, 1.f);

			deadlineVehs[veh] = DeadlineVehicle(veh, ptfxHandle);
		}
	}
}

static void OnStop()
{
	for (auto& pair : deadlineVehs)
	{
		DeadlineVehicle deadlineVeh = pair.second;
		if (DOES_PARTICLE_FX_LOOPED_EXIST(deadlineVeh.ptfxHandle))
		{
			REMOVE_PARTICLE_FX(deadlineVeh.ptfxHandle, 0);
		}
	}

	deadlineVehs.clear();
}

static RegisterEffect registerEffect(EFFECT_VEHS_DEADLINE, nullptr, OnStop, OnTick, EffectInfo
	{
		.Name = "Deadline",
		.Id = "vehs_deadline",
		.IsTimed = true
	}
);