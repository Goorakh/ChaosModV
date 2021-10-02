#pragma once

namespace AudioVolumeController
{
    void SetOverrideVolume(DWORD volume);
    bool HasActiveOverrideVolume();
    void ResetOverrideVolume();
}