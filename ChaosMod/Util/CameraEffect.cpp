#include <stdafx.h>
#include "CameraEffect.h"

#define CAM_EASE_TIME 1.f
#define CAM_EASE_TIME_MS CAM_EASE_TIME * 1000

#define CAM_EASE_SPEED 10.f

static Cam modCam;

static float camFOVTargetOverride = -1;

static int numCamUsers = 0;
static void RegisterModCamUsage()
{
    numCamUsers++;
    ModCamUsersUpdated();
}
static void UnregisterModCamUsage()
{
    numCamUsers--;
    ModCamUsersUpdated();
}

static void ModCamUsersUpdated()
{
    if (numCamUsers > 0)
    {
        if (!DOES_CAM_EXIST(modCam))
        {
            modCam = CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", 1);
        }

        SET_CAM_ACTIVE(modCam, true);
        RENDER_SCRIPT_CAMS(true, true, CAM_EASE_TIME_MS, 1, 1, 1);
    }
    else if (DOES_CAM_EXIST(modCam))
    {
        RENDER_SCRIPT_CAMS(false, true, 1000, true, true, true);
        SET_CAM_ACTIVE(modCam, false);
        DESTROY_CAM(modCam, true);
        modCam = 0;

        // Reset variables
        camFOVTargetOverride = -1;
    }
}

static void UpdateFOV()
{
    float currentFOV = GET_CAM_FOV(modCam);
    float targetFOV = camFOVTargetOverride != -1 ? camFOVTargetOverride : GET_GAMEPLAY_CAM_FOV();

    if (currentFOV > targetFOV)
    {
        SET_CAM_FOV(modCam, max(targetFOV, currentFOV - (CAM_EASE_SPEED * GET_FRAME_TIME())));
    }
    else if (currentFOV < targetFOV)
    {
        SET_CAM_FOV(modCam, min(targetFOV, currentFOV + (CAM_EASE_SPEED * GET_FRAME_TIME())));
    }
}

static void UpdateCoords()
{
    Vector3 currentCoords = GET_CAM_COORD(modCam);
    Vector3 targetCoords = GET_GAMEPLAY_CAM_COORD();

    if (currentCoords.DistanceTo(targetCoords) == 0.f)
    {
        return;
    }

    SET_CAM_COORD(modCam, )
}

static void UpdateModCam()
{
    if (!DOES_CAM_EXIST(modCam))
    {
        return;
    }

    UpdateFOV();
    UpdateCoords();
}

static void SetModCamFOV(float fov)
{
    camFOVTargetOverride = fov;
}
static void ResetModCamFOV()
{
    if (!DOES_CAM_EXIST(modCam))
    {
        return;
    }

    camFOVTargetOverride = GET_GAMEPLAY_CAM_FOV();
}