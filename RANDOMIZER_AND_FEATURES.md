# Pokémon Emerald Expansion - Randomizer & Enhanced Features

This document outlines the comprehensive randomizer and enhanced battle features implemented in this Pokémon Emerald Expansion fork.

## 🎲 Randomizer Features

### Core Randomization System
- **Global Toggle**: Randomizer can be enabled/disabled during new game creation via Professor Birch's introduction
- **Save Integration**: Randomizer state is saved per playthrough for consistency
- **Seeded Randomization**: Uses encryption key + various game data for reproducible results

### 🌟 What Gets Randomized

#### **Wild Pokémon Species**
- All wild encounters (grass, water, fishing) use random valid Pokémon
- Level ranges preserved from original encounter tables
- Consistent per location using map-based seeding
- Special encounters (Feebas) also randomized

#### **Trainer Pokémon**
- **All Trainer Types**: Regular trainers, gym trainers, gym leaders, Elite Four, Champion
- **Species Randomization**: Every trainer Pokémon gets a random species
- **Moveset Randomization**: All trainer Pokémon get 4 random moves from the entire move pool
- **No Duplicate Moves**: Ensures varied movesets per Pokémon
- **Consistent Seeding**: Same trainer will have same team across playthroughs with same seed

#### **Pickup Items**
- Random items from pickup table instead of level-based distribution
- Uses player trainer ID + party slot for consistent seeding

#### **Hidden Items**
- All hidden items in the overworld are randomized when found
- Uses encryption key + original item ID for consistent seeding
- Excludes key items and important progression items

#### **Tera Types** *(When Randomizer Enabled)*
- All captured Pokémon get completely random Tera types (any of 18 types)
- Personality + species based seeding for consistency per individual
- No longer limited to natural types

## 🎮 Enhanced Battle Features

### 🔮 Terastallization System
- **Early Access**: Tera Orb obtained from May/Brendan when receiving first 5 Poké Balls
- **Automatic Charging**: Tera Orb recharges at Pokémon Centers
- **Dual Gimmick Support**: Can be used simultaneously with Dynamax
- **Lore Integration**: Explained as new phenomenon from Paldea after Terapagos discovery

### ⚡ Dynamax Restrictions
- **Strategic Limitation**: Only usable in gym battles and major story encounters
- **Allowed Battles**:
  - Gym Leaders (Roxanne, Brawly, Wattson, Flannery, Norman, Winona, Tate & Liza, Juan)
  - Elite Four (Sidney, Phoebe, Glacia, Drake)
  - Champion (Wallace/Steven)
  - Rival Battles (May/Brendan)
  - Team Leaders (Archie, Maxie)
- **Blocked Battles**:
  - Wild Pokémon encounters
  - Regular trainer battles
  - Team grunt battles

### 🎭 Nuzlocke Mode
- **Optional Challenge**: Can be enabled after randomizer during new game setup
- **Core Rules**:
  - **One Catch Per Area**: Only first encounter per map can be caught
  - **Forced Nicknames**: All caught Pokémon must be nicknamed (skips prompt)
  - **Permanent Death**: Fainted Pokémon are automatically released
- **Area Tracking**: Uses efficient bitfield system to track caught status
- **Safari Zone Support**: Special handling for Safari Zone areas

## 📁 Implementation Details

### Files Modified

#### Core Randomizer Logic
- `src/battle_main.c` - Trainer species and moveset randomization
- `src/battle_script_commands.c` - Pickup item randomization and forced nicknames
- `src/field_specials.c` - Hidden item randomization
- `src/random_items.c` - Random item selection logic
- `src/wild_encounter.c` - Wild Pokémon species randomization
- `src/pokemon.c` - Tera type randomization and Nuzlocke rules
- `src/party_menu.c` - Nuzlocke death checking

#### Battle System Enhancements
- `src/battle_terastal.c` - Dual gimmick compatibility
- `src/battle_dynamax.c` - Battle type restrictions
- `include/config/battle.h` - Tera Orb flag configuration

#### User Interface & Story
- `src/main_menu.c` - New game introduction flow
- `data/maps/LittlerootTown_ProfessorBirchsLab/scripts.inc` - May/Brendan Tera Orb dialogue
- `data/text/birch_speech.inc` - Randomizer and Nuzlocke question text
- `include/strings.h` - Text string declarations
- `include/global.h` - Save block structure extensions

### Save Data Structure
- `randomizerEnabled` flag for randomizer state
- `nuzlockeEnabled` flag for Nuzlocke mode
- `nuzlockeCaughtAreas[64]` bitfield for area tracking

## 🎯 Usage Instructions

### Enabling Features
1. **Start New Game**: Begin a new game normally
2. **Randomizer Question**: Professor Birch will ask about enabling randomizer mode
3. **Nuzlocke Question**: Follow-up question about Nuzlocke mode (if desired)
4. **Tera Orb**: May/Brendan will give you the Tera Orb with your first Poké Balls

### Battle Controls
- **Terastallization**: Press START before selecting a move in any battle
- **Dynamax**: Available only in gym/major story battles via Dynamax Band + flag
- **Dual Gimmicks**: Both can be active simultaneously for maximum impact

### Randomizer Behavior
- **Consistent**: Same seed produces same randomization across playthroughs
- **Varied**: Different encryption keys create completely different experiences
- **Balanced**: All Pokémon species have equal chance of appearing
- **Dynamic**: Hidden items are randomized when found, not at game start
- **Filtered**: Key items and progression items excluded from randomization

## 🔧 Technical Features

### Random Number Generation
- **High-Quality RNG**: Uses SFC32 (Small Fast Counting 32-bit) algorithm
- **RTC Seeding**: Properly seeded using Real-Time Clock when BUGFIX enabled
- **Deterministic**: Personality + species based seeding for consistent results

### Performance Optimizations
- **Efficient Bitfields**: Area tracking uses minimal memory
- **Seeded Generation**: Avoids expensive calculations during battle
- **Memory Management**: Proper cleanup and party compaction

### Error Handling
- **Bag Full Support**: Proper handling when inventory is full
- **Edge Cases**: Handles Safari Zone, first battles, and special encounters
- **Battle Type Detection**: Robust trainer vs wild battle identification

## 🎨 Dialogue Examples

### Randomizer Introduction
> **PROF. BIRCH**: "Now, I have a special question for you! Would you like me to enable RANDOMIZER MODE? This will make wild POKéMON and trainer teams completely unpredictable!"

### Nuzlocke Introduction  
> **PROF. BIRCH**: "Now, would you like to enable NUZLOCKE MODE? This challenging mode enforces special rules: Only one POKéMON per area, all POKéMON must be nicknamed, and fainted POKéMON must be released!"

### Tera Orb Gift (May)
> **MAY**: "Oh! And here's something really special from my dad! It's a TERA ORB! It uses a new phenomenon discovered in PALDEA! After researchers found TERAPAGOS, this power spread to HOENN too! To TERASTALLIZE, just press START before picking a move in battle! Your POKéMON will get a sparkling crystal form and change types!"

### Tera Orb Gift (Brendan)
> **BRENDAN**: "And here's a TERA ORB from my old man. It's based on new research from PALDEA. They discovered TERAPAGOS and now this power works in HOENN. In battle, hit START before choosing your move to activate it. Your POKéMON will TERASTALLIZE and change types. Use it strategically."

## 🚀 Future Possibilities

This foundation enables easy expansion for additional features:
- Custom randomizer options (abilities, movesets, types)
- Additional Nuzlocke variants (hardcore, legacy rules)
- Extended battle gimmick combinations
- Tournament/challenge modes

## 📊 Statistics & Balance

### Randomization Distribution
- **Equal Species Chances**: All valid Pokémon have equal probability
- **Type Diversity**: Random Tera types create unexpected type combinations
- **Move Variety**: 4 random moves per trainer Pokémon from full move pool

### Battle Balance
- **Strategic Dynamax**: Limited to major battles for tactical decision-making
- **Accessible Terastallization**: Available early for consistent strategic options
- **Nuzlocke Challenge**: Optional hardcore mode for experienced players

---

*This implementation preserves the core Pokémon Emerald experience while adding substantial replay value and strategic depth through randomization and enhanced battle mechanics.*
