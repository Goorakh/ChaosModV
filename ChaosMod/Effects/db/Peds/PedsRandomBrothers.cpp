#include <stdafx.h>

static std::vector<Hash> GetAvailableVehModels()
{
	static std::vector<Hash> availableVehModels;
	if (availableVehModels.empty())
	{
		static const std::vector<Hash> allVehModels = Memory::GetAllVehModels();
		for (const Hash& vehModel : allVehModels)
		{
			if (GET_VEHICLE_MODEL_NUMBER_OF_SEATS(vehModel) > 0 && !IS_THIS_MODEL_A_TRAIN(vehModel) && GET_VEHICLE_MODEL_ACCELERATION(vehModel) > 0)
			{
				availableVehModels.push_back(vehModel);
			}
		}
	}

	return availableVehModels;
}

static void OnStart()
{
	static const std::vector<Hash> vehModels = GetAvailableVehModels();
	Hash chosenModel = vehModels[g_Random.GetRandomInt(0, vehModels.size() - 1)];
	SetSurroundingPedsInVehicles(chosenModel, -1, 30.f);

	WAIT(0);

	std::string vehName = _GET_LABEL_TEXT(GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(chosenModel));
	g_pEffectDispatcher->OverrideEffectName(EFFECT_PEDS_RANDOMBROTHERS, vehName + " Brothers");
}

static RegisterEffect registerEffect(EFFECT_PEDS_RANDOMBROTHERS, OnStart, EffectInfo
	{
		.Name = "${VEHICLE} Brothers",
		.Id = "peds_randombrothers",
		.EEffectGroupType = EEffectGroupType::TrafficSpawner
	}
);