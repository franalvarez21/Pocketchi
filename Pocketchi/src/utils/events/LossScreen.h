#pragma once

class LossScreen
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
    cycleAnimation = MAX_ANIMATION_FRAMES;
  }

  void eventDisplay(Utils *utils)
  {
    if (utils->cycle < CYCLE_HALF)
    {
      Arduboy2Base::drawBitmap(8, 8, Common::actionButtonKO, 30, 30, WHITE);
      Arduboy2Base::drawBitmap(90, 8, Common::actionButtonKO, 30, 30, WHITE);
    }
    else
    {
      Arduboy2Base::drawBitmap(8, 8, Common::actionButton, 30, 30, WHITE);
      Arduboy2Base::drawBitmap(90, 8, Common::actionButton, 30, 30, WHITE);
    }

    cycleAnimation--;

    utils->charDraw.DisplaySick(utils->cycle, MAX_MOVEMENT_STEPS - 3, 28);
  }
};
