/*
    Effect by Last0xygen
*/

#include <stdafx.h>

static void OnStart()
{
    RegisterModCamUsage();
}

static void OnTick()
{
    SetModCamFOV(10.f);
}

static void OnStop()
{
    ResetModCamFOV();
    UnregisterModCamUsage();
}

static RegisterEffect registerEffect(EFFECT_PLAYER_BINOCULARS, OnStart, OnStop, OnTick, EffectInfo
    {
        .Name = "Binoculars",
        .Id = "player_binoculars",
        .IsTimed = true,
        .IsShortDuration = true,
        .IncompatibleWith = { EFFECT_FLIP_CAMERA, EFFECT_PLAYER_GTA_2, EFFECT_PLAYER_QUAKE_FOV, EFFECT_PLAYER_ZOOMZOOM_CAM }
    }
);