#pragma once

class TimeEventScreen
{
private:
  uint8_t actionTime = MAX_ANIMATION_FRAMES;
  bool actionFlag = false;
  bool actionType = false;

public:
  uint8_t action(Utils *utils, Stats *stats)
  {
    if (!actionFlag)
    {
      if (Arduboy2Base::justPressed(A_BUTTON))
      {
        actionTime = MAX_ANIMATION_FRAMES;
        actionType = stats->getBar(stats->getArrowPosition(false)) == 1;
        actionFlag = true;
      }
      else if (Arduboy2Base::justPressed(B_BUTTON))
      {
        actionTime = MAX_ANIMATION_FRAMES;
        actionType = stats->getBar(stats->getArrowPosition(false)) == 1;
        actionFlag = true;
      }
    }
    else if (actionTime == 0)
    {
      actionTime = MAX_ANIMATION_FRAMES;
      actionFlag = false;

      if (actionType)
      {
        return 2;
      }
      return 1;
    }
    return 0;
  }

  void eventDisplay(Utils *utils, Stats *stats)
  {
    Arduboy2Base::drawBitmap(8, 14, Common::battleBar, 112, 10, WHITE);
    Arduboy2Base::drawBitmap(7 + (stats->getArrowPosition(!actionFlag) * 8), 2, Common::arrowDown, 10, 10, WHITE);
    for (uint8_t i = 0; i < MAX_BATTLE_POINTS; i++)
    {
      if (stats->getBar(i) == 0)
      {
        Arduboy2Base::drawBitmap(8 + (i * 8), 14, Common::battleBarSlot, 8, 8, BLACK);
      }
    }

    if (actionFlag)
    {
      if (actionTime > 0)
      {
        actionTime--;
      }

      if (actionType)
      {
        Arduboy2Base::drawBitmap(49, 32, Common::actionButtonOK, 30, 30, WHITE);
        utils->texts.printLine(80, 34, "HIT");
      }
      else
      {
        Arduboy2Base::drawBitmap(49, 32, Common::actionButtonKO, 30, 30, WHITE);
        utils->texts.printLine(80, 34, "MISS");
      }
    }
    else
    {
      Arduboy2Base::drawBitmap(49, 32, Common::actionButton, 30, 30, WHITE);
      if (utils->cycle > CYCLE_HALF)
      {
        utils->texts.printLine(19, 56, "ACTION");
      }
    }
  }
};
