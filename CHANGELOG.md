# Changelog - Randomizer & Enhanced Features

## Recent Additions (Last 2 Days)

### 🎲 Randomizer System
- **Added comprehensive randomization system**
  - Wild Pokémon species randomization
  - Trainer Pokémon species randomization  
  - Trainer moveset randomization (4 random moves per Pokémon)
  - Pickup item randomization
  - Random Tera types for captured Pokémon (when randomizer enabled)
- **Integrated into new game flow** with Professor Birch introduction
- **Seeded randomization** for consistent playthroughs

### 🎭 Nuzlocke Mode
- **Added full Nuzlocke mode support**
  - One catch per area rule
  - Forced nicknames for all catches
  - Automatic release of fainted Pokémon
  - Area tracking with bitfield system
  - Safari Zone special handling
- **Integrated into new game setup** after randomizer question

### 🔮 Terastallization Enhancements
- **Early access implementation**
  - Tera Orb given by May/Brendan with first Poké Balls
  - Automatic Tera Orb charging at Pokémon Centers
  - Lore explanation connecting to Paldea/Terapagos
- **Enhanced compatibility**
  - Can be used simultaneously with Dynamax
  - Random Tera types when randomizer is enabled

### ⚡ Dynamax Restrictions
- **Strategic battle limitations**
  - Only usable in gym battles and major story encounters
  - Blocked in wild battles and regular trainer fights
  - Maintains special feeling for important battles

### 📝 User Experience Improvements
- **Enhanced dialogue system**
  - New Professor Birch introduction questions
  - Character-appropriate Tera Orb explanations
  - Clear instructions for battle mechanics
- **Save system integration**
  - Persistent randomizer and Nuzlocke flags
  - Proper area tracking storage

## Technical Implementation

### Files Added/Modified
- Core battle system files (13 files)
- User interface and dialogue files (6 files)  
- Save data structure extensions
- Configuration flag updates

### Key Technical Features
- High-quality SFC32 RNG implementation
- Efficient bitfield area tracking
- Robust error handling and edge cases
- Memory-efficient randomization algorithms

### Quality Assurance
- All changes compile successfully
- No linting errors introduced
- Backwards compatibility maintained
- Proper testing of major features

---

*All features are production-ready and enhance the core Pokémon Emerald experience while maintaining game balance and stability.*