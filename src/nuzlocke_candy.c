#include "global.h"
#include "pokemon.h"
#include "item.h"
#include "caps.h"
#include "constants/items.h"

// Function to check if a Pokémon can use a Rare Candy in Nuzlocke mode
bool8 CanUseRareCandyInNuzlocke(struct Pokemon *mon)
{
    // If Nuzlocke mode isn't enabled, allow normal Rare Candy usage
    if (!gSaveBlock2Ptr->nuzlockeEnabled)
        return TRUE;
    
    // Check if the Pokémon has fainted - if so, don't allow Rare Candy use
    if (GetMonData(mon, MON_DATA_HP, NULL) == 0)
        return FALSE;
    
    // Check if using the Rare Candy would exceed the current level cap
    u8 currentLevel = GetMonData(mon, MON_DATA_LEVEL, NULL);
    u32 levelCap = GetCurrentLevelCap();
    
    // Don't allow Rare Candy use if it would exceed the level cap
    if (currentLevel >= levelCap)
        return FALSE;
    
    return TRUE;
}

// Function to check if a Pokémon can be revived in Nuzlocke mode
bool8 CanReviveInNuzlocke(struct Pokemon *mon)
{
    // If Nuzlocke mode isn't enabled, allow normal revival
    if (!gSaveBlock2Ptr->nuzlockeEnabled)
        return TRUE;
    
    // In Nuzlocke mode, don't allow reviving fainted Pokémon
    if (GetMonData(mon, MON_DATA_HP, NULL) == 0)
        return FALSE;
    
    return TRUE;
}
