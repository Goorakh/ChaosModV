/*
	Effect by DrUnderscore (James), modified by Last0xygen
*/

#include <stdafx.h>
// TODO: SHVDN has a memory pattern for the gameplay camera, so it might be wise at some point
// to use it to directly modify the rotation of the camera, but that's for a later date :^)

static void OnStart()
{
    SharedScriptCam::RegisterUse();
}

static void OnTick()
{
    SharedScriptCam::OverrideRotY(180.f);
}

static void OnStop()
{
    SharedScriptCam::ResetRotYOverride();
    SharedScriptCam::UnregisterUse();
}

static RegisterEffect registerEffect(EFFECT_FLIP_CAMERA, OnStart, OnStop, OnTick, EffectInfo
	{
		.Name = "Turn Turtle",
		.Id = "player_flip_camera",
		.IsTimed = true,
		.IsShortDuration = true,
		.IncompatibleWith = { EFFECT_PLAYER_QUAKE_FOV, EFFECT_PLAYER_GTA_2, EFFECT_PLAYER_BINOCULARS, EFFECT_PLAYER_ZOOMZOOM_CAM }
	}
);