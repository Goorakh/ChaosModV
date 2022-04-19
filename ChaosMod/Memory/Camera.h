#pragma once

#include "Memory.h"
#include "Handle.h"
#include "../Util/Natives.h"
#include "../Util/Logging.h"

static struct CameraStruct
{
    char pad0[0x1F0];
    float matrix[16];
};

namespace Memory
{
    static CameraStruct* GetGameplayCamPtr()
    {
        static CameraStruct* gameplayCamPtr = nullptr;
        if (!gameplayCamPtr)
        {
            Handle handle = Memory::FindPattern("48 8B C7 F3 0F 10 0D");
            if (!handle.IsValid())
            {
                return nullptr;
            }

            handle = handle.At(-0x1D);
            handle = handle.At(handle.Value<DWORD>()).At(4);
            handle = handle.At(handle.At(3).Value<DWORD>()).At(7);
            if (!handle.IsValid())
            {
                return nullptr;
            }

            gameplayCamPtr = handle.Get<CameraStruct>();

            LOG("Found gameplay cam ptr " << gameplayCamPtr);
        }

        return gameplayCamPtr;
    }

    static void SetOverrideCamFOV(float fov, bool overrideFOV)
    {

    }
}