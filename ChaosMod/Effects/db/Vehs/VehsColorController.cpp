#include <stdafx.h>

static void OnTickRed()
{
	for (Vehicle veh : GetAllVehs())
	{
		TOGGLE_VEHICLE_MOD(veh, 20, true); // Enable custom tyre smoke
		SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 255, 0, 0);

		SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 255, 0, 0);
		SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, 255, 0, 0);
		SET_VEHICLE_ENVEFF_SCALE(veh, 0.f);
		SET_VEHICLE_DIRT_LEVEL(veh, 0.f);
		REMOVE_DECALS_FROM_VEHICLE(veh);
	}
}

static RegisterEffect registerEffect1(EFFECT_RED_VEHS, nullptr, nullptr, OnTickRed, EffectInfo
	{
		.Name = "Red Traffic",
		.Id = "vehs_red",
		.IsTimed = true,
		.IncompatibleWith = { EFFECT_BLUE_VEHS, EFFECT_GREEN_VEHS, EFFECT_CHROME_VEHS, EFFECT_PINK_VEHS, EFFECT_RAINBOW_VEHS, EFFECT_VEHS_INVISIBLE },
		.EEffectGroupType = EEffectGroupType::TrafficColor
	}
);
static void OnTickBlue()
{
	for (Vehicle veh : GetAllVehs())
	{
		TOGGLE_VEHICLE_MOD(veh, 20, true); // Enable custom tyre smoke
		SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 0, 0, 255);

		SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 0, 0, 255);
		SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, 0, 0, 255);
		SET_VEHICLE_ENVEFF_SCALE(veh, 0.f);
		SET_VEHICLE_DIRT_LEVEL(veh, 0.f);
		REMOVE_DECALS_FROM_VEHICLE(veh);
	}
}

static RegisterEffect registerEffect2(EFFECT_BLUE_VEHS, nullptr, nullptr, OnTickBlue, EffectInfo
	{
		.Name = "Blue Traffic",
		.Id = "vehs_blue",
		.IsTimed = true,
		.IncompatibleWith = { EFFECT_RED_VEHS, EFFECT_GREEN_VEHS, EFFECT_CHROME_VEHS, EFFECT_PINK_VEHS, EFFECT_RAINBOW_VEHS, EFFECT_VEHS_INVISIBLE },
		.EEffectGroupType = EEffectGroupType::TrafficColor
	}
);
static void OnTickGreen()
{
	for (Vehicle veh : GetAllVehs())
	{
		TOGGLE_VEHICLE_MOD(veh, 20, true); // Enable custom tyre smoke
		SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 0, 255, 0);

		SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 0, 255, 0);
		SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, 0, 255, 0);
		SET_VEHICLE_ENVEFF_SCALE(veh, 0.f);
		SET_VEHICLE_DIRT_LEVEL(veh, 0.f);
		REMOVE_DECALS_FROM_VEHICLE(veh);
	}
}

static RegisterEffect registerEffect3(EFFECT_GREEN_VEHS, nullptr, nullptr, OnTickGreen, EffectInfo
	{
		.Name = "Green Traffic",
		.Id = "vehs_green",
		.IsTimed = true,
		.IncompatibleWith = { EFFECT_RED_VEHS, EFFECT_BLUE_VEHS, EFFECT_CHROME_VEHS, EFFECT_PINK_VEHS, EFFECT_RAINBOW_VEHS, EFFECT_VEHS_INVISIBLE },
		.EEffectGroupType = EEffectGroupType::TrafficColor
	}
);
static void OnTickChrome()
{
	for (Vehicle veh : GetAllVehs())
	{
		TOGGLE_VEHICLE_MOD(veh, 20, true); // Enable custom tyre smoke
		SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 219, 226, 233);

		// If the vehicle has a custom color, the effect won't work
		CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh);
		CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh);

		SET_VEHICLE_COLOURS(veh, 120, 120);
		SET_VEHICLE_ENVEFF_SCALE(veh, 0.f);
		SET_VEHICLE_DIRT_LEVEL(veh, 0.f);
		REMOVE_DECALS_FROM_VEHICLE(veh);
	}
}

static RegisterEffect registerEffect4(EFFECT_CHROME_VEHS, nullptr, nullptr, OnTickChrome, EffectInfo
	{
		.Name = "Chrome Traffic",
		.Id = "vehs_chrome",
		.IsTimed = true,
		.IncompatibleWith = { EFFECT_RED_VEHS, EFFECT_BLUE_VEHS, EFFECT_GREEN_VEHS, EFFECT_PINK_VEHS, EFFECT_RAINBOW_VEHS, EFFECT_VEHS_INVISIBLE },
		.EEffectGroupType = EEffectGroupType::TrafficColor
	}
);
static std::map<Vehicle, int> flameByCar;

static void OnStopPink()
{
	for (auto it = flameByCar.cbegin(); it != flameByCar.cend();)
	{
		int animHandle = it->second;
		STOP_PARTICLE_FX_LOOPED(animHandle, false);
		it++;
	}
	flameByCar.clear();
	REMOVE_NAMED_PTFX_ASSET("des_trailerpark");
}

static void OnTickPink()
{
	REQUEST_NAMED_PTFX_ASSET("des_trailerpark");
	while (!HAS_NAMED_PTFX_ASSET_LOADED("des_trailerpark"))
	{
		WAIT(0);
	}
	for (auto it = flameByCar.cbegin(); it != flameByCar.cend();)
	{
		Vehicle veh = it->first;
		if (!DOES_ENTITY_EXIST(veh))
		{
			STOP_PARTICLE_FX_LOOPED(it->second, false);
			flameByCar.erase(it++);
		}
		else
		{
			it++;
		}
	}

	for (Vehicle veh : GetAllVehs())
	{
		if (flameByCar.find(veh) == flameByCar.end())
		{
			USE_PARTICLE_FX_ASSET("des_trailerpark");
			int boneId = GET_ENTITY_BONE_INDEX_BY_NAME(veh, "chassis");
			int handle = START_PARTICLE_FX_LOOPED_ON_ENTITY_BONE("ent_ray_trailerpark_fires", veh, 0, 0, 0, 0, 0, 0, boneId, 1 * g_MetaInfo.m_fChaosMultiplier, false, false, false);
			flameByCar[veh] = handle;
		}

		TOGGLE_VEHICLE_MOD(veh, 20, true); // Enable custom tyre smoke
		SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 255, 0, 255);

		SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 255, 0, 255);
		SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, 255, 0, 255);
		SET_VEHICLE_ENVEFF_SCALE(veh, 0.f);
		SET_VEHICLE_DIRT_LEVEL(veh, 0.f);
		REMOVE_DECALS_FROM_VEHICLE(veh);
	}
}

static RegisterEffect registerEffect5(EFFECT_PINK_VEHS, nullptr, OnStopPink, OnTickPink, EffectInfo
	{
		.Name = "Hot Traffic",
		.Id = "vehs_pink",
		.IsTimed = true,
		.IncompatibleWith = { EFFECT_RED_VEHS, EFFECT_BLUE_VEHS, EFFECT_GREEN_VEHS, EFFECT_CHROME_VEHS, EFFECT_RAINBOW_VEHS, EFFECT_VEHS_INVISIBLE },
		.EEffectGroupType = EEffectGroupType::TrafficColor
	}
);
static void OnStopRainbow()
{
	for (int i = 0; i < 13; i++)
	{
		Memory::OverrideVehicleHeadlightColor(i, false, 0, 0, 0);
	}
}

static void OnTickRainbow()
{
	static int headlightColor = 0;

	static ULONG cnt = 0;
	static const float freq = .1f;

	if (++cnt >= (ULONG)-1)
	{
		cnt = 0;
	}

	for (Vehicle veh : GetAllVehs())
	{
		int r = std::sin(veh + freq * cnt * g_MetaInfo.m_fChaosMultiplier) * 127 + 128;
		int g = std::sin(veh + freq * cnt * g_MetaInfo.m_fChaosMultiplier + 2) * 127 + 128;
		int b = std::sin(veh + freq * cnt * g_MetaInfo.m_fChaosMultiplier + 4) * 127 + 128;

		SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, r, g, b);
		SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, g, b, r);

		// Neon lights

		_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, r, g, b);
		for (int i = 0; i < 4; i++)
		{
			_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, i, true);
		}

		// Headlights too

		TOGGLE_VEHICLE_MOD(veh, 22, true);
		_SET_VEHICLE_XENON_LIGHTS_COLOR(veh, headlightColor);

		TOGGLE_VEHICLE_MOD(veh, 20, true); // Enable custom tyre smoke
		SET_VEHICLE_TYRE_SMOKE_COLOR(veh, r, g, b);

		SET_VEHICLE_ENVEFF_SCALE(veh, 0.f);
		SET_VEHICLE_DIRT_LEVEL(veh, 0.f);
		REMOVE_DECALS_FROM_VEHICLE(veh);
	}

	// Headlight color switcher

	int r = std::sin(freq * cnt * g_MetaInfo.m_fChaosMultiplier) * 127 + 128;
	int g = std::sin(freq * cnt * g_MetaInfo.m_fChaosMultiplier + 2) * 127 + 128;
	int b = std::sin(freq * cnt * g_MetaInfo.m_fChaosMultiplier + 4) * 127 + 128;

	for (int i = 0; i < 13; i++)
	{
		Memory::OverrideVehicleHeadlightColor(i, true, r, g, b);
	}
}

static RegisterEffect registerEffect6(EFFECT_RAINBOW_VEHS, nullptr, OnStopRainbow, OnTickRainbow, EffectInfo
	{
		.Name = "Rainbow Traffic",
		.Id = "vehs_rainbow",
		.IsTimed = true,
		.IncompatibleWith = { EFFECT_RED_VEHS, EFFECT_BLUE_VEHS, EFFECT_GREEN_VEHS, EFFECT_CHROME_VEHS, EFFECT_PINK_VEHS, EFFECT_VEHS_INVISIBLE },
		.EEffectGroupType = EEffectGroupType::TrafficColor
	}
);
