/*
    Effect by Last0xygen
*/

#include <stdafx.h>

static void OnStart()
{
    SharedScriptCam::RegisterUse();
}

static void OnTick()
{
    SharedScriptCam::SetFOV(120.f);
}

static void OnStop()
{
    SharedScriptCam::ResetFOV();
    SharedScriptCam::UnregisterUse();
}

static RegisterEffect registerEffect(EFFECT_PLAYER_QUAKE_FOV, OnStart, OnStop, OnTick, EffectInfo
	{
		.Name = "Quake FOV",
		.Id = "player_quake_fov",
		.IsTimed = true,
		.IncompatibleWith = { EFFECT_PLAYER_GTA_2, EFFECT_PLAYER_BINOCULARS, EFFECT_PLAYER_ZOOMZOOM_CAM }
	}
);