#pragma once

class CharDraw
{
public:
  void DisplayEnemy(size_t cycle, size_t enemyID, size_t distance, bool battleAction, bool displayStar)
  {
    switch (enemyID)
    {
    case 1:
      Arduboy2Base::drawBitmap(24, 20, Enemies::dummy, 32, 40, WHITE);
      break;
    case 2:
      if (cycle < CYCLE_HALF)
      {
        Arduboy2Base::drawBitmap(24, 20, Enemies::mouse, 32, 40, WHITE);
      }
      else
      {
        Arduboy2Base::drawBitmap(24, 20, Enemies::mouse2, 32, 40, WHITE);
      }
      break;
    case 3:
      if (cycle < CYCLE_HALF)
      {
        Arduboy2Base::drawBitmap(24, 20, Enemies::cub, 32, 40, WHITE);
      }
      else
      {
        Arduboy2Base::drawBitmap(24, 20, Enemies::cub2, 32, 40, WHITE);
      }
      break;
    case 4:
      if (cycle < CYCLE_HALF)
      {
        Arduboy2Base::drawBitmap(24, 20, Enemies::cat, 32, 40, WHITE);
      }
      else
      {
        Arduboy2Base::drawBitmap(24, 20, Enemies::cat2, 32, 40, WHITE);
      }
      break;
    case 5:
      if (cycle < CYCLE_HALF)
      {
        Arduboy2Base::drawBitmap(24, 20, Enemies::fox, 32, 40, WHITE);
      }
      else
      {
        Arduboy2Base::drawBitmap(24, 20, Enemies::fox2, 32, 40, WHITE);
      }
      break;
    case 6:
      if (cycle < CYCLE_HALF)
      {
        Arduboy2Base::drawBitmap(24, 20, Enemies::dog, 32, 40, WHITE);
      }
      else
      {
        Arduboy2Base::drawBitmap(24, 20, Enemies::dog2, 32, 40, WHITE);
      }
      break;
    case 7:
      if (cycle < CYCLE_HALF)
      {
        Arduboy2Base::drawBitmap(24, 20, Enemies::wolf, 32, 40, WHITE);
      }
      else
      {
        Arduboy2Base::drawBitmap(24, 20, Enemies::wolf2, 32, 40, WHITE);
      }
      break;
    case 8:
      if (cycle < CYCLE_HALF)
      {
        Arduboy2Base::drawBitmap(24, 20, Enemies::foxLegend, 32, 40, WHITE);
      }
      else
      {
        Arduboy2Base::drawBitmap(24, 20, Enemies::foxLegend2, 32, 40, WHITE);
      }
      break;
    default:
      DisplayLookingRight(cycle, 24, 28, battleAction);
      break;
    }

    if (distance == 1 && displayStar)
    {
      Arduboy2Base::drawBitmap(16, 6, Enemies::star, 10, 10, WHITE);
    }
  }

  void DisplayLookingLeft(size_t cycle, size_t screenPosition, size_t heightPosition, bool battleAction)
  {
    screenPosition = screenPosition * 12;

    Arduboy2Base::drawBitmap(screenPosition + 6, heightPosition + 19, battleAction ? Pet::eye2 : Pet::eye3, 8, 8, WHITE);

    DisplayFullBody(cycle, false, true, screenPosition, heightPosition);
  }

  void DisplayLookingRight(size_t cycle, size_t screenPosition, size_t heightPosition, bool battleAction)
  {
    screenPosition = screenPosition * 12;

    Arduboy2Base::drawBitmap(screenPosition + 18, heightPosition + 19, battleAction ? Pet::eye6 : Pet::eye4, 8, 8, WHITE);

    DisplayFullBody(cycle, true, false, screenPosition, heightPosition);
  }

  void DisplayMovingLeft(size_t cycle, size_t screenPosition, size_t heightPosition)
  {
    screenPosition = screenPosition * 12;

    Arduboy2Base::drawBitmap(screenPosition + 6, heightPosition + 18, Pet::eye, 8, 8, WHITE);

    DisplayFullBody(cycle, false, true, screenPosition, heightPosition);
  }

  void DisplayMovingRight(size_t cycle, size_t screenPosition, size_t heightPosition)
  {
    screenPosition = screenPosition * 12;

    Arduboy2Base::drawBitmap(screenPosition + 18, heightPosition + 18, Pet::eye5, 8, 8, WHITE);

    DisplayFullBody(cycle, true, false, screenPosition, heightPosition);
  }

  void DisplayIdle(size_t cycle, size_t screenPosition, size_t heightPosition)
  {
    screenPosition = screenPosition * 12;

    Arduboy2Base::drawBitmap(screenPosition + 6, heightPosition + 18, Pet::eye, 8, 8, WHITE);
    Arduboy2Base::drawBitmap(screenPosition + 18, heightPosition + 18, Pet::eye5, 8, 8, WHITE);

    DisplayFullBody(cycle, true, true, screenPosition, heightPosition);
  }

  void DisplaySick(size_t cycle, size_t screenPosition, size_t heightPosition)
  {
    screenPosition = screenPosition * 12;

    Arduboy2Base::drawBitmap(screenPosition + 6, heightPosition + 19, Pet::eye3, 8, 8, WHITE);
    Arduboy2Base::drawBitmap(screenPosition + 18, heightPosition + 19, Pet::eye6, 8, 8, WHITE);

    DisplayFullBody(cycle, true, true, screenPosition, heightPosition);
  }

private:
  void DisplayFullBody(size_t cycle, bool leftEar, bool rightEar, size_t screenPosition, size_t heightPosition)
  {
    if (cycle < CYCLE_HALF)
    {
      Arduboy2Base::drawBitmap(screenPosition, heightPosition, Pet::body, 32, 32, WHITE);
      if (leftEar)
      {
        Arduboy2Base::drawBitmap(screenPosition - 4, heightPosition + 4, Pet::leftEar, 16, 16, WHITE);
        Arduboy2Base::drawBitmap(screenPosition + 8, heightPosition + 16, Pet::hideEar, 4, 2, BLACK);
      }
      if (rightEar)
      {
        Arduboy2Base::drawBitmap(screenPosition + 20, heightPosition + 4, Pet::rightEar, 16, 16, WHITE);
        Arduboy2Base::drawBitmap(screenPosition + 20, heightPosition + 16, Pet::hideEar, 4, 2, BLACK);
      }
    }
    else
    {
      Arduboy2Base::drawBitmap(screenPosition, heightPosition, Pet::body2, 32, 32, WHITE);
      if (leftEar)
      {
        Arduboy2Base::drawBitmap(screenPosition - 4, heightPosition + 6, Pet::leftEar2, 16, 16, WHITE);
        Arduboy2Base::drawBitmap(screenPosition + 8, heightPosition + 18, Pet::hideEar, 4, 2, BLACK);
      }
      if (rightEar)
      {
        Arduboy2Base::drawBitmap(screenPosition + 20, heightPosition + 6, Pet::rightEar2, 16, 16, WHITE);
        Arduboy2Base::drawBitmap(screenPosition + 20, heightPosition + 18, Pet::hideEar, 4, 2, BLACK);
      }
    }
  }
};
