
#include "Game.h"

#include "menus/TitleMenu.h"
#include "utils/events/IdleScreen.h"
#include "utils/events/TimeEventScreen.h"
#include "utils/events/GeneralScreen.h"
#include "utils/events/BattleScreen.h"

Arduboy2Base arduboy;

uint8_t onStage;
bool battleAction;

Utils utils;
Stats stats;

TitleMenu titleMenu;
IdleScreen idleScreen;
TimeEventScreen timeEventScreen;
GeneralScreen generalscreen;
BattleScreen battleScreen;

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
    mainHealthTick();
    break;
  case 6:
    mainSickTick();
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
  titleMenu.eventDisplay(&utils);
  if (titleMenu.action(&utils))
  {
    onStage = 1;
  }
}

void Game::mainIdleTick(void)
{
  idleScreen.eventDisplay(&utils);
  switch (idleScreen.action(&utils))
  {
  case 1:
    onStage = 4;
    break;
  case 2:
    stats.startBattle();
    onStage = 2;
    break;
  }

  generalscreen.eventDisplay(&utils);
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

  generalscreen.eventDisplay(&utils);
}

void Game::mainBattleAnimationTick(void)
{
  battleScreen.eventDisplay(&utils, &stats, battleAction);
  switch (battleScreen.action(&utils, &stats, battleAction))
  {
  case 1:
    onStage = 2; // continue
    break;
  case 2:
    onStage = 6; // sick / loss
    break;
  case 3:
    onStage = 7; // won
    break;
  }

  generalscreen.eventDisplay(&utils);
}

void Game::mainFoodTick(void)
{
  onStage = 1;
}

void Game::mainHealthTick(void)
{
  onStage = 1;
}

void Game::mainSickTick(void)
{
  onStage = 1;
}

void Game::mainVictoryTick(void)
{
  onStage = 1;
}

void Game::mainAutosaveTick(void)
{
  onStage = 1;
}
