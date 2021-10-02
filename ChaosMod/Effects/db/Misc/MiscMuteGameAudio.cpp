/*
	Effect by Gorakh
*/

#include <stdafx.h>
#include "Util/AudioVolumeController.h"

static void OnStop()
{
	AudioVolumeController::ResetOverrideVolume();
}

static void OnTick()
{
	if (!AudioVolumeController::HasActiveOverrideVolume())
	{
		AudioVolumeController::SetOverrideVolume(0);
		
		// Setting the volume every tick is not good for performance, but this should almost never be ran more than once anyway
		WAIT(5000);
	}
}

static RegisterEffect registerEffect(EFFECT_MISC_MUTE_GAME_AUDIO, nullptr, OnStop, OnTick, EffectInfo
	{
		.Name = "Deaf",
		.Id = "misc_mute_game_audio",
		.IsTimed = true,
		.IsShortDuration = true
	}
);
