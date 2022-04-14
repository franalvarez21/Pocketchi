#pragma once

#include "../Game.h"

class TitleMenu
{
private:
  size_t actionTime = MAX_ANIMATION_FRAMES;
  bool actionFlag = false;
  bool actionType = false;

public:
  size_t action()
  {
    if (!actionFlag)
    {
      if (Arduboy2Base::justPressed(A_BUTTON))
      {
        actionTime = MAX_ANIMATION_FRAMES;
        actionType = false;
        actionFlag = true;
      }
      else if (Arduboy2Base::justPressed(B_BUTTON))
      {
        actionTime = MAX_ANIMATION_FRAMES;
        actionType = true;
        actionFlag = true;
      }
    }
    else if (actionTime == 0)
    {
      actionTime = MAX_ANIMATION_FRAMES;
      actionFlag = false;
      return actionType ? 1 : 2;
    }
    return 0;
  }

  void eventDisplay(Utils *utils)
  {
    Arduboy2Base::drawBitmap(0, 0, Title::titleScreen, 128, 64, WHITE);

    if (actionFlag)
    {
      if (actionTime > 0)
      {
        actionTime--;
      }

      if (actionType)
      {
        Arduboy2Base::drawBitmap(90, 30, Common::actionButtonOK, 30, 30, WHITE);
      }
      else
      {
        Arduboy2Base::drawBitmap(90, 30, Common::actionButtonKO, 30, 30, WHITE);
      }
    }
    else
    {
      Arduboy2Base::drawBitmap(90, 30, Common::actionButton, 30, 30, WHITE);
    }

    if (utils->cycle < CYCLE_HALF)
    {
      Arduboy2Base::drawBitmap(16, 29, Title::titleAnimation, 46, 34, WHITE);
    }
    else
    {
      Arduboy2Base::drawBitmap(16, 29, Title::titleAnimation2, 46, 34, WHITE);
    }

    utils->texts.printLine(66, 52, "START");
    utils->texts.printLine(64, 57, "RESET");
  }
};
