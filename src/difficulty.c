#include "global.h"
#include "data.h"
#include "event_data.h"
#include "script.h"
#include "constants/battle.h"
#include "constants/trainers.h"
#include "constants/flags.h"
#include "constants/battle_ai.h"
#include "battle.h"

// Define MIN macro if not already defined
#ifndef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

// Define trainer class constants if not already defined
#ifndef TRAINER_CLASS_AQUA_GRUNT
#define TRAINER_CLASS_AQUA_GRUNT 0x2F
#endif

#ifndef TRAINER_CLASS_MAGMA_GRUNT
#define TRAINER_CLASS_MAGMA_GRUNT 0x30
#endif

#ifndef TRAINER_CLASS_AQUA_ADMIN
#define TRAINER_CLASS_AQUA_ADMIN 0x31
#endif

#ifndef TRAINER_CLASS_MAGMA_ADMIN
#define TRAINER_CLASS_MAGMA_ADMIN 0x32
#endif

#ifndef TRAINER_CLASS_AQUA_LEADER
#define TRAINER_CLASS_AQUA_LEADER 0x33
#endif

#ifndef TRAINER_CLASS_MAGMA_LEADER
#define TRAINER_CLASS_MAGMA_LEADER 0x34
#endif

// Get the current difficulty level
enum DifficultyLevel GetCurrentDifficultyLevel(void)
{
    if (!B_VAR_DIFFICULTY)
        return DIFFICULTY_NORMAL;

    return VarGet(B_VAR_DIFFICULTY);
}

// Get the current difficulty scaling based on badges and progress
enum DifficultyScaling GetCurrentDifficultyScaling(void)
{
    // Check if nuzlocke mode is enabled for additional difficulty
    bool8 nuzlockeMode = FALSE;
    if (gSaveBlock2Ptr && gSaveBlock2Ptr->nuzlockeEnabled)
        nuzlockeMode = TRUE;
    
    // Check badges to determine current gym progress
    if (FlagGet(FLAG_BADGE08_GET))
        return nuzlockeMode ? DIFFICULTY_SCALING_CHAMPION : DIFFICULTY_SCALING_CHAMPION;
    else if (FlagGet(FLAG_BADGE07_GET))
        return nuzlockeMode ? DIFFICULTY_SCALING_ELITE_FOUR : DIFFICULTY_SCALING_ELITE_FOUR;
    else if (FlagGet(FLAG_BADGE06_GET))
        return nuzlockeMode ? DIFFICULTY_SCALING_GYM_7_8 : DIFFICULTY_SCALING_GYM_7_8;
    else if (FlagGet(FLAG_BADGE05_GET))
        return nuzlockeMode ? DIFFICULTY_SCALING_GYM_7_8 : DIFFICULTY_SCALING_GYM_7_8;
    else if (FlagGet(FLAG_BADGE04_GET))
        return nuzlockeMode ? DIFFICULTY_SCALING_GYM_5_6 : DIFFICULTY_SCALING_GYM_5_6;
    else if (FlagGet(FLAG_BADGE03_GET))
        return nuzlockeMode ? DIFFICULTY_SCALING_GYM_5_6 : DIFFICULTY_SCALING_GYM_5_6;
    else if (FlagGet(FLAG_BADGE02_GET))
        return nuzlockeMode ? DIFFICULTY_SCALING_GYM_3_4 : DIFFICULTY_SCALING_GYM_3_4;
    else if (FlagGet(FLAG_BADGE01_GET))
        return nuzlockeMode ? DIFFICULTY_SCALING_GYM_3_4 : DIFFICULTY_SCALING_GYM_3_4;
    else
        return nuzlockeMode ? DIFFICULTY_SCALING_GYM_1_2 : DIFFICULTY_SCALING_GYM_1_2;
}

// Get enhanced AI flags based on difficulty scaling
u64 GetEnhancedAIFlags(u16 trainerId, enum DifficultyScaling scaling)
{
    u64 baseFlags = GetTrainerAIFlagsFromId(trainerId);
    u64 enhancedFlags = baseFlags;
    
    // Add progressive AI enhancements based on difficulty scaling
    switch (scaling)
    {
        case DIFFICULTY_SCALING_GYM_1_2:
            // Basic trainers get minimal AI enhancement
            enhancedFlags |= AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_CHECK_VIABILITY;
            break;
            
        case DIFFICULTY_SCALING_GYM_3_4:
            // Medium difficulty: Better AI and strategic thinking
            enhancedFlags |= AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_CHECK_VIABILITY | AI_FLAG_TRY_TO_FAINT;
            enhancedFlags |= AI_FLAG_HP_AWARE | AI_FLAG_SMART_MON_CHOICES | AI_FLAG_ACE_POKEMON;
            break;
            
        case DIFFICULTY_SCALING_GYM_5_6:
            // High difficulty: Advanced AI with prediction
            enhancedFlags |= AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_CHECK_VIABILITY | AI_FLAG_TRY_TO_FAINT;
            enhancedFlags |= AI_FLAG_HP_AWARE | AI_FLAG_SMART_MON_CHOICES | AI_FLAG_SMART_SWITCHING;
            enhancedFlags |= AI_FLAG_TRY_TO_2HKO | AI_FLAG_OMNISCIENT | AI_FLAG_ACE_POKEMON;
            break;
            
        case DIFFICULTY_SCALING_GYM_7_8:
            // Very high difficulty: Expert AI with full prediction
            enhancedFlags |= AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_CHECK_VIABILITY | AI_FLAG_TRY_TO_FAINT;
            enhancedFlags |= AI_FLAG_HP_AWARE | AI_FLAG_SMART_MON_CHOICES | AI_FLAG_SMART_SWITCHING;
            enhancedFlags |= AI_FLAG_TRY_TO_2HKO | AI_FLAG_OMNISCIENT | AI_FLAG_PREDICT_SWITCH;
            enhancedFlags |= AI_FLAG_PREDICT_INCOMING_MON | AI_FLAG_PREDICT_MOVE | AI_FLAG_ACE_POKEMON;
            break;
            
        case DIFFICULTY_SCALING_ELITE_FOUR:
            // Elite Four: Master AI with all enhancements
            enhancedFlags |= AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_CHECK_VIABILITY | AI_FLAG_TRY_TO_FAINT;
            enhancedFlags |= AI_FLAG_HP_AWARE | AI_FLAG_SMART_MON_CHOICES | AI_FLAG_SMART_SWITCHING;
            enhancedFlags |= AI_FLAG_TRY_TO_2HKO | AI_FLAG_OMNISCIENT | AI_FLAG_PREDICT_SWITCH;
            enhancedFlags |= AI_FLAG_PREDICT_INCOMING_MON | AI_FLAG_PREDICT_MOVE | AI_FLAG_ACE_POKEMON;
            enhancedFlags |= AI_FLAG_PREFER_HIGHEST_DAMAGE_MOVE | AI_FLAG_WEIGH_ABILITY_PREDICTION;
            break;
            
        case DIFFICULTY_SCALING_CHAMPION:
            // Champion: Ultimate AI with all enhancements and special flags
            enhancedFlags |= AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_CHECK_VIABILITY | AI_FLAG_TRY_TO_FAINT;
            enhancedFlags |= AI_FLAG_HP_AWARE | AI_FLAG_SMART_MON_CHOICES | AI_FLAG_SMART_SWITCHING;
            enhancedFlags |= AI_FLAG_TRY_TO_2HKO | AI_FLAG_OMNISCIENT | AI_FLAG_PREDICT_SWITCH;
            enhancedFlags |= AI_FLAG_PREDICT_INCOMING_MON | AI_FLAG_PREDICT_MOVE | AI_FLAG_ACE_POKEMON;
            enhancedFlags |= AI_FLAG_PREFER_HIGHEST_DAMAGE_MOVE | AI_FLAG_WEIGH_ABILITY_PREDICTION;
            enhancedFlags |= AI_FLAG_PP_STALL_PREVENTION | AI_FLAG_RISKY;
            break;
            
        default:
            break;
    }
    
    // Nuzlocke mode adds additional challenge
    if (gSaveBlock2Ptr && gSaveBlock2Ptr->nuzlockeEnabled)
    {
        enhancedFlags |= AI_FLAG_TRY_TO_FAINT | AI_FLAG_HP_AWARE;
        enhancedFlags |= AI_FLAG_SMART_MON_CHOICES | AI_FLAG_OMNISCIENT;
    }
    
    return enhancedFlags;
}

// Check if Terastallization has already been used in the current battle
bool8 HasTerastallizationBeenUsedInBattle(void)
{
    // Check if the battle flag for Terastallization usage is set
    if (gBattleStruct && gBattleStruct->teraUsedInBattle)
        return TRUE;
    return FALSE;
}

// Mark Terastallization as used in the current battle
void MarkTerastallizationAsUsedInBattle(void)
{
    if (gBattleStruct)
        gBattleStruct->teraUsedInBattle = TRUE;
}

// Check if a trainer should use Terastallization based on difficulty scaling
bool8 ShouldTrainerUseTerastallization(u16 trainerId, enum DifficultyScaling scaling)
{
    // Allow Terastallization from gym 1 onwards
    if (scaling < DIFFICULTY_SCALING_GYM_1_2)
        return FALSE;
    
    // Elite Four and Champion always use Terastallization
    if (scaling >= DIFFICULTY_SCALING_ELITE_FOUR)
        return TRUE;
    
    // Check trainer class for main story battles
    u32 trainerClass = GetTrainerClassFromId(trainerId);
    
    // Gym leaders, Elite Four, Champion, and other main story trainers can use Terastallization
    if (trainerClass == TRAINER_CLASS_LEADER || 
        trainerClass == TRAINER_CLASS_ELITE_FOUR ||
        trainerClass == TRAINER_CLASS_CHAMPION ||
        trainerClass == TRAINER_CLASS_RIVAL ||
        trainerClass == TRAINER_CLASS_AQUA_GRUNT ||
        trainerClass == TRAINER_CLASS_MAGMA_GRUNT ||
        trainerClass == TRAINER_CLASS_AQUA_ADMIN ||
        trainerClass == TRAINER_CLASS_MAGMA_ADMIN ||
        trainerClass == TRAINER_CLASS_AQUA_LEADER ||
        trainerClass == TRAINER_CLASS_MAGMA_LEADER)
    {
        // Every main story battle from gym 1 onwards can use Terastallization
        if (scaling >= DIFFICULTY_SCALING_GYM_1_2)
            return TRUE;
    }
    
    return FALSE;
}

// Check if a trainer should use Dynamax/Gigantamax based on difficulty scaling
bool8 ShouldTrainerUseDynamax(u16 trainerId, enum DifficultyScaling scaling)
{
    // Only allow Dynamax from gym 3 onwards
    if (scaling < DIFFICULTY_SCALING_GYM_3_4)
        return FALSE;
    
    // Elite Four and Champion always use Dynamax
    if (scaling >= DIFFICULTY_SCALING_ELITE_FOUR)
        return TRUE;
    
    // Gym leaders have a chance to use Dynamax based on difficulty
    u32 trainerClass = GetTrainerClassFromId(trainerId);
    if (trainerClass == TRAINER_CLASS_LEADER)
    {
        // Every gym from gym 3 onwards uses Dynamax on ace Pokémon
        if (scaling >= DIFFICULTY_SCALING_GYM_3_4)
            return TRUE; // Always use Dynamax in gyms 3+
    }
    
    return FALSE;
}

// Get enhanced trainer items based on difficulty scaling
const u16* GetEnhancedTrainerItems(u16 trainerId, enum DifficultyScaling scaling)
{
    const u16* baseItems = GetTrainerItemsFromId(trainerId);
    static u16 enhancedItems[MAX_TRAINER_ITEMS];
    
    // Copy base items
    for (int i = 0; i < MAX_TRAINER_ITEMS; i++)
        enhancedItems[i] = baseItems[i];
    
    // Add better items based on difficulty scaling
    switch (scaling)
    {
        case DIFFICULTY_SCALING_GYM_3_4:
            // Add better healing items
            if (enhancedItems[0] == ITEM_NONE)
                enhancedItems[0] = ITEM_SUPER_POTION;
            if (enhancedItems[1] == ITEM_NONE)
                enhancedItems[1] = ITEM_FULL_HEAL;
            break;
            
        case DIFFICULTY_SCALING_GYM_5_6:
            // Add even better items
            if (enhancedItems[0] == ITEM_NONE)
                enhancedItems[0] = ITEM_HYPER_POTION;
            if (enhancedItems[1] == ITEM_NONE)
                enhancedItems[1] = ITEM_FULL_RESTORE;
            if (enhancedItems[2] == ITEM_NONE)
                enhancedItems[2] = ITEM_FULL_HEAL;
            break;
            
        case DIFFICULTY_SCALING_GYM_7_8:
        case DIFFICULTY_SCALING_ELITE_FOUR:
        case DIFFICULTY_SCALING_CHAMPION:
            // Maximum items for high difficulty
            if (enhancedItems[0] == ITEM_NONE)
                enhancedItems[0] = ITEM_MAX_POTION;
            if (enhancedItems[1] == ITEM_NONE)
                enhancedItems[1] = ITEM_FULL_RESTORE;
            if (enhancedItems[2] == ITEM_NONE)
                enhancedItems[2] = ITEM_FULL_HEAL;
            if (enhancedItems[3] == ITEM_NONE)
                enhancedItems[3] = ITEM_REVIVE;
            break;
            
        default:
            break;
    }
    
    return enhancedItems;
}

// Get enhanced trainer party levels based on difficulty scaling
u8 GetEnhancedTrainerMonLevel(u8 baseLevel, enum DifficultyScaling scaling)
{
    u8 enhancedLevel = baseLevel;
    
    // Nuzlocke mode increases difficulty
    if (gSaveBlock2Ptr && gSaveBlock2Ptr->nuzlockeEnabled)
        enhancedLevel += 2;
    
    // Progressive level scaling based on difficulty
    switch (scaling)
    {
        case DIFFICULTY_SCALING_GYM_3_4:
            enhancedLevel += 1;
            break;
        case DIFFICULTY_SCALING_GYM_5_6:
            enhancedLevel += 2;
            break;
        case DIFFICULTY_SCALING_GYM_7_8:
            enhancedLevel += 3;
            break;
        case DIFFICULTY_SCALING_ELITE_FOUR:
            enhancedLevel += 4;
            break;
        case DIFFICULTY_SCALING_CHAMPION:
            enhancedLevel += 5;
            break;
        default:
            break;
    }
    
    // Cap at level 100
    if (enhancedLevel > 100)
        enhancedLevel = 100;
    
    return enhancedLevel;
}

// Get enhanced trainer mon IVs based on difficulty scaling
u32 GetEnhancedTrainerMonIVs(u32 baseIVs, enum DifficultyScaling scaling)
{
    u32 enhancedIVs = baseIVs;
    
    // Progressive IV scaling based on difficulty
    switch (scaling)
    {
        case DIFFICULTY_SCALING_GYM_3_4:
            // Increase IVs by 2-4 points
            enhancedIVs = TRAINER_PARTY_IVS(
                MIN(31, ((enhancedIVs >> 0) & 0x1F) + 2),
                MIN(31, ((enhancedIVs >> 5) & 0x1F) + 2),
                MIN(31, ((enhancedIVs >> 10) & 0x1F) + 2),
                MIN(31, ((enhancedIVs >> 15) & 0x1F) + 2),
                MIN(31, ((enhancedIVs >> 20) & 0x1F) + 2),
                MIN(31, ((enhancedIVs >> 25) & 0x1F) + 2)
            );
            break;
            
        case DIFFICULTY_SCALING_GYM_5_6:
            // Increase IVs by 4-6 points
            enhancedIVs = TRAINER_PARTY_IVS(
                MIN(31, ((enhancedIVs >> 0) & 0x1F) + 4),
                MIN(31, ((enhancedIVs >> 5) & 0x1F) + 4),
                MIN(31, ((enhancedIVs >> 10) & 0x1F) + 4),
                MIN(31, ((enhancedIVs >> 15) & 0x1F) + 4),
                MIN(31, ((enhancedIVs >> 20) & 0x1F) + 4),
                MIN(31, ((enhancedIVs >> 25) & 0x1F) + 4)
            );
            break;
            
        case DIFFICULTY_SCALING_GYM_7_8:
            // Increase IVs by 6-8 points
            enhancedIVs = TRAINER_PARTY_IVS(
                MIN(31, ((enhancedIVs >> 0) & 0x1F) + 6),
                MIN(31, ((enhancedIVs >> 5) & 0x1F) + 6),
                MIN(31, ((enhancedIVs >> 10) & 0x1F) + 6),
                MIN(31, ((enhancedIVs >> 15) & 0x1F) + 6),
                MIN(31, ((enhancedIVs >> 20) & 0x1F) + 6),
                MIN(31, ((enhancedIVs >> 25) & 0x1F) + 6)
            );
            break;
            
        case DIFFICULTY_SCALING_ELITE_FOUR:
        case DIFFICULTY_SCALING_CHAMPION:
            // Maximum IVs for ultimate challenge
            enhancedIVs = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31);
            break;
            
        default:
            break;
    }
    
    return enhancedIVs;
}

// Check if this is a major battle that should use enhanced difficulty
bool8 IsMajorBattle(u16 trainerId)
{
    u32 trainerClass = GetTrainerClassFromId(trainerId);
    
    return (trainerClass == TRAINER_CLASS_LEADER ||
            trainerClass == TRAINER_CLASS_ELITE_FOUR ||
            trainerClass == TRAINER_CLASS_CHAMPION ||
            trainerClass == TRAINER_CLASS_RIVAL ||
            trainerClass == TRAINER_CLASS_AQUA_GRUNT ||
            trainerClass == TRAINER_CLASS_MAGMA_GRUNT ||
            trainerClass == TRAINER_CLASS_AQUA_ADMIN ||
            trainerClass == TRAINER_CLASS_MAGMA_ADMIN ||
            trainerClass == TRAINER_CLASS_AQUA_LEADER ||
            trainerClass == TRAINER_CLASS_MAGMA_LEADER);
}

// Automatically enable enhanced difficulty flags for major battles
void EnableEnhancedDifficultyForBattle(u16 trainerId)
{
    if (!IsMajorBattle(trainerId))
        return;
    
    enum DifficultyScaling scaling = GetCurrentDifficultyScaling();
    
    // Enable Dynamax battle flag for gym 3+ battles
    if (scaling >= DIFFICULTY_SCALING_GYM_3_4)
    {
        if (B_FLAG_DYNAMAX_BATTLE != 0)
            FlagSet(B_FLAG_DYNAMAX_BATTLE);
    }
    
    // Enable Tera Orb charging for gym 3+ battles
    if (scaling >= DIFFICULTY_SCALING_GYM_3_4)
    {
        if (B_FLAG_TERA_ORB_CHARGED != 0)
            FlagSet(B_FLAG_TERA_ORB_CHARGED);
    }
    
    // Set up enhanced battle conditions based on difficulty scaling
    switch (scaling)
    {
        case DIFFICULTY_SCALING_ELITE_FOUR:
        case DIFFICULTY_SCALING_CHAMPION:
            // Enable maximum difficulty flags
            if (B_FLAG_NO_BAG_USE != 0)
                FlagSet(B_FLAG_NO_BAG_USE);
            break;
            
        case DIFFICULTY_SCALING_GYM_7_8:
            // Enable high difficulty flags
            if (B_FLAG_NO_BAG_USE != 0)
                FlagSet(B_FLAG_NO_BAG_USE);
            break;
            
        default:
            break;
    }
}

// Set the current difficulty level
void SetCurrentDifficultyLevel(enum DifficultyLevel desiredDifficulty)
{
    if (!B_VAR_DIFFICULTY)
        return;

    if (desiredDifficulty > DIFFICULTY_MAX)
        desiredDifficulty = DIFFICULTY_MAX;

    VarSet(B_VAR_DIFFICULTY, desiredDifficulty);
}

// Get battle partner difficulty level
enum DifficultyLevel GetBattlePartnerDifficultyLevel(u16 partnerId)
{
    enum DifficultyLevel difficulty = GetCurrentDifficultyLevel();

    if (partnerId > TRAINER_PARTNER(PARTNER_NONE))
        partnerId -= TRAINER_PARTNER(PARTNER_NONE);

    if (difficulty == DIFFICULTY_NORMAL)
        return DIFFICULTY_NORMAL;

    if (gBattlePartners[difficulty][partnerId].party == NULL)
        return DIFFICULTY_NORMAL;

    return difficulty;
}

// Get trainer difficulty level with enhanced scaling
enum DifficultyLevel GetTrainerDifficultyLevel(u16 trainerId)
{
    enum DifficultyLevel difficulty = GetCurrentDifficultyLevel();

    if (difficulty == DIFFICULTY_NORMAL)
        return DIFFICULTY_NORMAL;

    if (gTrainers[difficulty][trainerId].party == NULL)
        return DIFFICULTY_NORMAL;

    return difficulty;
}

// Script command to increase difficulty
void Script_IncreaseDifficulty(void)
{
    enum DifficultyLevel currentDifficulty;

    if (!B_VAR_DIFFICULTY)
        return;

    currentDifficulty = GetCurrentDifficultyLevel();

    if (currentDifficulty++ > DIFFICULTY_MAX)
        return;

    Script_RequestEffects(SCREFF_V1);
    Script_RequestWriteVar(B_VAR_DIFFICULTY);

    SetCurrentDifficultyLevel(currentDifficulty);
}

// Script command to decrease difficulty
void Script_DecreaseDifficulty(void)
{
    enum DifficultyLevel currentDifficulty;

    if (!B_VAR_DIFFICULTY)
        return;

    currentDifficulty = GetCurrentDifficultyLevel();

    if (!currentDifficulty)
        return;

    Script_RequestEffects(SCREFF_V1);
    Script_RequestWriteVar(B_VAR_DIFFICULTY);

    SetCurrentDifficultyLevel(--currentDifficulty);
}

// Script command to get current difficulty
void Script_GetDifficulty(void)
{
    Script_RequestEffects(SCREFF_V1);
    gSpecialVar_Result = GetCurrentDifficultyLevel();
}

// Script command to set difficulty
void Script_SetDifficulty(void *ctx)
{
    // Cast to proper type for script reading
    struct ScriptContext *scriptCtx = (struct ScriptContext *)ctx;
    enum DifficultyLevel desiredDifficulty = ScriptReadByte(scriptCtx);

    Script_RequestEffects(SCREFF_V1);
    Script_RequestWriteVar(B_VAR_DIFFICULTY);

    SetCurrentDifficultyLevel(desiredDifficulty);
}
