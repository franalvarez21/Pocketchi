#pragma once

class UIDraw
{
public:
  void DisplayHealthRight(uint8_t hp)
  {
    Arduboy2Base::drawBitmap(116, 8, Common::healthRight, 6, 55, WHITE);
    for (uint8_t i = 0; i < MAX_LIFE - hp; i++)
    {
      Arduboy2Base::drawBitmap(116, 8 + (i * 8), Common::healthOff, 4, 7, BLACK);
    }
  }

  void DisplayHealthLeft(uint8_t hp)
  {
    Arduboy2Base::drawBitmap(6, 8, Common::healthLeft, 6, 55, WHITE);
    for (uint8_t i = 0; i < MAX_LIFE - hp; i++)
    {
      Arduboy2Base::drawBitmap(8, 8 + (i * 8), Common::healthOff, 4, 7, BLACK);
    }
  }
};
