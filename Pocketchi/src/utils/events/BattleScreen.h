#pragma once

class BattleScreen
{
private:
  size_t cycleAnimation;

public:
  size_t action(Stats *stats, bool battleAction)
  {
    if (cycleAnimation == 0)
    {
      if (battleAction)
      {
        stats->decHPEnemy(1);
      }
      else if (stats->getCurrentEnemyID() != 1)
      {
        if (stats->getDistance() == 1)
        {
          stats->decHP(2);
        }
        else
        {
          stats->decHP(1);
        }
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
    cycleAnimation = MAX_ANIMATION_FRAMES + 16;
  }

  void eventDisplay(Utils *utils, Stats *stats, bool battleAction)
  {
    utils->uiDraw.DisplayHealthRight(stats->getHP());
    utils->uiDraw.DisplayHealthLeft(stats->getHPEnemy());

    if (battleAction)
    {
      if (utils->cycle % 4 == 0)
      {
        Arduboy2Base::drawBitmap(8, 8 + ((MAX_LIFE - stats->getHPEnemy()) * 8), Common::healthOff, 4, 7, BLACK);
      }
    }
    else if (stats->getCurrentEnemyID() != 1)
    {
      if (utils->cycle % 4 == 0)
      {
        if (stats->getDistance() == 1 && stats->getHP() > 1)
        {
          Arduboy2Base::drawBitmap(116, 8 + ((MAX_LIFE - stats->getHP() + 1) * 8), Common::healthOff, 4, 7, BLACK);
        }
        Arduboy2Base::drawBitmap(116, 8 + ((MAX_LIFE - stats->getHP()) * 8), Common::healthOff, 4, 7, BLACK);
      }
    }

    cycleAnimation--;

    utils->charDraw.DisplayLookingLeft(utils->cycle, MAX_MOVEMENT_STEPS - 1, 28, battleAction);
    utils->charDraw.DisplayEnemy(utils->cycle, stats->getCurrentEnemyID(), stats->getDistance(), battleAction, true);
  }
};
