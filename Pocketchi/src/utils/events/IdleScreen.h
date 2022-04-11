#pragma once

class IdleScreen
{
private:
  bool moving = false;
  bool direction = false;
  uint8_t currentPosition = MAX_MOVEMENT_STEPS - 3;
  uint8_t cycleIdle = MAX_ANIMATION_FRAMES * 2;
  uint8_t cycleMoving = 0;

public:
  uint8_t action(Utils *utils)
  {
    if (Arduboy2Base::justPressed(B_BUTTON))
    {
      return 2;
    }
    if (Arduboy2Base::justPressed(A_BUTTON))
    {
      return 1;
    }
    return 0;
  }

  void eventDisplay(Utils *utils)
  {
    uint8_t screenPosition = currentPosition * 12;
    uint8_t heightPosition = 28;

    timeTick();

    if (moving)
    {
      if (direction)
      {
        displayMovingRight(utils, currentPosition, screenPosition, heightPosition);
      }
      else
      {
        displayMovingLeft(utils, currentPosition, screenPosition, heightPosition);
      }
    }
    else
    {
      displayIdle(utils, currentPosition, screenPosition, heightPosition);
    }
  }

  void timeTick()
  {
    if (cycleIdle > 0)
    {
      cycleIdle--;
      if (cycleIdle <= 0)
      {
        moving = true;
        cycleMoving = MAX_ANIMATION_FRAMES;

        if (currentPosition == 1)
        {
          currentPosition++;
          direction = true;
        }
        else if (currentPosition == 4)
        {
          direction = rand() % 2 == 0 ? true : false;
          if (direction)
          {
            currentPosition++;
          }
          else
          {
            currentPosition--;
          }
        }
        else if (currentPosition == 7)
        {
          currentPosition--;
          direction = false;
        }
      }
    }
    else if (cycleMoving > 0)
    {
      cycleMoving--;
      if (cycleMoving <= 0)
      {
        if (currentPosition == 1 || currentPosition == 4 || currentPosition == 7)
        {
          moving = false;
          cycleIdle = MAX_ANIMATION_FRAMES * 2;
        }
        else
        {
          moving = true;
          cycleMoving = MAX_ANIMATION_FRAMES;

          if (direction)
          {
            currentPosition++;
          }
          else
          {
            currentPosition--;
          }
        }
      }
    }
  }

  void displayMovingLeft(Utils *utils, uint8_t position, uint8_t screenPosition, uint8_t heightPosition)
  {
    if (utils->cycle < CYCLE_HALF)
    {
      Arduboy2Base::drawBitmap(screenPosition, heightPosition, Pet::body, 32, 32, WHITE);
      Arduboy2Base::drawBitmap(screenPosition + 6, heightPosition + 19, Pet::eye, 8, 8, WHITE);
      Arduboy2Base::drawBitmap(screenPosition + 22, heightPosition - 4, Pet::rightEar, 16, 16, WHITE);
    }
    else
    {
      Arduboy2Base::drawBitmap(screenPosition, heightPosition, Pet::body2, 32, 32, WHITE);
      Arduboy2Base::drawBitmap(screenPosition + 6, heightPosition + 19, Pet::eye, 8, 8, WHITE);
      Arduboy2Base::drawBitmap(screenPosition + 22, heightPosition - 2, Pet::rightEar2, 16, 16, WHITE);
    }
  }

  void displayMovingRight(Utils *utils, uint8_t position, uint8_t screenPosition, uint8_t heightPosition)
  {
    if (utils->cycle < CYCLE_HALF)
    {
      Arduboy2Base::drawBitmap(screenPosition, heightPosition, Pet::body, 32, 32, WHITE);
      Arduboy2Base::drawBitmap(screenPosition + 18, heightPosition + 19, Pet::eye, 8, 8, WHITE);
      Arduboy2Base::drawBitmap(screenPosition - 6, heightPosition - 4, Pet::leftEar, 16, 16, WHITE);
    }
    else
    {
      Arduboy2Base::drawBitmap(screenPosition, heightPosition, Pet::body2, 32, 32, WHITE);
      Arduboy2Base::drawBitmap(screenPosition + 18, heightPosition + 19, Pet::eye, 8, 8, WHITE);
      Arduboy2Base::drawBitmap(screenPosition - 6, heightPosition - 2, Pet::leftEar2, 16, 16, WHITE);
    }
  }

  void displayIdle(Utils *utils, uint8_t position, uint8_t screenPosition, uint8_t heightPosition)
  {
    if (utils->cycle < CYCLE_HALF)
    {
      Arduboy2Base::drawBitmap(screenPosition, heightPosition, Pet::body, 32, 32, WHITE);
      Arduboy2Base::drawBitmap(screenPosition + 6, heightPosition + 19, Pet::eye, 8, 8, WHITE);
      Arduboy2Base::drawBitmap(screenPosition + 18, heightPosition + 19, Pet::eye, 8, 8, WHITE);
      Arduboy2Base::drawBitmap(screenPosition - 6, heightPosition - 4, Pet::leftEar, 16, 16, WHITE);
      Arduboy2Base::drawBitmap(screenPosition + 22, heightPosition - 4, Pet::rightEar, 16, 16, WHITE);
    }
    else
    {
      Arduboy2Base::drawBitmap(screenPosition, heightPosition, Pet::body2, 32, 32, WHITE);
      Arduboy2Base::drawBitmap(screenPosition + 6, heightPosition + 19, Pet::eye, 8, 8, WHITE);
      Arduboy2Base::drawBitmap(screenPosition + 18, heightPosition + 19, Pet::eye, 8, 8, WHITE);
      Arduboy2Base::drawBitmap(screenPosition - 6, heightPosition - 2, Pet::leftEar2, 16, 16, WHITE);
      Arduboy2Base::drawBitmap(screenPosition + 22, heightPosition - 2, Pet::rightEar2, 16, 16, WHITE);
    }
  }
};
