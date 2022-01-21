/*
	Effect by Gorakh
*/

#include <stdafx.h>

static constexpr int FIRE_DURATION = 700;

static std::map<Entity, int> entityHealthValues = {};
static std::map<FireId, int> timeToStopFires = {};

static bool isEntityFireProof(Entity entity)
{
	BOOL fireProof, _;

	return _GET_ENTITY_PROOFS(entity, &_, &fireProof, &_, &_, &_, &_, &_, &_) && fireProof;
}

static bool isEntityInvincible(Entity entity)
{
	auto addr = getScriptHandleBaseAddress(entity);

	if (addr)
	{
		DWORD flag = *(DWORD*)(addr + 0x188);
		return ((flag & (1 << 8)) != 0) || ((flag & (1 << 9)) != 0);
	}

	return false;
}

static void updateEntity(Entity entity)
{
	if (!IS_ENTITY_DEAD(entity, 0) && !isEntityInvincible(entity) && !isEntityFireProof(entity) && !IS_ENTITY_ON_FIRE(entity))
	{
		int health = GET_ENTITY_HEALTH(entity);
		if (entityHealthValues.contains(entity) && health < entityHealthValues[entity])
		{
			FireId fire = START_ENTITY_FIRE(entity);
			timeToStopFires[fire] = GET_GAME_TIMER() + FIRE_DURATION;
		}

		entityHealthValues[entity] = health;
	}
}

static void OnTick()
{
	for (Ped ped : GetAllPeds())
	{
		updateEntity(ped);
	}

	for (Vehicle veh : GetAllVehs())
	{
		updateEntity(veh);
	}

	for (Object prop : GetAllProps())
	{
		updateEntity(prop);
	}

	Vector3 impactCoords;
	for (Ped ped : GetAllPeds())
	{
		if (GET_PED_LAST_WEAPON_IMPACT_COORD(ped, &impactCoords))
		{
			START_SCRIPT_FIRE(impactCoords.x, impactCoords.y, impactCoords.z, 3, false);
		}
	}

	for (auto it = timeToStopFires.begin(); it != timeToStopFires.end(); )
	{
		FireId fire = it->first;
		int timeToStopFire = it->second;

		if (!fire || timeToStopFire <= GET_GAME_TIMER())
		{
			if (fire)
			{
				REMOVE_SCRIPT_FIRE(fire);
			}

			it = timeToStopFires.erase(it);
		}
		else
		{
			it++;
		}
	}
}

static void OnStop()
{
	entityHealthValues.clear();
	timeToStopFires.clear();
}

static RegisterEffect registerEffect(EFFECT_PEDS_FLAMING_COMBAT, nullptr, OnStop, OnTick, EffectInfo
	{
		.Name = "Firefighting",
		.Id = "peds_flaming_combat",
		.IsTimed = true
	}
);