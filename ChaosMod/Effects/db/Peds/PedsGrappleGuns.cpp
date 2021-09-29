/*
	Effect by Gorakh
*/

#include <stdafx.h>

static void OnStart()
{
	for (Ped ped : GetAllPeds())
	{
		CLEAR_ENTITY_LAST_WEAPON_DAMAGE(ped);
	}
	
	for (Vehicle veh : GetAllVehs())
	{
		CLEAR_ENTITY_LAST_WEAPON_DAMAGE(veh);
	}

	for (Entity prop : GetAllProps())
	{
		CLEAR_ENTITY_LAST_WEAPON_DAMAGE(prop);
	}
}

static Entity GetLastEntityShotBy(Ped attacker)
{
	Hash weaponHash;
	GET_CURRENT_PED_WEAPON(attacker, &weaponHash, true);

	for (Ped ped : GetAllPeds())
	{
		if (ped != attacker && HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY(ped, attacker, 1) && HAS_ENTITY_BEEN_DAMAGED_BY_WEAPON(ped, weaponHash, 0))
		{
			CLEAR_ENTITY_LAST_WEAPON_DAMAGE(ped);

			if (IS_PED_IN_ANY_VEHICLE(ped, false))
			{
				Vehicle pedVehicle = GET_VEHICLE_PED_IS_IN(ped, false);
				CLEAR_ENTITY_LAST_WEAPON_DAMAGE(pedVehicle);
				return pedVehicle;
			}

			return ped;
		}
	}

	for (Vehicle veh : GetAllVehs())
	{
		if (HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY(veh, attacker, 1) && HAS_ENTITY_BEEN_DAMAGED_BY_WEAPON(veh, weaponHash, 0))
		{
			CLEAR_ENTITY_LAST_WEAPON_DAMAGE(veh);
			return veh;
		}
	}

	for (Entity prop : GetAllProps())
	{
		if (HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY(prop, attacker, 1) && HAS_ENTITY_BEEN_DAMAGED_BY_WEAPON(prop, weaponHash, 0))
		{
			SET_ENTITY_DYNAMIC(prop, true);

			CLEAR_ENTITY_LAST_WEAPON_DAMAGE(prop);
			return prop;
		}
	}

	return 0;
}

static void OnTick()
{
	Vector3 impactCoords;

	for (Ped ped : GetAllPeds())
	{
		if (DOES_ENTITY_EXIST(ped) && !IS_ENTITY_DEAD(ped, 0) && GET_PED_LAST_WEAPON_IMPACT_COORD(ped, &impactCoords))
		{
			Entity shotEntity = GetLastEntityShotBy(ped);
			if (shotEntity && DOES_ENTITY_EXIST(shotEntity))
			{
				if (IS_ENTITY_A_PED(shotEntity) && !IS_PED_A_PLAYER(shotEntity) && !IS_PED_IN_ANY_VEHICLE(shotEntity, false))
				{
					SET_PED_TO_RAGDOLL(shotEntity, 500, 500, 0, false, false, false);
				}

				Vector3 entityVelocity = GET_ENTITY_VELOCITY(shotEntity);

				Vector3 force = (GET_ENTITY_COORDS(ped, true) - impactCoords);
				force = force / force.Length(); // Normalize vector
				force = force * 25.f * g_MetaInfo.m_fChaosMultiplier;

				APPLY_FORCE_TO_ENTITY(shotEntity, 1, force.x, force.y, force.z, impactCoords.x, impactCoords.y, impactCoords.z, 0, false, false, true, true, true);
			}
		}
	}
}

static RegisterEffect registerEffect(EFFECT_PEDS_GRAPPLE_GUNS, OnStart, nullptr, OnTick, EffectInfo
	{
		.Name = "Gravity Guns",
		.Id = "peds_grapple_guns",
		.IsTimed = true
	}
);
