#pragma once

class VictoryScreen
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
    cycleAnimation = MAX_ANIMATION_FRAMES * 2;
  }

  void eventDisplay(Utils *utils)
  {
    if (utils->cycle < CYCLE_HALF)
    {
      Arduboy2Base::drawBitmap(8, 8, Common::actionButtonOK, 30, 30, WHITE);
      Arduboy2Base::drawBitmap(90, 8, Common::actionButtonOK, 30, 30, WHITE);
    }
    else
    {
      Arduboy2Base::drawBitmap(8, 8, Common::actionButton, 30, 30, WHITE);
      Arduboy2Base::drawBitmap(90, 8, Common::actionButton, 30, 30, WHITE);
    }

    cycleAnimation--;

    utils->charDraw.DisplayIdle(utils->cycle, MAX_MOVEMENT_STEPS - 3, 28);
  }
};
