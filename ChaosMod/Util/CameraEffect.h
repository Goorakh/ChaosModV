#pragma once

/// <summary>
/// Registers a use for the shared mod camera
/// </summary>
static void RegisterModCamUsage();
/// <summary>
/// Unregisters a use for the shared mod camera
/// </summary>
static void UnregisterModCamUsage();

static void UpdateModCam();

static void SetModCamFOV(float fov);
static void ResetModCamFOV();
