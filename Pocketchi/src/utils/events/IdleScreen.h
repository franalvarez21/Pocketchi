#pragma once

class IdleScreen
{
private:
  bool moving;
  bool direction;
  uint8_t currentPosition;
  uint8_t cycleIdle;
  uint8_t cycleMoving;
  uint8_t messageCycle;

public:
  uint8_t action(Utils *utils)
  {
    if (Arduboy2Base::justPressed(RIGHT_BUTTON) || Arduboy2Base::justPressed(LEFT_BUTTON) || Arduboy2Base::justPressed(UP_BUTTON) || Arduboy2Base::justPressed(DOWN_BUTTON))
    {
      refreshMessageCycle();
    }
    if (Arduboy2Base::justPressed(B_BUTTON))
    {
      messageCycle = 0;
      return 2;
    }
    if (Arduboy2Base::justPressed(A_BUTTON))
    {
      messageCycle = 0;
      return 1;
    }
    return 0;
  }

  void refresh()
  {
    moving = false;
    direction = false;
    currentPosition = MAX_MOVEMENT_STEPS - 3;
    cycleIdle = MAX_ANIMATION_FRAMES * 2;
    cycleMoving = 0;
  }

  void refreshMessageCycle()
  {
    messageCycle = MAX_ANIMATION_FRAMES * 2;
  }

  void eventDisplay(Utils *utils, Stats *stats)
  {
    timeTick();

    if (messageCycle > 0)
    {
      messageCycle--;

      utils->texts.printLine(8, 8, "LEVEL");
      utils->texts.printValue(34, 8, stats->getLevel());

      utils->texts.printLine(75, 8, "DISTANCE");
      utils->texts.printValue(116, 8, stats->getDistance());
    }

    if (moving)
    {
      if (direction)
      {
        utils->charDraw.DisplayMovingRight(utils->cycle, currentPosition, 28);
      }
      else
      {
        utils->charDraw.DisplayMovingLeft(utils->cycle, currentPosition, 28);
      }
    }
    else
    {
      utils->charDraw.DisplayIdle(utils->cycle, currentPosition, 28);
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
};
