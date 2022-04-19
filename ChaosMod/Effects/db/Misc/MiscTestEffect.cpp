/*
	Effect by <Your Name>
*/

#include <stdafx.h>
#include "Memory/Camera.h"

static void OnStart()
{
	Memory::GetGameplayCamPtr();
}

static void OnStop()
{

}

static void OnTick()
{

}

// Any of these functions can be omitted and either replaced with a `nullptr` or completely left out (default parameter values) in the `RegisterEffect` declaration
static RegisterEffect registerEffect(EFFECT_MISC_TEST, OnStart, OnStop, OnTick, EffectInfo
	{
		// These are always required, you may have to add more designators depending on your effect
		.Name = "!Test",
		.Id = "player_funny_stuff"
	}
);