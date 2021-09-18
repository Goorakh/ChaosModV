#include <stdafx.h>

#include "Memory/Hooks/AudioPitchHook.h"

static void OnStop()
{
	Hooks::ResetAudioPitch();
}

static void OnTick()
{
	Hooks::SetAudioPitch(g_Random.GetRandomInt(-900, 2000) * g_MetaInfo.m_fChaosMultiplier);
}

static RegisterEffect registerEffect(EFFECT_WEIRD_PITCH, nullptr, OnStop, OnTick, EffectInfo
	{
		.Name = "Weird Pitch",
		.Id = "misc_weirdpitch",
		.IsTimed = true,
		.IncompatibleWith = { EFFECT_GAMESPEED_X02, EFFECT_GAMESPEED_X05, EFFECT_LOW_PITCH, EFFECT_MISC_SIN_PITCH, EFFECT_HIGH_PITCH, EFFECT_PEDS_MINIONS }
	}
);