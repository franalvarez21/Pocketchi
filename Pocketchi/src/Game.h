#pragma once

#define MAX_MOVEMENT_STEPS 7
#define MAX_LIFE 7
#define MAX_LEVEL 999
#define MAX_ANIMATION_FRAMES 20
#define MAX_BATTLE_POINTS 14
#define MAX_IDLE_ANIMATION_FRAMES 4

#define CYCLE_MAX 20
#define CYCLE_HALF 10

#define SAVE_FILE_ADDRESS (EEPROM_STORAGE_SPACE_START + 64)
#define GAME_ID 112

#include "utils/Utils.h"

class Game
{
public:
  void setup(void);
  void changeStage(uint8_t);
  void loop(void);
  void loadGame(void);
  void saveGame(void);
  void mainMenuTick(void);
  void mainIdleTick(void);
  void mainBattleTick(void);
  void mainBattleAnimationTick(void);
  void mainFoodTick(void);
  void mainHealthTick(void);
  void mainSickTick(void);
  void mainLossTick(void);
  void mainVictoryTick(void);
  void mainStartBattleTick(void);
};
