#pragma once

class IdleScreen
{
private:
  bool moving;
  bool direction;
  bool canSave;
  size_t currentPosition;
  size_t cycleIdle;
  size_t cycleMoving;
  size_t messageCycle;
  size_t saveMessageCycle;

public:
  size_t action(Utils *utils)
  {
    if (Arduboy2Base::justPressed(RIGHT_BUTTON) || Arduboy2Base::justPressed(LEFT_BUTTON) || Arduboy2Base::justPressed(UP_BUTTON) || Arduboy2Base::justPressed(DOWN_BUTTON))
    {
      if (messageCycle > 0 && canSave)
      {
        refreshSaveMessageCycle();
        canSave = false;
        refreshMessageCycle();
        return 3;
      }
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
    saveMessageCycle = 0;
    canSave = true;
  }

  void refreshMessageCycle()
  {
    messageCycle = MAX_ANIMATION_FRAMES * 2;
  }

  void refreshSaveMessageCycle()
  {
    saveMessageCycle = MAX_ANIMATION_FRAMES * 2;
  }

  void eventDisplay(Utils *utils, Stats *stats)
  {
    timeTick();

    if (messageCycle > 0)
    {
      messageCycle--;

      utils->texts.printLine(0, 2, "LEVEL");
      utils->texts.printValue(26, 2, stats->getLevel());

      utils->texts.printLine(0, 7, "DISTANCE");
      utils->texts.printValue(41, 7, stats->getDistance());

      utils->texts.printLine(0, 12, "LIFE");
      utils->texts.printValue(21, 12, stats->getHP());

      if (saveMessageCycle == 0 && canSave)
      {
        Arduboy2Base::drawBitmap(83, 2, Common::arrowsOption, 9, 9, WHITE);
        utils->texts.printLine(94, 2, "PRESS");
        utils->texts.printLine(94, 7, "TO SAVE");
      }
      else if (saveMessageCycle == 0 && !canSave)
      {
        Arduboy2Base::drawBitmap(119, 2, Common::miniOption, 6, 6, WHITE);
        Arduboy2Base::drawBitmap(114, 7, Common::miniOption, 6, 6, WHITE);
        utils->texts.printLine(89, 2, "ACTION");
        utils->texts.printLine(94, 7, "FOOD");
      }
    }
    else
    {
      Arduboy2Base::drawBitmap(0, 2, Common::arrowsOption, 9, 9, WHITE);
      utils->texts.printLine(11, 2, "INFO");
      if (saveMessageCycle == 0)
      {
        Arduboy2Base::drawBitmap(119, 2, Common::miniOption, 6, 6, WHITE);
        Arduboy2Base::drawBitmap(114, 7, Common::miniOption, 6, 6, WHITE);
        utils->texts.printLine(89, 2, "ACTION");
        utils->texts.printLine(94, 7, "FOOD");
      }
    }

    if (saveMessageCycle > 0)
    {
      saveMessageCycle--;

      utils->texts.printLine(75, 2, "GAME SAVED!");
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
