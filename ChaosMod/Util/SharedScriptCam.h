#pragma once

namespace SharedScriptCam
{
    // Registers a use of the shared script cam, if there is no camera active, a new one is created
    void RegisterUse();

    // Unregisters a use of the shared script cam, if there are no more registered users, the script camera is removed
    void UnregisterUse();

    void SetFOV(float fov);
    void ResetFOV();

    void OverrideRotY(float y);
    void ResetRotYOverride();
}