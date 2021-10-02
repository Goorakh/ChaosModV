#include <stdafx.h>
#include <mmsystem.h>
#include "AudioVolumeController.h"

namespace AudioVolumeController
{
    bool hasOriginalVolume = false;
    DWORD originalVolume;

    bool hasOverrideVolume = false;
    DWORD overrideVolume;

    void SetOverrideVolume(DWORD volume)
    {
        if (!hasOriginalVolume)
        {
            if (waveOutGetVolume(NULL, &originalVolume) == MMSYSERR_NOERROR)
            {
                hasOriginalVolume = true;
            }
        }

        if (hasOriginalVolume)
        {
            overrideVolume = volume;

            if (waveOutSetVolume(NULL, overrideVolume) == MMSYSERR_NOERROR)
            {
                hasOverrideVolume = true;
            }
        }
    }

    bool HasActiveOverrideVolume()
    {
        return hasOverrideVolume;
    }

    void ResetOverrideVolume()
    {
        if (hasOverrideVolume && hasOriginalVolume)
        {
            waveOutSetVolume(NULL, originalVolume);
            
            hasOverrideVolume = false;
            hasOriginalVolume = false;
        }
    }
}