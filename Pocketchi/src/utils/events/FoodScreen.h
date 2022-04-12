#pragma once

class FoodScreen
{
private:
  uint8_t cycleAnimation;

public:
  bool action(Utils *utils)
  {
    if (cycleAnimation == 0)
    {
      return true;
    }
    return false;
  }

  void refresh()
  {
    cycleAnimation = 40;
  }

  void eventDisplay(Utils *utils, Stats *stats)
  {
    utils->uiDraw.DisplayHealthRight(stats->getHP());

    if (cycleAnimation == 15)
    {
      stats->incHP(1);
    }

    if (cycleAnimation > 30)
    {
      Arduboy2Base::drawBitmap(8, 29, Common::food, 30, 30, WHITE);
    }
    else if (cycleAnimation > 20)
    {
      Arduboy2Base::drawBitmap(8, 29, Common::food2, 30, 30, WHITE);
    }
    else if (cycleAnimation > 10)
    {
      Arduboy2Base::drawBitmap(8, 29, Common::food3, 30, 30, WHITE);
    }

    cycleAnimation--;

    utils->charDraw.DisplayMovingLeft(utils->cycle, MAX_MOVEMENT_STEPS - 3, 28);
  }
};
