#include <stdafx.h>

struct MeteorInfo
{
	MeteorInfo() : MeteorInfo(0)
	{
	}

	MeteorInfo(Object _meteorProp)
	{
		meteorProp = _meteorProp;
		despawnTimer = 5;
		hasDoneImpactEffects = false;
	}

	Object meteorProp;
	int despawnTimer;
	bool hasDoneImpactEffects;

	void OnImpact(Vector3 impactCoords)
	{
		#pragma region Force Nearby Entities Away
		static const float MAX_DIST = 10.f;

		int count = 10;
		for (Ped ped : GetAllPeds())
		{
			if (ped && DOES_ENTITY_EXIST(ped))
			{
				Vector3 pedCoords = GET_ENTITY_COORDS(ped, 0);
				if (impactCoords.DistanceTo(pedCoords) <= MAX_DIST)
				{
					Vector3 forceVec = pedCoords - impactCoords;
					forceVec.z += 0.5f; // Apply artificial upwards force
					forceVec = forceVec / forceVec.Length(); // Normalize vector
					forceVec = forceVec * 10.f; // Length of vector is now 10

					SET_PED_TO_RAGDOLL(ped, 1000, 1000, 0, false, false, false);
					Vector3 forceOffset = GET_OFFSET_FROM_ENTITY_GIVEN_WORLD_COORDS(ped, pedCoords.x + -forceVec.x * 0.3f, pedCoords.y + -forceVec.y * 0.3f, pedCoords.z + -forceVec.z * 0.3f);
					APPLY_FORCE_TO_ENTITY(ped, 1, forceVec.x, forceVec.y, forceVec.z, forceOffset.x, forceOffset.y, forceOffset.z, 0, false, false, true, false, false);

					if (--count == 0)
					{
						WAIT(0);
						count = 10;
					}
				}
			}
		}

		for (Vehicle veh : GetAllVehs())
		{
			if (veh && DOES_ENTITY_EXIST(veh))
			{
				Vector3 vehCoords = GET_ENTITY_COORDS(veh, 0);
				if (impactCoords.DistanceTo(vehCoords) <= MAX_DIST)
				{
					Vector3 forceVec = vehCoords - impactCoords;
					forceVec.z += 0.5f; // Apply artificial upwards force
					forceVec = forceVec / forceVec.Length(); // Normalize vector
					forceVec = forceVec * 10.f; // Length of vector is now 10

					Vector3 forceOffset = GET_OFFSET_FROM_ENTITY_GIVEN_WORLD_COORDS(veh, vehCoords.x + -forceVec.x * 0.3f, vehCoords.y + -forceVec.y * 0.3f, vehCoords.z + -forceVec.z * 0.3f);
					APPLY_FORCE_TO_ENTITY(veh, 1, forceVec.x, forceVec.y, forceVec.z, forceOffset.x, forceOffset.y, forceOffset.z, 0, false, false, true, false, false);

					if (--count == 0)
					{
						WAIT(0);
						count = 10;
					}
				}
			}
		}

		for (Object prop : GetAllProps())
		{
			if (prop && DOES_ENTITY_EXIST(prop) && prop != meteorProp)
			{
				Vector3 propCoords = GET_ENTITY_COORDS(prop, 0);
				if (impactCoords.DistanceTo(propCoords) <= MAX_DIST)
				{
					Vector3 forceVec = propCoords - impactCoords;
					forceVec.z += 0.5f; // Apply artificial upwards force
					forceVec = forceVec / forceVec.Length(); // Normalize vector
					forceVec = forceVec * 10.f; // Length of vector is now 10

					Vector3 forceOffset = GET_OFFSET_FROM_ENTITY_GIVEN_WORLD_COORDS(prop, propCoords.x + -forceVec.x * 0.3f, propCoords.y + -forceVec.y * 0.3f, propCoords.z + -forceVec.z * 0.3f);
					APPLY_FORCE_TO_ENTITY(prop, 1, forceVec.x, forceVec.y, forceVec.z, forceOffset.x, forceOffset.y, forceOffset.z, 0, false, false, true, false, false);

					if (--count == 0)
					{
						WAIT(0);
						count = 10;
					}
				}
			}
		}
		#pragma endregion

		#pragma region Play Particle FX
		static const char* ptfxAsset = "core";

		REQUEST_NAMED_PTFX_ASSET(ptfxAsset);
		while (!HAS_NAMED_PTFX_ASSET_LOADED(ptfxAsset))
		{
			WAIT(0);
		}

		USE_PARTICLE_FX_ASSET(ptfxAsset);

		START_PARTICLE_FX_NON_LOOPED_AT_COORD("bul_gravel_heli", impactCoords.x, impactCoords.y, impactCoords.z, 0.f, 0.f, 0.f, 50.f, false, false, false);

		REMOVE_NAMED_PTFX_ASSET(ptfxAsset);
		#pragma endregion

		float playerDist = impactCoords.DistanceTo(GET_ENTITY_COORDS(PLAYER_PED_ID(), 0));
		if (playerDist <= MAX_DIST)
		{
			SHAKE_GAMEPLAY_CAM("SMALL_EXPLOSION_SHAKE", (1.f - (playerDist / MAX_DIST)) * 2.f);

			REQUEST_SCRIPT_AUDIO_BANK("FBI_04_HEAT_SOUNDS", 0, 0);
			PLAY_SOUND_FROM_COORD(-1, "Tow_truck_damage", impactCoords.x, impactCoords.y, impactCoords.z, "FBI_04_HEAT_SOUNDS", 0, MAX_DIST * 2.f, 0);
		}

		hasDoneImpactEffects = true;
	}
};

static void OnTick()
{
	// Thanks to menyoo for the prop names
	static const char* propNames[] = { "prop_asteroid_01", "prop_test_boulder_01", "prop_test_boulder_02", "prop_test_boulder_03", "prop_test_boulder_04" };
	static constexpr int MAX_METEORS = 20;

	static MeteorInfo meteors[MAX_METEORS] = {};
	static int meteorsAmount = 0;

	Vector3 playerPos = GET_ENTITY_COORDS(PLAYER_PED_ID(), false);

	static DWORD64 lastTick = 0;
	DWORD64 curTick = GET_GAME_TIMER();

	if (meteorsAmount <= MAX_METEORS && curTick > lastTick + 200)
	{
		lastTick = curTick;

		Vector3 spawnPos = Vector3::Init(
			playerPos.x + g_Random.GetRandomInt(-100, 100),
			playerPos.y + g_Random.GetRandomInt(-100, 100),
			playerPos.z + g_Random.GetRandomInt(25, 50)
		);

		Hash choosenPropHash = GET_HASH_KEY(propNames[g_Random.GetRandomInt(0, sizeof(propNames) / sizeof(*propNames) - 1)]);
		Object meteor = CreatePoolProp(choosenPropHash, spawnPos.x, spawnPos.y, spawnPos.z, true);

		meteorsAmount++;

		for (int i = 0; i < MAX_METEORS; i++)
		{
			if (!meteors[i].meteorProp || !DOES_ENTITY_EXIST(meteors[i].meteorProp))
			{
				meteors[i] = MeteorInfo(meteor);
				break;
			}
		}

		SET_OBJECT_PHYSICS_PARAMS(meteor, 100000.f, 1.f, 1.f, 0.f, 0.f, .5f, 0.f, 0.f, 0.f, 0.f, 0.f);
		APPLY_FORCE_TO_ENTITY_CENTER_OF_MASS(meteor, 0, 50.f, 0, -10000.f, true, false, true, true);
	}

	static DWORD64 lastTick2 = 0;
	for (int i = 0; i < MAX_METEORS; i++)
	{
		Object& prop = meteors[i].meteorProp;
		if (prop)
		{
			if (DOES_ENTITY_EXIST(prop) && meteors[i].despawnTimer > 0)
			{
				Vector3 propPos = GET_ENTITY_COORDS(prop, false);
				if (GET_DISTANCE_BETWEEN_COORDS(playerPos.x, playerPos.y, playerPos.z, propPos.x, propPos.y, propPos.z, true) < 400.f)
				{
					if (HAS_ENTITY_COLLIDED_WITH_ANYTHING(prop))
					{
						if (!meteors[i].hasDoneImpactEffects)
						{
							float groundZ;
							if (GET_GROUND_Z_FOR_3D_COORD(propPos.x, propPos.y, propPos.z, &groundZ, 0, 0))
							{
								meteors[i].OnImpact(Vector3::Init(propPos.x, propPos.y, groundZ));
							}
						}

						if (lastTick2 < curTick - 1000)
						{
							meteors[i].despawnTimer--;
						}
					}

					continue;
				}
			}

			meteorsAmount--;

			SET_OBJECT_AS_NO_LONGER_NEEDED(&prop);

			prop = 0;
		}
	}

	if (lastTick2 < curTick - 1000)
	{
		lastTick2 = curTick;
	}
}

static RegisterEffect registerEffect(EFFECT_METEOR_RAIN, nullptr, nullptr, OnTick, EffectInfo
	{
		.Name = "Meteor Shower",
		.Id = "meteorrain",
		.IsTimed = true
	}
);