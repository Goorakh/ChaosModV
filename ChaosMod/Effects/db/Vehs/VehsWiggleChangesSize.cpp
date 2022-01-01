/*
	Effect by Reguas
*/

#include <stdafx.h>

static void OnTick()
{
	static DWORD64 lastTick = GET_GAME_TIMER();
	DWORD64 curTick = GET_GAME_TIMER();
	Ped player = PLAYER_PED_ID();
	if (IS_PED_IN_ANY_VEHICLE(player, 0))
	{
		Entity vehicle = GET_VEHICLE_PED_IS_IN(player, 0);

		if (IS_THIS_MODEL_A_CAR(GET_ENTITY_MODEL(vehicle))) // unfortunately, doesn't work with bikes, and has much less effect on planes
		{
			static Vehicle savedVehicle = 0;
			static float savedHeading = 0;
			static float savedDelta = 0;
			static float multiplier = 1.f;

			if (savedVehicle != vehicle)
			{
				multiplier = 1.f;
				savedHeading = 0;
				savedDelta = 0;
			}

			float heading = GET_ENTITY_HEADING(vehicle);
			if (savedHeading == 0 || curTick - lastTick > 500)
			{
				savedHeading = heading;
				lastTick = curTick;
			}

			float delta = heading - savedHeading;
			if (delta < -180.f)
			{
				delta += 360.f;
			}
			if (delta > 180.f)
			{
				delta -= 360.f;
			}

			if (savedDelta == 0 && savedHeading != 0)
			{
				savedDelta = delta;
			}
			if (delta * savedDelta < 0 && abs(delta) >= 7.5f)
			{
				savedDelta = delta;
				savedHeading = heading;
				multiplier += 0.01f;
			}

			static float savedLength;
			float length;
			Vector3 rv, fv, uv, pv;
			GET_ENTITY_MATRIX(vehicle, &rv, &fv, &uv, &pv);
			length = fv.Length() + rv.Length() + uv.Length();

			if (savedVehicle != vehicle)
			{
				savedLength = length;
				savedVehicle = vehicle;
			}
			if (length - savedLength < 0.1f)
			{
				Memory::SetVehicleScale(vehicle, multiplier * g_MetaInfo.m_fChaosMultiplier);
			}
		}
	}
}

static RegisterEffect registerEffect(EFFECT_WIGGLE_CHANGES_SIZE, nullptr, nullptr, OnTick, EffectInfo
	{
		.Name = "Wiggle-Wiggle",
		.Id = "veh_wiggle_changes_size",
		.IsTimed = true
	}
);