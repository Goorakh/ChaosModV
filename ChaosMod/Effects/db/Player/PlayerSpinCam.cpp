/*
    Effect by ProfessorBiddle, based on code from DrUnderscore, Idea from Synfetic
*/

#include <stdafx.h>

float camRot = 0.f;
const float camRotRate = 1.2f;

static void OnStart()
{
    SharedScriptCam::RegisterUse();
}

static void OnTick()
{
    camRot += camRotRate;
    SharedScriptCam::OverrideRotY(camRot);
}

static void OnStop()
{
    SharedScriptCam::ResetRotYOverride();
    SharedScriptCam::UnregisterUse();
}

static RegisterEffect registerEffect(EFFECT_PLAYER_SPIN_CAMERA, OnStart, OnStop, OnTick, EffectInfo
    {
        .Name = "Spinning Camera",
        .Id = "player_spin_camera",
        .IsTimed = true,
        .IsShortDuration = true,
        .IncompatibleWith = { EFFECT_FLIP_CAMERA, EFFECT_PLAYER_GTA_2 }
    }
);