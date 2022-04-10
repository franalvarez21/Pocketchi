
#include "Game.h"

#include "menus/TitleMenu.h"
#include "utils/events/IdleScreen.h"
#include "utils/events/GeneralScreen.h"

Arduboy2Base arduboy;

uint8_t onStage;

Utils utils;
Stats stats;

TitleMenu titleMenu;
IdleScreen idleScreen;
GeneralScreen generalscreen;

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
    mainFoodTick();
    break;
  case 4:
    mainHealthTick();
    break;
  case 5:
    mainSickTick();
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
    // onStage = 2;
    break;
  case 2:
    // onStage = 0;
    break;
  }

  generalscreen.eventDisplay(&utils);
}

void Game::mainBattleTick(void)
{
  /*
  if (arduboy.justPressed(A_BUTTON))
  {
    pauseMenu.refresh();
    onStage = 1;

    stats.displayHub(&numbers);
    dungeon.borders();
  }
  else
  {
    action = dungeon.movePlayer(&utils, &stats);
    if (actions.evaluateAction(&utils, &stats, &dungeon, action))
    {
      dungeon.cutsceneStart(false);
      onStage = 4;
    }
    else if (dungeon.level < MAX_LEVEL)
    {
      dungeon.display(utils.cycle, utils.mode);
    }

    if ((utils.mode == 0 && dungeon.level == MAX_LEVEL) || (utils.mode == 1 && dungeon.level == MAX_CHALLENGE_LEVEL) || (utils.mode == 2 && dungeon.level == MAX_ADVANCE_LEVEL))
    {
      dungeon.cutsceneStart(false);
      onStage = 6;
    }
    else if (stats.getHP() < 1)
    {
      utils.overBeep();
      dungeon.cutsceneStart(true);
      onStage = 5;
    }
    else
    {
      stats.displayHub(&numbers);
      dungeon.borders();
    }
  }
  */
}

void Game::mainFoodTick(void)
{
  /*
  dungeon.cutscene.eventDisplay();
  if (utils.mode == 0)
  {
    Arduboy2Base::drawBitmap(0, 0, Title::title_loading, 128, 64, WHITE);
  }
  else if (utils.mode == 1)
  {
    Arduboy2Base::drawBitmap(0, 0, Title::title_loading_2, 128, 64, WHITE);
  }
  else if (utils.mode == 2)
  {
    Arduboy2Base::drawBitmap(0, 0, Title::title_loading_3, 128, 64, WHITE);
  }
  if (dungeon.cutscene.enabled())
  {
    onStage = 2;
  }
  */
}

void Game::mainHealthTick(void)
{
  /*
  dungeon.displayLevelStart(&utils, &effects);
  dungeon.cutscene.eventDisplay();
  if (dungeon.cutscene.enabled())
  {
    onStage = 2;
  }

  dungeon.borders();
  dungeon.displayLevel(&numbers);
  stats.displayHub(&numbers, false);
  */
}

void Game::mainSickTick(void)
{
  /*
  dungeon.displayGameOver(&stats, &numbers);
  dungeon.cutscene.eventDisplay();
  if (dungeon.cutscene.enabled() && (arduboy.justPressed(A_BUTTON) || arduboy.justPressed(B_BUTTON) || arduboy.justPressed(LEFT_BUTTON) || arduboy.justPressed(RIGHT_BUTTON)))
  {
    onStage = 0;
  }
  */
}

void Game::mainAutosaveTick(void)
{
  /*
  dungeon.displayEnding(&stats, &numbers);
  dungeon.cutscene.eventDisplay();
  if (dungeon.cutscene.enabled() && (arduboy.justPressed(A_BUTTON) || arduboy.justPressed(B_BUTTON) || arduboy.justPressed(LEFT_BUTTON) || arduboy.justPressed(RIGHT_BUTTON)))
  {
    onStage = 0;
  }
  */
}
