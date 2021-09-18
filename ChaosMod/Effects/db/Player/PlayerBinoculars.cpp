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
    SharedScriptCam::SetFOV(10.f);
}

static void OnStop()
{
    SharedScriptCam::ResetFOV();
    SharedScriptCam::UnregisterUse();
}

static RegisterEffect registerEffect(EFFECT_PLAYER_BINOCULARS, OnStart, OnStop, OnTick, EffectInfo
    {
        .Name = "Binoculars",
        .Id = "player_binoculars",
        .IsTimed = true,
        .IsShortDuration = true,
        .IncompatibleWith = { EFFECT_PLAYER_GTA_2, EFFECT_PLAYER_QUAKE_FOV, EFFECT_PLAYER_ZOOMZOOM_CAM }
    }
);