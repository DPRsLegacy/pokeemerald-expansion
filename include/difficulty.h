#ifndef GUARD_DIFFICULTY_H
#define GUARD_DIFFICULTY_H

#include "global.h"

// Progressive difficulty scaling for gym battles and major battles
enum DifficultyScaling
{
    DIFFICULTY_SCALING_NONE = 0,
    DIFFICULTY_SCALING_GYM_1_2,      // Gyms 1-2: Basic difficulty
    DIFFICULTY_SCALING_GYM_3_4,      // Gyms 3-4: Medium difficulty + Terastallization
    DIFFICULTY_SCALING_GYM_5_6,      // Gyms 5-6: High difficulty + Terastallization + Dynamax
    DIFFICULTY_SCALING_GYM_7_8,      // Gyms 7-8: Very high difficulty + Terastallization + Dynamax
    DIFFICULTY_SCALING_ELITE_FOUR,   // Elite Four: Maximum difficulty + Terastallization + Dynamax
    DIFFICULTY_SCALING_CHAMPION,     // Champion: Ultimate difficulty + Terastallization + Dynamax
};

enum DifficultyLevel
{
    DIFFICULTY_NORMAL = 0,
    DIFFICULTY_HARD,
    DIFFICULTY_EXPERT,
    DIFFICULTY_MASTER,
    DIFFICULTY_MAX = DIFFICULTY_MASTER
};

// Define the count constant
#define DIFFICULTY_COUNT (DIFFICULTY_MAX + 1)

// Enhanced difficulty functions
enum DifficultyScaling GetCurrentDifficultyScaling(void);
u64 GetEnhancedAIFlags(u16 trainerId, enum DifficultyScaling scaling);
bool8 ShouldTrainerUseTerastallization(u16 trainerId, enum DifficultyScaling scaling);
bool8 ShouldTrainerUseDynamax(u16 trainerId, enum DifficultyScaling scaling);
const u16* GetEnhancedTrainerItems(u16 trainerId, enum DifficultyScaling scaling);
u8 GetEnhancedTrainerMonLevel(u8 baseLevel, enum DifficultyScaling scaling);
u32 GetEnhancedTrainerMonIVs(u32 baseIVs, enum DifficultyScaling scaling);
bool8 IsMajorBattle(u16 trainerId);
void EnableEnhancedDifficultyForBattle(u16 trainerId);

// Terastallization usage tracking
bool8 HasTerastallizationBeenUsedInBattle(void);
void MarkTerastallizationAsUsedInBattle(void);

// Basic difficulty functions
enum DifficultyLevel GetCurrentDifficultyLevel(void);
void SetCurrentDifficultyLevel(enum DifficultyLevel desiredDifficulty);
enum DifficultyLevel GetBattlePartnerDifficultyLevel(u16 partnerId);
enum DifficultyLevel GetTrainerDifficultyLevel(u16 trainerId);

// Script commands
void Script_IncreaseDifficulty(void);
void Script_DecreaseDifficulty(void);
void Script_GetDifficulty(void);
void Script_SetDifficulty(void *ctx); // Remove struct ScriptContext reference

#endif // GUARD_DIFFICULTY_H
