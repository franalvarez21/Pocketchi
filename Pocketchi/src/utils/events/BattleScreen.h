#pragma once

class BattleScreen
{
private:
  uint8_t currentPosition;
  uint8_t cycleAnimation;

public:
  uint8_t action(Utils *utils, Stats *stats, bool battleAction)
  {
    if (cycleAnimation == 0)
    {
      if (battleAction)
      {
        stats->decHPEnemy(1);
      }
      else
      {
        stats->decHP(1);
      }

      if (stats->getHP() == 0)
      {
        return 2;
      }
      else if (stats->getHPEnemy() == 0)
      {
        return 3;
      }
      else
      {
        return 1;
      }
    }
    return 4;
  }

  void refresh()
  {
    cycleAnimation = MAX_ANIMATION_FRAMES * 2;
  }

  void eventDisplay(Utils *utils, Stats *stats, bool battleAction)
  {
    Arduboy2Base::drawBitmap(8, 8, Common::healthLeft, 6, 55, WHITE);
    Arduboy2Base::drawBitmap(114, 8, Common::healthRight, 6, 55, WHITE);

    for (uint8_t i = 0; i < MAX_LIFE - stats->getHP(); i++)
    {
      Arduboy2Base::drawBitmap(114, 8 + (i * 8), Common::healthOff, 4, 7, BLACK);
    }

    for (uint8_t i = 0; i < MAX_LIFE - stats->getHPEnemy(); i++)
    {
      Arduboy2Base::drawBitmap(10, 8 + (i * 8), Common::healthOff, 4, 7, BLACK);
    }

    if (battleAction)
    {
      if (utils->cycle % 4 == 0)
      {
        Arduboy2Base::drawBitmap(10, 8 + ((MAX_LIFE - stats->getHPEnemy()) * 8), Common::healthOff, 4, 7, BLACK);
      }
    }
    else
    {
      if (utils->cycle % 4 == 0)
      {
        Arduboy2Base::drawBitmap(114, 8 + ((MAX_LIFE - stats->getHP()) * 8), Common::healthOff, 4, 7, BLACK);
      }
    }

    cycleAnimation--;

    displayLookingLeft(utils, MAX_MOVEMENT_STEPS - 1, (MAX_MOVEMENT_STEPS - 1) * 12, 28, battleAction);
    displayLookingRight(utils, 3, (3 - 1) * 12, 28, battleAction);
  }

  void displayLookingLeft(Utils *utils, uint8_t position, uint8_t screenPosition, uint8_t heightPosition, bool battleAction)
  {
    Arduboy2Base::drawBitmap(screenPosition, heightPosition, battleAction ? Pet::body3 : Pet::body, 32, 32, WHITE);
    Arduboy2Base::drawBitmap(screenPosition + 10, battleAction ? heightPosition + 13 : heightPosition + 17, battleAction ? Pet::eye4 : Pet::eye3, 8, 8, WHITE);
    if (utils->cycle < CYCLE_HALF)
    {
      Arduboy2Base::drawBitmap(screenPosition + 22, heightPosition - 4, Pet::rightEar, 16, 16, WHITE);
    }
    else
    {
      Arduboy2Base::drawBitmap(screenPosition + 22, heightPosition - 2, Pet::rightEar2, 16, 16, WHITE);
    }
  }

  void displayLookingRight(Utils *utils, uint8_t position, uint8_t screenPosition, uint8_t heightPosition, bool battleAction)
  {
    Arduboy2Base::drawBitmap(screenPosition, heightPosition, battleAction ? Pet::body : Pet::body4, 32, 32, WHITE);
    Arduboy2Base::drawBitmap(screenPosition + 14, battleAction ? heightPosition + 17 : heightPosition + 13, battleAction ? Pet::eye3 : Pet::eye2, 8, 8, WHITE);
    if (utils->cycle < CYCLE_HALF)
    {
      Arduboy2Base::drawBitmap(screenPosition - 6, heightPosition - 4, Pet::leftEar, 16, 16, WHITE);
    }
    else
    {
      Arduboy2Base::drawBitmap(screenPosition - 6, heightPosition - 2, Pet::leftEar2, 16, 16, WHITE);
    }
  }
};
