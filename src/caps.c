#include "global.h"
#include "battle.h"
#include "event_data.h"
#include "caps.h"
#include "pokemon.h"


u32 GetCurrentLevelCap(void)
{
    // Level caps for gym badges
    static const u32 sLevelCapFlagMap[][2] =
    {
        {FLAG_BADGE01_GET, 15},  // Roxanne's Stone Badge
        {FLAG_BADGE02_GET, 19},  // Brawly's Knuckle Badge
        {FLAG_BADGE03_GET, 24},  // Wattson's Dynamo Badge
        {FLAG_BADGE04_GET, 29},  // Flannery's Heat Badge
        {FLAG_BADGE05_GET, 31},  // Norman's Balance Badge
        {FLAG_BADGE06_GET, 33},  // Winona's Feather Badge
        {FLAG_BADGE07_GET, 42},  // Tate & Liza's Mind Badge
        {FLAG_BADGE08_GET, 46},  // Juan's Rain Badge
        {FLAG_IS_CHAMPION, 58},  // After becoming Champion
    };
    
    // Level caps for major story events
    static const u32 sStoryLevelCapFlagMap[][2] =
    {
        {FLAG_ADVENTURE_STARTED, 10},           // After receiving Pokédex
        {FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY, 22}, // After defeating Team Magma/Aqua at Mt. Chimney
        {FLAG_DELIVERED_DEVON_GOODS, 17},       // After delivering Devon Goods
        {FLAG_DEFEATED_MAGMA_SPACE_CENTER, 40}, // After defeating Team Magma at Space Center
        {FLAG_KYOGRE_ESCAPED_SEAFLOOR_CAVERN, 44}, // After Kyogre escapes Seafloor Cavern
        {FLAG_DEFEATED_RAYQUAZA, 55},           // After defeating Rayquaza
        {FLAG_DEFEATED_ELITE_4_DRAKE, 57},      // After defeating Drake of Elite Four
    };

    u32 i;
    u32 gymCap = MAX_LEVEL;
    u32 storyCap = MAX_LEVEL;

    if (B_LEVEL_CAP_TYPE == LEVEL_CAP_FLAG_LIST)
    {
        // Check gym badge caps
        for (i = 0; i < ARRAY_COUNT(sLevelCapFlagMap); i++)
        {
            if (!FlagGet(sLevelCapFlagMap[i][0]))
            {
                gymCap = sLevelCapFlagMap[i][1];
                break;
            }
        }
        
        // Check story event caps
        for (i = 0; i < ARRAY_COUNT(sStoryLevelCapFlagMap); i++)
        {
            if (!FlagGet(sStoryLevelCapFlagMap[i][0]))
            {
                storyCap = sStoryLevelCapFlagMap[i][1];
                break;
            }
        }
        
        // Return the lower of the two caps
        return gymCap < storyCap ? gymCap : storyCap;
    }
    else if (B_LEVEL_CAP_TYPE == LEVEL_CAP_VARIABLE)
    {
        return VarGet(B_LEVEL_CAP_VARIABLE);
    }

    return MAX_LEVEL;
}

u32 GetSoftLevelCapExpValue(u32 level, u32 expValue)
{
    static const u32 sExpScalingDown[5] = { 4, 8, 16, 32, 64 };
    static const u32 sExpScalingUp[5]   = { 16, 8, 4, 2, 1 };

    u32 levelDifference;
    u32 currentLevelCap = GetCurrentLevelCap();

    if (B_EXP_CAP_TYPE == EXP_CAP_NONE)
        return expValue;

    if (level < currentLevelCap)
    {
        if (B_LEVEL_CAP_EXP_UP)
        {
            levelDifference = currentLevelCap - level;
            if (levelDifference > ARRAY_COUNT(sExpScalingUp) - 1)
                return expValue + (expValue / sExpScalingUp[ARRAY_COUNT(sExpScalingUp) - 1]);
            else
                return expValue + (expValue / sExpScalingUp[levelDifference]);
        }
        else
        {
            return expValue;
        }
    }
    else if (B_EXP_CAP_TYPE == EXP_CAP_HARD)
    {
        return 0;
    }
    else if (B_EXP_CAP_TYPE == EXP_CAP_SOFT)
    {
        levelDifference = level - currentLevelCap;
        if (levelDifference > ARRAY_COUNT(sExpScalingDown) - 1)
            return expValue / sExpScalingDown[ARRAY_COUNT(sExpScalingDown) - 1];
        else
            return expValue / sExpScalingDown[levelDifference];
    }
    else
    {
       return expValue;
    }
}

u32 GetCurrentEVCap(void)
{
    static const u16 sEvCapFlagMap[][2] = {
        // Define EV caps for each milestone
        {FLAG_BADGE01_GET, MAX_TOTAL_EVS *  1 / 17},
        {FLAG_BADGE02_GET, MAX_TOTAL_EVS *  3 / 17},
        {FLAG_BADGE03_GET, MAX_TOTAL_EVS *  5 / 17},
        {FLAG_BADGE04_GET, MAX_TOTAL_EVS *  7 / 17},
        {FLAG_BADGE05_GET, MAX_TOTAL_EVS *  9 / 17},
        {FLAG_BADGE06_GET, MAX_TOTAL_EVS * 11 / 17},
        {FLAG_BADGE07_GET, MAX_TOTAL_EVS * 13 / 17},
        {FLAG_BADGE08_GET, MAX_TOTAL_EVS * 15 / 17},
        {FLAG_IS_CHAMPION, MAX_TOTAL_EVS},
    };

    if (B_EV_CAP_TYPE == EV_CAP_FLAG_LIST)
    {
        for (u32 evCap = 0; evCap < ARRAY_COUNT(sEvCapFlagMap); evCap++)
        {
            if (!FlagGet(sEvCapFlagMap[evCap][0]))
                return sEvCapFlagMap[evCap][1];
        }
    }
    else if (B_EV_CAP_TYPE == EV_CAP_VARIABLE)
    {
        return VarGet(B_EV_CAP_VARIABLE);
    }
    else if (B_EV_CAP_TYPE == EV_CAP_NO_GAIN)
    {
        return 0;
    }

    return MAX_TOTAL_EVS;
}
