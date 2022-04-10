#pragma once

#include "../Game.h"

class TitleMenu
{
public:
  bool action(Utils *utils)
  {
    return (Arduboy2Base::justPressed(B_BUTTON) || Arduboy2Base::justPressed(A_BUTTON));
  }

  void eventDisplay(Utils *utils)
  {
    Arduboy2Base::drawBitmap(0, 0, Title::titleScreen, 128, 64, WHITE);
  }
};
