#include <stdafx.h>
#include "SharedScriptCam.h"

namespace SharedScriptCam
{
    // NOTE(Gorakh): This didn't end up working, I managed to find the FOV offset of the gameplay camera, but it seems it is set in a game loop somewhere right before rendering, so changing it doesn't affect anything, might be able to suppress that part of the game loop though, for now I'll keep this here in case a fix for that gets figured out.
    /*
    class CamData
    {
    public:
        //char padding0[0x10];
        //
        //char padding1[0x40]; // Camera matrix
        //
        //char padding2[0x4];
        //
        //float fNearDOF;
        //float fFarDOF;
        //
        //char padding3[0x14];
        //
        //float fFOV;
        //
        //float fNearClip;
        //float fFarClip;
        //
        //char padding4[0x64];
    };
    CamData* GetGameplayCamPtr()
    {
        // Memory pattern taken from: https://github.com/crosire/scripthookvdotnet/blob/main/source/core/NativeMemory.cs#L296

        static CamData** gameplayCamAddr = nullptr;

        if (!gameplayCamAddr)
        {
            Handle handle = Memory::FindPattern("48 8B C7 F3 0F 10 0D");
            if (!handle.IsValid())
            {
                return nullptr;
            }

            handle = handle.At(-0x1D);
            handle = handle.At(handle.Value<int>()).At(4);
            gameplayCamAddr = handle.At(handle.At(3).Value<int>()).At(7).Get<CamData*>();
        }

        return *gameplayCamAddr;
    }
    */

    Cam sharedScriptCam;
    int numUsers = 0;
    float overrideRotY = NAN;

    Cam GetTargetCam()
    {
        Cam renderingCam = GET_RENDERING_CAM();
        if (DOES_CAM_EXIST(renderingCam))
        {
            // If there is another script cam, the mod script cam is no longer needed
            if (DOES_CAM_EXIST(sharedScriptCam))
            {
                DESTROY_CAM(sharedScriptCam, true);
            }

            return renderingCam;
        }

        if (!DOES_CAM_EXIST(sharedScriptCam))
        {
            sharedScriptCam = CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", 0);
            SET_CAM_ACTIVE(sharedScriptCam, true);
            RENDER_SCRIPT_CAMS(true, true, 1000, 1, 1, 1);
        }
        else if (!IS_CAM_ACTIVE(sharedScriptCam) || !IS_CAM_RENDERING(sharedScriptCam))
        {
            SET_CAM_ACTIVE(sharedScriptCam, true);
            RENDER_SCRIPT_CAMS(true, true, 1000, 1, 1, 1);
        }

        return sharedScriptCam;
    }

    void RegisterUse()
    {
        numUsers++;
    }
    void UnregisterUse()
    {
        numUsers--;

        if (numUsers == 0)
        {
            if (DOES_CAM_EXIST(sharedScriptCam))
            {
                SET_CAM_ACTIVE(sharedScriptCam, false);

                if (!DOES_CAM_EXIST(GET_RENDERING_CAM()))
                {
                    RENDER_SCRIPT_CAMS(false, true, 1000, 1, 1, 1);
                }

                DESTROY_CAM(sharedScriptCam, true);
            }
        }
    }

    void UpdateCam()
    {
        if (DOES_CAM_EXIST(sharedScriptCam))
        {
            Vector3 camCoords = GET_GAMEPLAY_CAM_COORD();
            SET_CAM_COORD(sharedScriptCam, camCoords.x, camCoords.y, camCoords.z);

            Vector3 camRot = GET_GAMEPLAY_CAM_ROT(2);
            SET_CAM_ROT(sharedScriptCam, camRot.x, camRot.y, camRot.z, 2);
        }

        if (overrideRotY != NAN)
        {
            Cam targetCam = GetTargetCam();

            Vector3 camRot = GET_CAM_ROT(targetCam, 2);
            SET_CAM_ROT(targetCam, camRot.x, overrideRotY, camRot.z, 2);
        }
    }

    void SetFOV(float fov)
    {
        SET_CAM_FOV(GetTargetCam(), fov);
    }
    void ResetFOV()
    {
        SET_CAM_FOV(GetTargetCam(), GET_GAMEPLAY_CAM_FOV());
    }

    void OverrideRotY(float y)
    {
        overrideRotY = y;
    }
    void ResetRotYOverride()
    {
        overrideRotY = NAN;
    }
}