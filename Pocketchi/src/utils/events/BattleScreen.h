#pragma once

class BattleScreen
{
private:
  uint8_t cycleAnimation;

public:
  uint8_t action(Stats *stats, bool battleAction)
  {
    if (cycleAnimation == 0)
    {
      if (battleAction)
      {
        stats->decHPEnemy(1);
      }
      else if (stats->getCurrentEnemyID() != 1)
      {
        stats->decHP(1);
      }

      if (stats->getHP() == 0)
      {
        return 2;
      }
      else if (stats->getHPEnemy() == 0)
      {
        return 3;
      }
      else
      {
        return 1;
      }
    }
    return 4;
  }

  void refresh()
  {
    cycleAnimation = MAX_ANIMATION_FRAMES * 2;
  }

  void eventDisplay(Utils *utils, Stats *stats, bool battleAction)
  {
    utils->uiDraw.DisplayHealthRight(stats->getHP());
    utils->uiDraw.DisplayHealthLeft(stats->getHPEnemy());

    if (battleAction)
    {
      if (utils->cycle % 4 == 0)
      {
        Arduboy2Base::drawBitmap(10, 8 + ((MAX_LIFE - stats->getHPEnemy()) * 8), Common::healthOff, 4, 7, BLACK);
      }
    }
    else if (stats->getCurrentEnemyID() != 1)
    {
      if (utils->cycle % 4 == 0)
      {
        Arduboy2Base::drawBitmap(114, 8 + ((MAX_LIFE - stats->getHP()) * 8), Common::healthOff, 4, 7, BLACK);
      }
    }

    cycleAnimation--;

    utils->charDraw.DisplayLookingLeft(utils->cycle, MAX_MOVEMENT_STEPS - 1, 28, battleAction);
    utils->charDraw.DisplayEnemy(utils->cycle, stats->getCurrentEnemyID(), stats->getDistance(), battleAction);
  }
};
