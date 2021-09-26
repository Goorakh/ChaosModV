/*
Effect by Last0xygen
*/

#include <stdafx.h>

struct OrbitPed
{
    Ped ped;
    float angle;
};
static std::vector<OrbitPed> orbitingPeds;
static int pedCount = 20;

static void OnStart()
{
    Ped player = PLAYER_PED_ID();
    Vector3 pos = GET_ENTITY_COORDS(player, false);
}

static void OnTick()
{
    Ped player = PLAYER_PED_ID();
    int count = 5;
    // Update bodyguards if amount is wrong
    if (orbitingPeds.size() != pedCount * g_MetaInfo.m_fChaosMultiplier)
    {
        int pedsDiff = (pedCount * g_MetaInfo.m_fChaosMultiplier) - orbitingPeds.size();
        if (pedsDiff > 0) // Add peds
        {
            static Hash pedHash = GET_HASH_KEY("MP_M_FIBSec_01");
            LoadModel(pedHash);
            while (pedsDiff-- > 0)
            {
                Ped ped = CREATE_PED(-1, pedHash, 0, 0, 0, 0, true, false);
                SET_ENTITY_HAS_GRAVITY(ped, false);
                SET_PED_CAN_RAGDOLL(ped, false);
                SET_ENTITY_COLLISION(ped, false, true);
                SET_PED_CAN_BE_TARGETTED_BY_PLAYER(ped, player, false);
                SET_PED_SEEING_RANGE(ped, 0.f);
                SET_PED_HEARING_RANGE(ped, 0.f);
                OrbitPed orbPed = { ped, 0 /*angle will be set after, since all ped angles need to be updated anyway*/};
                orbitingPeds.push_back(orbPed);
                if (--count == 0)
                {
                    WAIT(0);
                    count = 5;
                }
            }
        }
        else if (pedsDiff < 0) // Remove peds
        {
            while (pedsDiff++ < 0)
            {
                OrbitPed orbitPed = orbitingPeds.back();

                SET_ENTITY_ALPHA(orbitPed.ped, 0, true);
                SET_PED_AS_NO_LONGER_NEEDED(&orbitPed.ped);
                DELETE_PED(&orbitPed.ped);

                orbitingPeds.pop_back();

                if (--count == 0)
                {
                    WAIT(0);
                    count = 5;
                }
            }
        }

        // Update ped angles, since number of peds has changed
        for (int i = 0; i < orbitingPeds.size(); i++)
        {
            float offset = (360 / (pedCount * g_MetaInfo.m_fChaosMultiplier)) * i;
            orbitingPeds[i].angle = offset;
        }
    }
    Entity entityToCircle = player;
    if (IS_PED_IN_ANY_VEHICLE(player, false))
    {
        entityToCircle = GET_VEHICLE_PED_IS_IN(player, false);
    }
    float heading = GET_ENTITY_HEADING(entityToCircle);

    for (std::vector<OrbitPed>::iterator it = orbitingPeds.begin(); it != orbitingPeds.end(); )
    {
        OrbitPed pedInfo = *it;
        if (IS_PED_DEAD_OR_DYING(pedInfo.ped, false))
        {
            SET_ENTITY_HEALTH(pedInfo.ped, 0, 0);
            SET_ENTITY_ALPHA(pedInfo.ped, 0, true);
            SET_PED_AS_NO_LONGER_NEEDED(&pedInfo.ped);
            DELETE_PED(&pedInfo.ped);
            it = orbitingPeds.erase(it);
            if (--count == 0)
            {
                WAIT(0);
                count = 5;
            }
        }
        else
        {
            Vector3 min;
            Vector3 max;
            GET_MODEL_DIMENSIONS(GET_ENTITY_MODEL(pedInfo.ped), &min, &max);
            float height = max.z - min.z;

            Vector3 coord = GetCoordAround(entityToCircle, heading - pedInfo.angle, 3, -(height / 2.f), true);
            SET_ENTITY_COORDS(pedInfo.ped, coord.x, coord.y, coord.z , false, false, false, false);
            SET_ENTITY_HEADING(pedInfo.ped, pedInfo.angle + 90); // Always face away from player
            TASK_STAND_STILL(pedInfo.ped, 5000);
            it->angle += 1;
            it++;
        }
    }
}

static void OnStop()
{
    int count = 5;
    for (std::vector<OrbitPed>::iterator it = orbitingPeds.begin(); it != orbitingPeds.end();)
    {
        OrbitPed pedInfo = *it;
        SET_ENTITY_HEALTH(pedInfo.ped, 0, 0);
        SET_ENTITY_ALPHA(pedInfo.ped, 0, true);
        SET_PED_AS_NO_LONGER_NEEDED(&pedInfo.ped);
        DELETE_PED(&pedInfo.ped);
        it = orbitingPeds.erase(it);
        if (--count == 0)
        {
            WAIT(0);
            count = 5;
        }
    }
    orbitingPeds.clear();
}

static RegisterEffect registerEffect(EFFECT_MISC_WITNESS_PROTECTION, OnStart, OnStop, OnTick, EffectInfo
    {
        .Name = "Witness Protection",
        .Id = "misc_witness_protection",
		.IsTimed = true
    }
);
