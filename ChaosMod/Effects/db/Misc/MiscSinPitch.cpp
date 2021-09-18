#include <stdafx.h>

#include "Memory/Hooks/AudioPitchHook.h"

static float timer;

static void OnStart()
{
	timer = 0;
}

static void OnStop()
{
	Hooks::ResetAudioPitch();
}

static void OnTick()
{
	Hooks::SetAudioPitch(SIN(timer * g_MetaInfo.m_fChaosMultiplier) * 400.f * g_MetaInfo.m_fChaosMultiplier);
	timer += GET_FRAME_TIME();
}

static RegisterEffect registerEffect(EFFECT_MISC_SIN_PITCH, OnStart, OnStop, OnTick, EffectInfo
	{
		.Name = "Wave Pitch",
		.Id = "misc_sinpitch",
		.IsTimed = true,
		.IncompatibleWith = { EFFECT_GAMESPEED_X02, EFFECT_GAMESPEED_X05, EFFECT_LOW_PITCH, EFFECT_HIGH_PITCH, EFFECT_WEIRD_PITCH, EFFECT_PEDS_MINIONS }
	}
);