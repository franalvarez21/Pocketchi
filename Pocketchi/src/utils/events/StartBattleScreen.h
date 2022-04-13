#pragma once

class StartBattleScreen
{
private:
  uint8_t cycleAnimation;

public:
  bool action()
  {
    if (cycleAnimation == 0)
    {
      return true;
    }
    return false;
  }

  void refresh()
  {
    cycleAnimation = MAX_ANIMATION_FRAMES + 16;
  }

  void eventDisplay(Utils *utils, Stats *stats)
  {
    Arduboy2Base::drawBitmap((MAX_MOVEMENT_STEPS * 12) + 6, 20, Common::exclamation, 10, 10, WHITE);

    cycleAnimation--;

    utils->charDraw.DisplayLookingLeft(utils->cycle, MAX_MOVEMENT_STEPS, 28, false);
    utils->charDraw.DisplayEnemy(utils->cycle, stats->getCurrentEnemyID(), stats->getDistance(), false);
  }
};
