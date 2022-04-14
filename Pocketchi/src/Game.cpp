
#include "Game.h"

#include "menus/TitleMenu.h"
#include "utils/events/IdleScreen.h"
#include "utils/events/TimeEventScreen.h"
#include "utils/events/BattleScreen.h"
#include "utils/events/StartBattleScreen.h"
#include "utils/events/VictoryScreen.h"
#include "utils/events/FoodScreen.h"
#include "utils/events/LossScreen.h"
#include "utils/events/SickScreen.h"

Arduboy2Base arduboy;
byte gameID;

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
StartBattleScreen startBattleScreen;

void Game::setup(void)
{
  arduboy.begin();
  arduboy.setFrameRate(15);
  arduboy.initRandomSeed();
  arduboy.systemButtons();
  arduboy.waitNoButtons();
  arduboy.audio.off();
  gameID = GAME_ID;

  if ((EEPROM.read(SAVE_FILE_ADDRESS) == gameID) && (EEPROM.read(SAVE_FILE_ADDRESS + sizeof(byte) + sizeof(Stats)) == gameID))
  {
    loadGame();
  }
  else
  {
    stats.init();
  }

  changeStage(0);
}

void Game::changeStage(uint8_t stage)
{
  onStage = stage;
  utils.refreshCycle();
}

void Game::loadGame(void)
{
  EEPROM.get(SAVE_FILE_ADDRESS + sizeof(byte), stats);
}

void Game::saveGame(void)
{
  EEPROM.put(SAVE_FILE_ADDRESS, gameID);
  EEPROM.put(SAVE_FILE_ADDRESS + sizeof(byte), stats);
  EEPROM.put(SAVE_FILE_ADDRESS + sizeof(byte) + sizeof(Stats), gameID);
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
  case 8:
    mainStartBattleTick();
    break;
  default:
    mainMenuTick();
    break;
  }

  utils.tick();

  arduboy.display();
}

void Game::mainMenuTick(void)
{
  rand() % analogRead(0);
  titleMenu.eventDisplay(&utils);
  switch (titleMenu.action())
  {
  case 1:
    changeStage(1);
    idleScreen.refresh();
    break;
  case 2:
    stats.init();
    changeStage(1);
    idleScreen.refresh();
    break;
  }
}

void Game::mainIdleTick(void)
{
  idleScreen.eventDisplay(&utils, &stats);
  switch (idleScreen.action(&utils))
  {
  case 1:
    changeStage(4);
    foodScreen.refresh();
    break;
  case 2:
    changeStage(8);
    stats.refreshEnemy();
    stats.startBattle();
    startBattleScreen.refresh();
    break;
  case 3:
    saveGame();
    break;
  }
}

void Game::mainBattleTick(void)
{
  timeEventScreen.eventDisplay(&utils, &stats);
  switch (timeEventScreen.action(&utils, &stats))
  {
  case 1:
    changeStage(3);
    battleAction = false;
    battleScreen.refresh();
    break;
  case 2:
    changeStage(3);
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
    changeStage(2);
    stats.refresh();
    break;
  case 2:
    changeStage(6);
    lossScreen.refresh();
    stats.incHP(MAX_LIFE);
    stats.refreshDistance();
    break;
  case 3:
    changeStage(7);
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
    changeStage(7);
    victoryScreen.refresh();
  }
}

void Game::mainSickTick(void)
{
  sickScreen.eventDisplay(&utils);
  if (sickScreen.action(&utils))
  {
    changeStage(7);
    victoryScreen.refresh();
  }
}

void Game::mainLossTick(void)
{
  lossScreen.eventDisplay(&utils);
  if (lossScreen.action(&utils))
  {
    changeStage(5);
    sickScreen.refresh();
  }
}

void Game::mainVictoryTick(void)
{
  victoryScreen.eventDisplay(&utils);
  if (victoryScreen.action(&utils))
  {
    changeStage(1);
    idleScreen.refresh();
  }
}

void Game::mainStartBattleTick(void)
{
  startBattleScreen.eventDisplay(&utils, &stats);
  if (startBattleScreen.action())
  {
    changeStage(2);
  }
}
