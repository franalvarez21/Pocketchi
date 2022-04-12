#pragma once

class SickScreen
{
private:
  bool waitingAction;
  uint8_t cycleAnimation;

public:
  bool action(Utils *utils)
  {
    if (Arduboy2Base::justPressed(B_BUTTON) || Arduboy2Base::justPressed(A_BUTTON))
    {
      waitingAction = false;
    }

    if (cycleAnimation == 0)
    {
      return true;
    }
    return false;
  }

  void refresh()
  {
    waitingAction = true;
    cycleAnimation = MAX_ANIMATION_FRAMES * 2;
  }

  void eventDisplay(Utils *utils)
  {

    if (waitingAction)
    {
      Arduboy2Base::drawBitmap(89, 6, Common::KO, 32, 32, WHITE);

      Arduboy2Base::drawBitmap(8, 8, Common::actionButton, 30, 30, WHITE);
    }
    else
    {
      Arduboy2Base::drawBitmap(90, 8, Common::healthKit, 30, 30, WHITE);

      if (utils->cycle < CYCLE_HALF)
      {
        Arduboy2Base::drawBitmap(8, 8, Common::actionButtonOK, 30, 30, WHITE);
      }
      else
      {
        Arduboy2Base::drawBitmap(8, 8, Common::actionButton, 30, 30, WHITE);
      }

      cycleAnimation--;
    }

    utils->charDraw.DisplaySick(utils->cycle, MAX_MOVEMENT_STEPS - 3, 28);
  }
};
