/*
    Effect by Moxi, based on code from DrUnderscore & ProfessorBiddle, cleaned by Last0xygen.
*/

#include <stdafx.h>

static float camZoom = 80.f;
static float camZoomRate = 0.6f;

static void OnStart()
{
    SharedScriptCam::RegisterUse();
    camZoom = 80.f;
}

static void OnTick()
{
    static DWORD64 lastTick = 0;
    DWORD64 curTick = GET_GAME_TIMER();

    if (curTick > lastTick + 5)
    {
        lastTick = curTick;

        if (camZoom < 11 || camZoom > 119)
        {
            camZoomRate = camZoomRate*-1;
        }
        camZoom += camZoomRate;
    }

    SharedScriptCam::SetFOV(camZoom);
}

static void OnStop()
{
    SharedScriptCam::ResetFOV();
    SharedScriptCam::UnregisterUse();
}

static RegisterEffect registerEffect(EFFECT_PLAYER_ZOOMZOOM_CAM, OnStart, OnStop, OnTick, EffectInfo
    {
        .Name = "Zoom Zoom Cam",
        .Id = "player_zoomzoom_cam",
        .IsTimed = true,
        .IsShortDuration = true,
        .IncompatibleWith = { EFFECT_PLAYER_GTA_2, EFFECT_PLAYER_QUAKE_FOV, EFFECT_PLAYER_BINOCULARS }
    }
);