#include "global.h"
#include "random.h"
#include "constants/items.h"
#include "constants/hold_effects.h"

// List of item IDs that should be excluded from random item selection
static const u16 sInvalidRandomItems[] = {
    ITEM_NONE,
    ITEM_MASTER_BALL,
    ITEM_PREMIER_BALL,
    ITEM_SAFARI_BALL,
    // ITEM_GS_BALL, (Removed - not defined in this version)
    // ITEM_PARK_BALL, (Removed - not defined in this version)
    // ITEM_RED_APRICORN, (Removed - not defined in this version)
    // ITEM_BLUE_APRICORN, (Removed - not defined in this version)
    // ITEM_YELLOW_APRICORN, (Removed - not defined in this version)
    // ITEM_GREEN_APRICORN, (Removed - not defined in this version)
    // ITEM_PINK_APRICORN, (Removed - not defined in this version)
    // ITEM_WHITE_APRICORN, (Removed - not defined in this version)
    // ITEM_BLACK_APRICORN, (Removed - not defined in this version)
    ITEM_WAILMER_PAIL,
    ITEM_DEVON_GOODS,
    ITEM_SOOT_SACK,
    ITEM_BASEMENT_KEY,
    ITEM_ACRO_BIKE,
    ITEM_POKEBLOCK_CASE,
    ITEM_LETTER,
    ITEM_EON_TICKET,
    ITEM_RED_ORB,
    ITEM_BLUE_ORB,
    ITEM_SCANNER,
    ITEM_GO_GOGGLES,
    ITEM_METEORITE,
    // ITEM_ROOM_1_KEY, (Removed - not defined in this version)
    // ITEM_ROOM_2_KEY, (Removed - not defined in this version)
    // ITEM_ROOM_4_KEY, (Removed - not defined in this version)
    // ITEM_ROOM_6_KEY, (Removed - not defined in this version)
    ITEM_STORAGE_KEY,
    ITEM_ROOT_FOSSIL,
    ITEM_CLAW_FOSSIL,
    ITEM_DEVON_SCOPE,
    ITEM_MACH_BIKE,
    ITEM_CONTEST_PASS,
    // ITEM_OAKS_PARCEL, (Removed - not defined in this version)
    // ITEM_SECRET_KEY, (Removed - not defined in this version)
    // ITEM_BIKE_VOUCHER, (Removed - not defined in this version)
    // ITEM_GOLD_TEETH, (Removed - not defined in this version)
    // ITEM_OLD_AMBER, (Removed - not defined in this version)
    // ITEM_CARD_KEY, (Removed - not defined in this version)
    // ITEM_LIFT_KEY, (Removed - not defined in this version)
    // ITEM_HELIX_FOSSIL, (Removed - not defined in this version)
    // ITEM_DOME_FOSSIL, (Removed - not defined in this version)
    // ITEM_SILPH_SCOPE, (Removed - not defined in this version)
    ITEM_BICYCLE,
    ITEM_TOWN_MAP,
    // ITEM_VS_SEEKER, (Removed - not defined in this version)
    // ITEM_FAME_CHECKER, (Removed - not defined in this version)
    ITEM_TM_CASE,
    ITEM_BERRY_POUCH,
    // ITEM_TEACHY_TV, (Removed - not defined in this version)
    // ITEM_TRI_PASS, (Removed - not defined in this version)
    // ITEM_RAINBOW_PASS, (Removed - not defined in this version)
    // ITEM_TEA, (Removed - not defined in this version)
    // ITEM_MYSTIC_TICKET, (Removed - not defined in this version)
    // ITEM_AURORA_TICKET, (Removed - not defined in this version)
    // ITEM_POWDER_JAR, (Removed - not defined in this version)
    ITEM_RUBY,
    ITEM_SAPPHIRE,
    ITEM_MAGMA_EMBLEM,
    ITEM_OLD_SEA_MAP,
    ITEM_INFINITE_CANDY
};

// Function to check if an item is valid for random selection
static bool8 IsValidRandomItem(u16 itemId)
{
    u32 i;
    
    if (itemId == ITEM_NONE || itemId >= ITEMS_COUNT)
        return FALSE;
    
    // Check against the invalid items list
    for (i = 0; i < ARRAY_COUNT(sInvalidRandomItems); i++)
    {
        if (itemId == sInvalidRandomItems[i])
            return FALSE;
    }
    
    return TRUE;
}

// Get a random valid item for hidden item spots
u16 GetRandomValidItem(u16 originalItem)
{
    u16 randomItem;
    u32 attempts = 0;
    
    // Use a seeded RNG for consistent results
    // The seed is based on the encryption key and the original item
    u32 seed = gSaveBlock2Ptr->encryptionKey + originalItem;
    SeedRng(seed);
    
    do {
        randomItem = (Random() % (ITEMS_COUNT - 1)) + 1; // Random item from 1 to ITEMS_COUNT-1
        attempts++;
        
        // Avoid infinite loops
        if (attempts > 100)
        {
            // If we can't find a valid item after 100 attempts, just return the original
            return originalItem;
        }
    } while (!IsValidRandomItem(randomItem));
    
    return randomItem;
}
