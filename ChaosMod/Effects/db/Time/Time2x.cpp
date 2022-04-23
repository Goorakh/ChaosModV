/*
	Effect by Gorakh
*/

#include <stdafx.h>

#include "Memory/Timescale.h"
#include "Memory/Hooks/AudioPitchHook.h"

static void OnTick()
{
	Memory::SetTimescaleLimitsDisabled(true);
	SET_TIME_SCALE(2.f);
	//Memory::SetTimeScale(2.f);
	Hooks::SetAudioPitch(2000);
}

static void OnStop()
{
	SET_TIME_SCALE(1.f);
	Hooks::ResetAudioPitch();
	Memory::SetTimescaleLimitsDisabled(false);
}

static RegisterEffect registerEffect(EFFECT_TIME_GAMESPEED_2X, nullptr, OnStop, OnTick, EffectInfo
	{
		.Name = "2x Gamespeed",
		.Id = "time_2x_gamespeed",
		.IsTimed = true,
		.IsShortDuration = true
	}
);