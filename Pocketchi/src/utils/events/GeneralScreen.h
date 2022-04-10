#pragma once

class GeneralScreen
{
public:
  void eventDisplay(Utils *utils)
  {
    Arduboy2Base::drawBitmap(0, 0, Title::leftSide, 4, 64, WHITE);
    Arduboy2Base::drawBitmap(124, 0, Title::rightSide, 4, 64, WHITE);
  }
};
