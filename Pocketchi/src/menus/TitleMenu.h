#pragma once

#include "../Game.h"

class TitleMenu
{
private:
  uint8_t actionTime = MAX_ANIMATION_FRAMES;
  bool actionFlag = false;
  bool actionType = false;

public:
  bool action()
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
      return actionType;
    }
    return false;
  }

  void eventDisplay()
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
  }
};
