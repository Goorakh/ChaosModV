#include <stdafx.h>

static void OnStart()
{
	static const Hash faggioHash = GET_HASH_KEY("FAGGIO");
	SetSurroundingPedsInVehicles(faggioHash, -1, 30.f);
}

static RegisterEffect registerEffect(EFFECT_PEDS_SCOOTERBROTHERS, OnStart, EffectInfo
	{
		.Name = "Scooter Brothers",
		.Id = "peds_scooterbrothers",
		.EEffectGroupType = EEffectGroupType::TrafficSpawner
	}
);