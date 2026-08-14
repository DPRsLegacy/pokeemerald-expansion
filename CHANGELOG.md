# 🎮 Pokémon Emerald Expansion - Changelog

> **Enhanced Randomizer & Difficulty System**  
> *Transform your Pokémon Emerald experience with new features and challenges*

---

## 🚀 **What's New (Latest Update)**

### 🪦 **MegaGraveSite on Route 103**
- **New map west of Route 103** – Stepping onto the unmarked tiles at the west side of Route 103 teleports you to MegaGraveSite (Smitty Werben Man Jensen’s grave). The same tiles on the east side of the grave site send you back. No cave-door graphics; the ground stays matching.
- **Mega Ring from the grave** – Read the gravestone to receive the **Mega Ring** (once). That is the key item that lets your Pokémon Mega Evolve in battle if they hold the matching Mega Stone.
- **Hidden Big Pearl** – A hidden Big Pearl sits next to the grave.

### 🎛️ **Story Trainers Use Mega Evolution**
- **Gym Leaders, Elite Four, Champion, rivals, and Team Aqua/Magma admins and leaders Mega Evolve** when they have a Pokémon that can.
- **One Mega per battle** – Prefers the ace if it can Mega Evolve; otherwise uses the last Mega-capable Pokémon on the team.
- **Matching Mega Stone is given automatically** – The chosen Pokémon holds the correct Mega Stone (for example Manectricite, Absolite, Salamencite). Rayquaza-style Megas that need a move still work without replacing the held item.
- **Does not stack with Tera/Dynamax on the same Pokémon** – The Mega Pokémon is not also flagged to Terastallize or Dynamax.

### 🎛️ **Mauville Pokémon Center Mega Stone Dealer**
- **Mega Stone shop in Mauville Pokémon Center** – A new NPC in Mauville City Pokémon Center 1F sells every Mega Stone: original Mega Evolutions, Legends Z-A Megas, and Mega Dimension DLC Megas (including Mega X/Y and Mega Z stones).
- **¥1800 each** – All Mega Stones use a custom mart price of **¥1800**. The clerk does not mention the price in dialogue; it appears in the shop menu.
- **Locked until Wattson is defeated** – The shop only opens after you earn the Dynamo Badge (`FLAG_BADGE03_GET`). Before then, the dealer says they only sell to trainers who have defeated Gym Leader Wattson.

### 🎛️ **Follow Pokémon on Game Mode Menu**
- **Follow Pokémon toggle** – New optional setting on the intro **Game Mode** screen. When ON, your first conscious party Pokémon follows you in the overworld (HGSS-style).
- **Independent toggle** – Works like Randomizer, Nuzlocke, Soul Link, and Random Evolution; not tied to Nuzlocke mode.
- **Default OFF** – Follow Pokémon is disabled unless you turn it ON before **Start Game**. Old saves default to OFF.
- **Follower system enabled** – Compile-time follower support (`OW_FOLLOWERS_ENABLED`) is now ON; spawn is gated at runtime by your Game Mode choice.

### 🔄 **Rebased onto Latest RHH Master (July 2026)**
- **Upstream sync** – Custom features are now built on top of the latest [rh-hideout/pokeemerald-expansion](https://github.com/rh-hideout/pokeemerald-expansion) `master` (includes Gen VII/VIII animation updates, official difficulty system, and 1100+ upstream commits since the original fork).
- **Single squashed commit** – All romhack changes (randomizer, nuzlocke, soul link, random evolution, scaled difficulty, custom items, Petalburg vendor) are consolidated into one commit on upstream for easier future rebases.
- **Item IDs updated** – `ITEM_SOUL_LINK_BALL` and `ITEM_INFINITE_CANDY` are assigned after upstream’s latest item table entries (IDs 874–875). Old saves from pre-rebase builds are **not compatible**.
- **Integration fixes** – Soul Link Ball uses upstream `constants/pokeball.h` + `gPokeBalls[]`; capture rate handled in `ComputeBallData`; eevee mom trades use upstream `InGameTradeID` enum; custom mart script opcode coexists with upstream `getbraillestringwidth`.

### 🎛️ **Latest Update: Petalburg Mart Evolution Seller & Custom Mart Prices**
- **Evolution stone/item seller in Petalburg Poké Mart** – A scientist NPC in the Petalburg Mart sells evolution stones and evolution items. All items are **¥250** each. Includes: Fire, Water, Thunder, Leaf, Ice, Sun, Moon, Shiny, Dusk, Dawn Stone; Oval Stone, Everstone; Dragon Scale, Upgrade, Protector, Electirizer, Magmarizer, Dubious Disc, Reaper Cloth, Prism Scale, Whipped Dream, Sachet; King's Rock, Metal Coat; Deep Sea Scale, Deep Sea Tooth; Sweet/Tart Apple, Cracked/Chipped Pot; Galarica Cuff, Galarica Wreath.
- **Custom mart price script command** – New script command **`setcustommartprice <price>`** sets the price in Pokedollars for the next **`pokemart`** (e.g. `setcustommartprice 250`). Use before `pokemart` in any map script; use `setcustommartprice 0` to revert to default item prices. The custom price is cleared when the shop is closed.

### 🎛️ **Soul Link Ball & Item Icons**
- **Soul Link Ball** – New Poké Ball type for soul-link runs. When **Soul Link** is ON in Game Mode, 30 Soul Link Balls are added to your PC at new game. Using the ball bypasses the Nuzlocke one-per-route rule; catch rate matches Great Ball (1.5×). Description: *"For use when your soul link partner gets a random shiny encounter."*
- **Soul Link on Game Mode menu** – Game Mode screen now includes a **Soul Link** toggle. When ON, Soul Link Balls are added to the PC at new game (alongside Potion and Infinite Candy).
- **Infinite Candy icon** – Infinite Candy now uses the **infinite_candy.png** item icon (and **infinite_candy.pal** palette) instead of the Rare Candy graphic.
- **Soul Link Ball icon** – Item uses Link ball graphics in battle/party; in PC/bag it uses a dedicated Soul Link icon when built from the 32×32 asset, with a safe fallback to avoid crashes.

### 🎛️ **Game Mode Selection Menu (New Game Intro)**
- **Follow Pokémon toggle** – Optional ON/OFF setting for overworld follower Pokémon (first live party member follows you when enabled).
- **Nuzlocke shiny exception** – In Nuzlocke mode, shiny Pokémon can be caught even if you have already caught a Pokémon on that route or location.
- **Dedicated full-screen Game Mode menu** – After naming your character, the intro pauses and switches to a dedicated settings-style screen (like the in-game Options menu) instead of showing choices in the dialogue box.
- **Clean layout** – "GAME MODE" title in its own bordered white text box; Randomizer, Nuzlocke, Soul Link, **Random Evolution**, **Follow Pokémon**, and Start Game in a second bordered white box with ON/OFF shown inside the window.
- **Random Evolution mode** – New optional mode: when ON, Pokémon evolve into a **random valid species** (chosen by RNG at evolution time) instead of their normal evolution.

### ✨ **Enhanced Difficulty System - COMPLETED!**
The gym battles, Elite Four, and Champion are now **significantly more challenging** with progressive difficulty scaling!

### 🔄 **Elite Four & Champion Dynamax Restriction**
- **Elite Four & Champion now only use Dynamax on ace Pokémon** (like gym leaders)
- **Maintains strategic balance** - ace Pokémon showdowns are the ultimate challenge
- **Consistent with gym battle mechanics** - no more overwhelming full-team Dynamax

### 🆕 **Major Story Battles Now Get Scaled Difficulty!**
- **Rival battles** now receive enhanced AI and difficulty scaling
- **Team Aqua/Magma battles** get progressively harder as you advance
- **All major story encounters** now scale with your progress
- **Consistent challenge** throughout the entire game experience

**🎯 Progressive Challenge:**
- **Gyms 1-2**: Terastallization only (once per battle on ace Pokémon)
- **Gyms 3-8**: Terastallization + Dynamax (Tera once per battle on ace)
- **Elite Four & Champion**: Both gimmicks on ace Pokémon only

**🧠 Smarter AI:**
- **Early gyms**: Basic strategic thinking
- **Mid gyms**: Advanced AI that saves ace Pokémon for last
- **End game**: Master AI with full prediction and strategic switching

**⚡ Battle Gimmicks:**
- **Terastallization**: Available in all main story battles
- **Dynamax**: Restricted to gyms 3-8, Elite Four, and Champion (ace Pokémon only)
- **Mega Evolution**: All mega evolutions are now in the game and mega stones are avaliable for sale in the Mauville City poke center
- **Strategic depth**: Every battle now requires preparation and skill

---

## 🎲 **Randomizer System**

**What it does:**
- Randomizes wild Pokémon species
- Randomizes trainer Pokémon teams
- Gives random movesets to all Pokémon
- Randomizes pickup items
- Randomizes hidden items found in the world
- Adds random Tera types when enabled

**How to use:**
- After the intro (naming, etc.), a **Game Mode** screen appears before "Are you ready?"
- Toggle **Randomizer**, **Nuzlocke**, **Soul Link**, **Random Evolution**, and/or **Follow Pokémon** ON or OFF, then choose **Start Game**
- Your choices apply for that playthrough

---

## 🎲 **Random Evolution Mode**

**What it does:**
- When enabled, any Pokémon that would evolve (level, stone, trade, etc.) **evolves into a random valid species** instead of its normal evolution.
- The target species is determined by the game’s RNG at evolution time (same valid-species pool as the Randomizer; excludes legendaries and problematic species).
- RNG is seeded per evolution so the chosen species is consistent for that evolution event.

**How to use:**
- On the **Game Mode** screen before "Are you ready?", toggle **Random Evolution** ON, then **Start Game**.
- Evolutions throughout the playthrough will be random until you start a new game and turn the mode OFF.

---

## 🐾 **Follow Pokémon Mode**

**What it does:**
- When enabled, your first conscious, non-egg party Pokémon follows you in the overworld (HGSS-style).
- Follower updates automatically when your lead party member changes.
- Respects existing follower restrictions (indoor maps with large sprites, surf/bike states, etc.).

**How to use:**
- On the **Game Mode** screen before "Are you ready?", toggle **Follow Pokémon** ON, then **Start Game**.
- Default is OFF; must be enabled at new game (no mid-save toggle yet).

---

## 🎭 **Nuzlocke Mode**

**Classic Nuzlocke Rules:**
- **One catch per area** - choose wisely!
- **Shiny exception** - shiny Pokémon can always be caught, even on a route/location where you already caught something
- **Forced nicknames** - bond with your team
- **Fainted = Dead** - permanent loss
- **Area tracking** - automatic management

**Enhanced Features:**
- Integrated with difficulty system
- Additional challenge scaling
- Strategic ace Pokémon usage by gym leaders

---

## 🔮 **Terastallization**

**Early Access:**
- Get Tera Orb from May/Brendan with first Poké Balls
- Automatic charging at Pokémon Centers

**Battle Usage:**
- **Gym Leaders**: Once per battle on ace Pokémon only
- **Other Trainers**: Full freedom to use
- **Can combine** with Dynamax for maximum power

---

## ⚡ **Dynamax System**

**Strategic Restrictions:**
- **Available in**: Gym battles, Elite Four, Champion
- **Blocked in**: Wild battles, regular trainer fights
- **Maintains**: Special feeling for important battles

**Usage Rules:**
- **Gyms 1-2**: Not available
- **Gyms 3-8**: Ace Pokémon only
- **Elite Four & Champion**: Ace Pokémon only

---

## 🏆 **Difficulty System Details**

### **Early Game (Gyms 1-2)**
- **Terastallization**: Learn the new mechanic
- **AI Level**: Basic strategic thinking
- **Challenge**: Moderate but fair
- **Focus**: Mastering Terastallization basics

### **Mid Game (Gyms 3-8)**
- **Both Gimmicks**: Terastallization + Dynamax
- **AI Level**: Advanced strategic thinking
- **Challenge**: Significantly harder
- **Focus**: Strategic ace Pokémon battles

### **End Game (Elite Four & Champion)**
- **Strategic Power**: Ace Pokémon use both gimmicks
- **AI Level**: Master-level strategic thinking
- **Challenge**: Maximum difficulty
- **Focus**: Ultimate test of skill and preparation

### **Main Story Battles**
- **Rivals**: Full Terastallization capability + scaled difficulty
- **Team Aqua/Magma**: Enhanced AI + Terastallization + scaled difficulty
- **No Restrictions**: Use battle mechanics freely
- **Progressive Challenge**: AI and stats scale with your progress

---

## 🛠️ **Technical Improvements**

### **Recent Fixes (Latest Update)**
✅ **Follow Pokémon toggle on Game Mode menu**  
✅ **Rebased and builds cleanly on latest RHH master**  
✅ **System fully tested and operational**  
✅ **Memory-efficient battle tracking**  
✅ **Proper header organization**  
✅ **Enhanced maintainability**  
✅ **Added hidden item randomization**  


## 🎯 **Player Experience**

### **What You'll Notice**
- **Every gym battle matters** - no more "easy" early gyms
- **Progressive challenge** - difficulty increases with your progress
- **Strategic depth** - preparation and understanding are rewarded
- **Consistent engagement** - battles stay challenging throughout

### **Strategic Elements Added**
- **Ace Pokémon timing** - when to use limited Terastallization
- **Team building** - consider both gimmicks in your strategy
- **Risk management** - especially important in Nuzlocke mode
- **Battle preparation** - every major battle requires planning

---

## 🚀 **Getting Started**

### **New Game Setup**
1. **Start new game** - Professor Birch introduces new features
2. **Choose game modes** - Toggle Randomizer, Nuzlocke, Soul Link, Random Evolution, and Follow Pokémon ON or OFF
3. **Receive Tera Orb** - from May/Brendan with first Poké Balls
4. **Begin your journey** - with enhanced difficulty and features!

### **Tips for Success**
- **Prepare for every gym** - no battle is easy anymore
- **Learn gimmick mechanics** - Terastallization in early gyms
- **Save your best moves** - for the ace Pokémon showdowns
- **Build balanced teams** - consider both gimmicks in your strategy

---

## ✅ **System Status**

**🏆 PRODUCTION READY**  
**🎮 All Features Implemented**  
**🧪 Fully Tested**  
**🚀 Ready for Players**  
**✨ Enhanced Experience Guaranteed**

---

*Last Updated: July 7, 2026 — Follow Pokémon Game Mode toggle*
*All features are production-ready and enhance the core Pokémon Emerald experience while maintaining game balance and stability. Saves from builds prior to this rebase will not load.*