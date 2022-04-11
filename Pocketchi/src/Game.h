#pragma once

#define MAX_MOVEMENT_STEPS 7
#define MAX_LIFE 7
#define MAX_ANIMATION_FRAMES 20
#define MAX_BATTLE_POINTS 14
#define MAX_IDLE_ANIMATION_FRAMES 4
#define MAX_CHALLENGE_LEVEL 7
#define MAX_STEPS 25

#define CYCLE_MAX 20
#define CYCLE_HALF 10

#include "utils/Utils.h"

class Game
{
public:
  void setup(void);
  void loop(void);
  void mainMenuTick(void);
  void mainIdleTick(void);
  void mainBattleTick(void);
  void mainBattleAnimationTick(void);
  void mainFoodTick(void);
  void mainHealthTick(void);
  void mainSickTick(void);
  void mainVictoryTick(void);
  void mainAutosaveTick(void);
};
