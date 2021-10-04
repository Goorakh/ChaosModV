/*
Effect by Last0xygen
*/

#include <stdafx.h>

struct OrbitPed
{
    OrbitPed(Ped _ped)
    {
        ped = _ped;

        Vector3 min, max;
        GET_MODEL_DIMENSIONS(GET_ENTITY_MODEL(ped), &min, &max);
        height = max.z - min.z;

        angle = 0.f;
    }

    Ped ped;
    float angle;
    float height;
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

                OrbitPed orbPed = OrbitPed(ped);
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

                if (DOES_ENTITY_EXIST(orbitPed.ped))
                {
                    SET_ENTITY_ALPHA(orbitPed.ped, 0, true);
                    SET_PED_AS_NO_LONGER_NEEDED(&orbitPed.ped);
                    DELETE_PED(&orbitPed.ped);
                }

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
    float radius = 3.f;
    if (IS_PED_IN_ANY_VEHICLE(player, false))
    {
        entityToCircle = GET_VEHICLE_PED_IS_IN(player, false);

        Vector3 min, max;
        GET_MODEL_DIMENSIONS(GET_ENTITY_MODEL(entityToCircle), &min, &max);
        Vector3 vehModelSize = max - min;
        vehModelSize.z = 0.f;

        radius = max(radius, vehModelSize.Length() + 0.3f);
    }

    float heading = GET_ENTITY_HEADING(entityToCircle);
    for (OrbitPed& pedInfo : orbitingPeds)
    {
        if (DOES_ENTITY_EXIST(pedInfo.ped))
        {
            if (IS_PED_DEAD_OR_DYING(pedInfo.ped, false))
            {
                SET_ENTITY_HEALTH(pedInfo.ped, 0, 0);
                SET_ENTITY_ALPHA(pedInfo.ped, 0, true);
                SET_PED_AS_NO_LONGER_NEEDED(&pedInfo.ped);
                DELETE_PED(&pedInfo.ped);

                if (--count == 0)
                {
                    WAIT(0);
                    count = 5;
                }
            }
            else
            {
                Vector3 coord = GetCoordAround(entityToCircle, heading - pedInfo.angle, radius, -(pedInfo.height / 2.f), true);
                SET_ENTITY_COORDS(pedInfo.ped, coord.x, coord.y, coord.z, false, false, false, false);
                SET_ENTITY_HEADING(pedInfo.ped, pedInfo.angle + 90); // Always face away from player
                TASK_STAND_STILL(pedInfo.ped, 5000);
                pedInfo.angle += 1;
            }
        }
    }
}

static void OnStop()
{
    int count = 5;
    for (OrbitPed& pedInfo : orbitingPeds)
    {
        if (DOES_ENTITY_EXIST(pedInfo.ped))
        {
            SET_ENTITY_HEALTH(pedInfo.ped, 0, 0);
            SET_ENTITY_ALPHA(pedInfo.ped, 0, true);
            SET_PED_AS_NO_LONGER_NEEDED(&pedInfo.ped);
            DELETE_PED(&pedInfo.ped);
            if (--count == 0)
            {
                WAIT(0);
                count = 5;
            }
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
