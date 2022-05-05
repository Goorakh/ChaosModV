#include <stdafx.h>

#include "Memory/Hooks/AudioPitchHook.h"

static void OnStop()
{
	Hooks::ResetAudioPitch();
}

static void OnTick()
{
	Hooks::SetAudioPitch(SIN((GET_GAME_TIMER() / 7.f) * MetaModifiers::m_fChaosMultiplier) * 1000.f * MetaModifiers::m_fChaosMultiplier);
}

static RegisterEffect registerEffect(EFFECT_MISC_SIN_PITCH, nullptr, OnStop, OnTick, EffectInfo
	{
		.Name = "Wave Pitch",
		.Id = "misc_sinpitch",
		.IsTimed = true,
		.IncompatibleWith = { EFFECT_GAMESPEED_X02, EFFECT_GAMESPEED_X05, EFFECT_LOW_PITCH, EFFECT_HIGH_PITCH, EFFECT_WEIRD_PITCH, EFFECT_PEDS_MINIONS }
	}
);