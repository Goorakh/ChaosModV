/*
    Effect by Gorakh, using modified code from "Witness Protection"
*/

#include <stdafx.h>

static const char* availableWeapons[] =
{
    "WEAPON_ADVANCEDRIFLE",
    "WEAPON_APPISTOL",
    "WEAPON_ASSAULTRIFLE",
    "WEAPON_ASSAULTSHOTGUN",
    "WEAPON_ASSAULTSMG",
    "WEAPON_AUTOSHOTGUN",
    "WEAPON_BULLPUPRIFLE",
    "WEAPON_BULLPUPSHOTGUN",
    "WEAPON_CARBINERIFLE",
    "WEAPON_COMBATMG",
    "WEAPON_COMBATPDW",
    "WEAPON_COMBATPISTOL",
    "WEAPON_COMPACTLAUNCHER",
    "WEAPON_COMPACTRIFLE",
    "WEAPON_DBSHOTGUN",
    "WEAPON_DOUBLEACTION",
    "WEAPON_FIREWORK",
    "WEAPON_FLAREGUN",
    "WEAPON_GRENADELAUNCHER",
    "WEAPON_GUSENBERG",
    "WEAPON_HEAVYPISTOL",
    "WEAPON_HEAVYSHOTGUN",
    "WEAPON_HEAVYSNIPER",
    "WEAPON_HOMINGLAUNCHER",
    "WEAPON_MACHINEPISTOL",
    "WEAPON_MARKSMANPISTOL",
    "WEAPON_MARKSMANRIFLE",
    "WEAPON_MG",
    "WEAPON_MICROSMG",
    "WEAPON_MINIGUN",
    "WEAPON_MINISMG",
    "WEAPON_MUSKET",
    "WEAPON_PISTOL",
    "WEAPON_PISTOL50",
    "WEAPON_PUMPSHOTGUN",
    "WEAPON_RAILGUN",
    "WEAPON_REVOLVER",
    "WEAPON_RPG",
    "WEAPON_SAWNOFFSHOTGUN",
    "WEAPON_SMG",
    "WEAPON_SNIPERRIFLE",
    "WEAPON_SNSPISTOL",
    "WEAPON_SPECIALCARBINE",
    "WEAPON_STUNGUN",
    "WEAPON_VINTAGEPISTOL",
    "WEAPON_RAYPISTOL",
    "WEAPON_RAYCARBINE",
    "WEAPON_RAYMINIGUN"
};

struct GunPed
{
    Ped ped;
    float angle;
};
static std::vector<GunPed> gunPeds;
static int gunCount = 20;
static Hash gunModelHash;

// Time to wait until firing the next gun
static float timeBetweenShots;
static float nextShotTimer;
static int nextShootingPedIndex;

static int debugWeaponIndex = 0;
static void OnStart()
{
    //gunModelHash = GET_HASH_KEY(availableWeapons[g_Random.GetRandomInt(0, sizeof(availableWeapons) / sizeof(*availableWeapons) - 1)]);
    gunModelHash = GET_HASH_KEY(availableWeapons[debugWeaponIndex++]);

    timeBetweenShots = (_GET_WEAPON_TIME_BETWEEN_SHOTS(gunModelHash) / gunCount) * 2.f;
    nextShotTimer = timeBetweenShots;
    nextShootingPedIndex = 0;
}

static void OnTick()
{
    Ped player = PLAYER_PED_ID();
    int count = 5;
    if (gunPeds.empty())
    {
        static Hash pedHash = GET_HASH_KEY("G_M_Y_Lost_03");
        LoadModel(pedHash);
        for (int i = 0; i < gunCount; i++)
        {
            Ped ped = CREATE_PED(-1, pedHash, 0, 0, 0, 0, true, false);

            SET_ENTITY_COLLISION(ped, false, false);
            SET_ENTITY_COMPLETELY_DISABLE_COLLISION(ped, false, false);
            SET_PED_CAN_BE_TARGETTED_BY_PLAYER(ped, player, false);

            GIVE_WEAPON_TO_PED(ped, gunModelHash, 9999, false, true);
            SET_CURRENT_PED_WEAPON(ped, gunModelHash, true);
            SET_PED_INFINITE_AMMO(ped, true, gunModelHash);

            SET_PED_DROPS_WEAPONS_WHEN_DEAD(ped, false);

            float offset = (360.f / gunCount) * i;
            GunPed gunPed = { ped, offset };
            gunPeds.push_back(gunPed);
            if (--count == 0)
            {
                WAIT(0);
                count = 5;
            }
        }
    }
    Entity entityToCircle = player;
    if (IS_PED_IN_ANY_VEHICLE(player, false))
    {
        entityToCircle = GET_VEHICLE_PED_IS_IN(player, false);
    }

    float heading = GET_ENTITY_HEADING(entityToCircle);

    Vector3 min;
    Vector3 max;
    GET_MODEL_DIMENSIONS(GET_ENTITY_MODEL(entityToCircle), &min, &max);

    float height = max.z - min.z;
    float zCorrection = -(height / 2);
    float radius = max(3, sqrt((max.x - min.x) * (max.x - min.x) + (max.y - min.y) * (max.y - min.y)) * 1.2f);

    for (std::vector<GunPed>::iterator it = gunPeds.begin(); it != gunPeds.end(); )
    {
        GunPed gunPed = *it;
        SET_ENTITY_INVINCIBLE(gunPed.ped, true);
        SET_ENTITY_ALPHA(gunPed.ped, 0, false);

        Vector3 coord = GetCoordAround(entityToCircle, heading - gunPed.angle, radius, zCorrection, true);
        SET_ENTITY_COORDS(gunPed.ped, coord.x, coord.y, coord.z, false, false, false, false);
        SET_ENTITY_HEADING(gunPed.ped, gunPed.angle + 90); // Always face away from player

        //SET_PED_CONFIG_FLAG(gunPed.ped, 78, true);
        if (!GET_PED_CONFIG_FLAG(gunPed.ped, 78, 1))
        {
            SET_PED_CONFIG_FLAG(gunPed.ped, 78, true);
            //Vector3 aimCoords = GetCoordAround(entityToCircle, heading - gunPed.angle, radius + 1.f, zCorrection, true);
            //TASK_AIM_GUN_AT_COORD(gunPed.ped, aimCoords.x, aimCoords.y, aimCoords.z, 10000, 0, 0);
        }

        SET_PED_SEEING_RANGE(gunPed.ped, 0.f);
        SET_PED_HEARING_RANGE(gunPed.ped, 0.f);

        //TASK_SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(gunPed.ped, true);
        it->angle += 0.4f;
        it++;
    }

    if ((nextShotTimer -= GET_FRAME_TIME()) <= 0)
    {
        nextShotTimer = timeBetweenShots;

        GunPed gunPed = gunPeds[nextShootingPedIndex];
        Vector3 shootCoords = GetCoordAround(entityToCircle, heading - gunPed.angle, radius + 1.f, zCorrection, true);
        //SHOOT_SINGLE_BULLET_BETWEEN_COORDS
        TASK_SHOOT_AT_COORD(gunPed.ped, shootCoords.x, shootCoords.y, shootCoords.z, 500, GET_HASH_KEY("FIRING_PATTERN_SINGLE_SHOT"));

        if (++nextShootingPedIndex >= gunPeds.size())
        {
            nextShootingPedIndex = 0;
        }
    }
}

static void OnStop()
{
    int count = 5;
    for (std::vector<GunPed>::iterator it = gunPeds.begin(); it != gunPeds.end();)
    {
        GunPed gunInfo = *it;
        SET_ENTITY_INVINCIBLE(gunInfo.ped, false);
        SET_ENTITY_HEALTH(gunInfo.ped, 0, 0);
        SET_PED_AS_NO_LONGER_NEEDED(&gunInfo.ped);
        DELETE_PED(&gunInfo.ped);
        it = gunPeds.erase(it);
        if (--count == 0)
        {
            WAIT(0);
            count = 5;
        }
    }

    gunPeds.clear();
}

static RegisterEffect registerEffect(EFFECT_MISC_BULLET_RING, OnStart, OnStop, OnTick, EffectInfo
    {
        .Name = "Gunbender",
        .Id = "misc_bullet_ring",
        .IsTimed = true
    }
);
