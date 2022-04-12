#pragma once

class CharDraw
{
public:
  void DisplayDummy(uint8_t screenPosition, uint8_t heightPosition)
  {
    screenPosition = screenPosition * 12;

    Arduboy2Base::drawBitmap(screenPosition, heightPosition, Common::dummy, 32, 40, WHITE);
  }

  void DisplayLookingLeft(uint8_t cycle, uint8_t screenPosition, uint8_t heightPosition, bool battleAction)
  {
    screenPosition = screenPosition * 12;

    Arduboy2Base::drawBitmap(screenPosition + 6, heightPosition + 19, battleAction ? Pet::eye2 : Pet::eye3, 8, 8, WHITE);

    DisplayFullBody(cycle, false, true, screenPosition, heightPosition);
  }

  void DisplayLookingRight(uint8_t cycle, uint8_t screenPosition, uint8_t heightPosition, bool battleAction)
  {
    screenPosition = screenPosition * 12;

    Arduboy2Base::drawBitmap(screenPosition + 18, heightPosition + 19, battleAction ? Pet::eye3 : Pet::eye4, 8, 8, WHITE);

    DisplayFullBody(cycle, true, false, screenPosition, heightPosition);
  }

  void DisplayMovingLeft(uint8_t cycle, uint8_t screenPosition, uint8_t heightPosition)
  {
    screenPosition = screenPosition * 12;

    Arduboy2Base::drawBitmap(screenPosition + 6, heightPosition + 19, Pet::eye, 8, 8, WHITE);

    DisplayFullBody(cycle, false, true, screenPosition, heightPosition);
  }

  void DisplayMovingRight(uint8_t cycle, uint8_t screenPosition, uint8_t heightPosition)
  {
    screenPosition = screenPosition * 12;

    Arduboy2Base::drawBitmap(screenPosition + 18, heightPosition + 19, Pet::eye, 8, 8, WHITE);

    DisplayFullBody(cycle, true, false, screenPosition, heightPosition);
  }

  void DisplayIdle(uint8_t cycle, uint8_t screenPosition, uint8_t heightPosition)
  {
    screenPosition = screenPosition * 12;

    Arduboy2Base::drawBitmap(screenPosition + 6, heightPosition + 19, Pet::eye, 8, 8, WHITE);
    Arduboy2Base::drawBitmap(screenPosition + 18, heightPosition + 19, Pet::eye, 8, 8, WHITE);

    DisplayFullBody(cycle, true, true, screenPosition, heightPosition);
  }

  void DisplaySick(uint8_t cycle, uint8_t screenPosition, uint8_t heightPosition)
  {
    screenPosition = screenPosition * 12;

    Arduboy2Base::drawBitmap(screenPosition + 6, heightPosition + 19, Pet::eye3, 8, 8, WHITE);
    Arduboy2Base::drawBitmap(screenPosition + 18, heightPosition + 19, Pet::eye3, 8, 8, WHITE);

    DisplayFullBody(cycle, true, true, screenPosition, heightPosition);
  }

private:
  void DisplayFullBody(uint8_t cycle, bool leftEar, bool rightEar, uint8_t screenPosition, uint8_t heightPosition)
  {
    if (cycle < CYCLE_HALF)
    {
      Arduboy2Base::drawBitmap(screenPosition, heightPosition, Pet::body, 32, 32, WHITE);
      if (leftEar)
        Arduboy2Base::drawBitmap(screenPosition - 6, heightPosition - 4, Pet::leftEar, 16, 16, WHITE);
      if (rightEar)
        Arduboy2Base::drawBitmap(screenPosition + 22, heightPosition - 4, Pet::rightEar, 16, 16, WHITE);
    }
    else
    {
      Arduboy2Base::drawBitmap(screenPosition, heightPosition, Pet::body2, 32, 32, WHITE);
      if (leftEar)
        Arduboy2Base::drawBitmap(screenPosition - 6, heightPosition - 2, Pet::leftEar2, 16, 16, WHITE);
      if (rightEar)
        Arduboy2Base::drawBitmap(screenPosition + 22, heightPosition - 2, Pet::rightEar2, 16, 16, WHITE);
    }
  }
};
