
#include "Game.h"

#include "menus/TitleMenu.h"
#include "utils/events/IdleScreen.h"
#include "utils/events/TimeEventScreen.h"
#include "utils/events/BattleScreen.h"
#include "utils/events/VictoryScreen.h"
#include "utils/events/FoodScreen.h"
#include "utils/events/LossScreen.h"
#include "utils/events/SickScreen.h"

Arduboy2Base arduboy;

uint8_t onStage;
bool battleAction;

Utils utils;
Stats stats;

TitleMenu titleMenu;
IdleScreen idleScreen;
TimeEventScreen timeEventScreen;
BattleScreen battleScreen;
VictoryScreen victoryScreen;
FoodScreen foodScreen;
LossScreen lossScreen;
SickScreen sickScreen;

void Game::setup(void)
{
  arduboy.begin();
  arduboy.setFrameRate(15);
  arduboy.initRandomSeed();
  arduboy.systemButtons();
  arduboy.waitNoButtons();
  arduboy.audio.off();

  stats.init();
  onStage = 0;
  idleScreen.refreshMessageCycle();
}

void Game::loop(void)
{
  if (!(arduboy.nextFrame()))
  {
    return;
  }

  arduboy.pollButtons();
  arduboy.clear();

  switch (onStage)
  {
  case 0:
    mainMenuTick();
    break;
  case 1:
    mainIdleTick();
    break;
  case 2:
    mainBattleTick();
    break;
  case 3:
    mainBattleAnimationTick();
    break;
  case 4:
    mainFoodTick();
    break;
  case 5:
    mainSickTick();
    break;
  case 6:
    mainLossTick();
    break;
  case 7:
    mainVictoryTick();
    break;
  default:
    mainAutosaveTick();
    break;
  }

  utils.tick();

  arduboy.display();
}

void Game::mainMenuTick(void)
{
  rand() % analogRead(0);
  titleMenu.eventDisplay();
  if (titleMenu.action())
  {
    onStage = 1;
    idleScreen.refresh();
  }
}

void Game::mainIdleTick(void)
{
  idleScreen.eventDisplay(&utils, &stats);
  switch (idleScreen.action(&utils))
  {
  case 1:
    onStage = 4;
    foodScreen.refresh();
    break;
  case 2:
    onStage = 2;
    stats.startBattle();
    break;
  }
}

void Game::mainBattleTick(void)
{
  timeEventScreen.eventDisplay(&utils, &stats);
  switch (timeEventScreen.action(&utils, &stats))
  {
  case 1:
    onStage = 3;
    battleAction = false;
    battleScreen.refresh();
    break;
  case 2:
    onStage = 3;
    battleAction = true;
    battleScreen.refresh();
    break;
  }
}

void Game::mainBattleAnimationTick(void)
{
  battleScreen.eventDisplay(&utils, &stats, battleAction);
  switch (battleScreen.action(&stats, battleAction))
  {
  case 1:
    onStage = 2;
    stats.refresh();
    break;
  case 2:
    onStage = 6;
    lossScreen.refresh();
    stats.incHP(MAX_LIFE);
    stats.refreshDistance();
    break;
  case 3:
    onStage = 7;
    victoryScreen.refresh();
    stats.redDistance(1);
    break;
  }
}

void Game::mainFoodTick(void)
{
  foodScreen.eventDisplay(&utils, &stats);
  if (foodScreen.action(&utils))
  {
    onStage = 7;
    victoryScreen.refresh();
  }
}

void Game::mainSickTick(void)
{
  sickScreen.eventDisplay(&utils);
  if (sickScreen.action(&utils))
  {
    onStage = 7;
    victoryScreen.refresh();
  }
}

void Game::mainLossTick(void)
{
  lossScreen.eventDisplay(&utils);
  if (lossScreen.action(&utils))
  {
    onStage = 5;
    sickScreen.refresh();
  }
}

void Game::mainVictoryTick(void)
{
  victoryScreen.eventDisplay(&utils);
  if (victoryScreen.action(&utils))
  {
    onStage = 1;
    idleScreen.refresh();
  }
}

void Game::mainAutosaveTick(void)
{
  onStage = 1;
}
