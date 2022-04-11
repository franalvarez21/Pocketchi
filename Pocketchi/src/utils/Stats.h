#pragma once

struct Stats
{
  uint8_t hp;
  uint8_t hpEnemy;
  uint8_t level;
  uint8_t distance;
  uint8_t battleBarPoints[MAX_BATTLE_POINTS];
  uint8_t arrowPosition;
  bool arrowDirection;

  void init()
  {
    hp = MAX_LIFE;
    hpEnemy = 0;
    level = 1;
    distance = MAX_MOVEMENT_STEPS;
    startBattle();
  }

  void startBattle()
  {
    if (distance > 0)
    {
      hpEnemy = level;
    }
    else
    {
      hpEnemy = MAX_LIFE;
    }

    for (uint8_t i = 0; i < MAX_BATTLE_POINTS; i++)
    {
      battleBarPoints[i] = rand() % 100 < ((level + 2) * 10) ? 0 : 1;
    }
    arrowPosition = 0;
    arrowDirection = true;
  }

  uint8_t getHP()
  {
    return hp;
  }

  uint8_t getHPEnemy()
  {
    return hpEnemy;
  }

  uint8_t getArrowPosition(bool modifyPosition)
  {
    if (modifyPosition)
    {
      if (arrowDirection)
      {
        arrowPosition++;
        if (arrowPosition == MAX_BATTLE_POINTS - 1)
        {
          arrowDirection = false;
        }
      }
      else
      {
        arrowPosition--;
        if (arrowPosition == 0)
        {
          arrowDirection = true;
        }
      }
    }
    return arrowPosition;
  }

  uint8_t getBar(uint8_t position)
  {
    return battleBarPoints[position];
  }

  void incHP(uint8_t val)
  {
    hp = min(hp + val, MAX_LIFE);
  }

  void decHP(uint8_t val)
  {
    hp = max(hp - val, 0);
  }

  void decHPEnemy(uint8_t val)
  {
    hpEnemy = max(hpEnemy - val, 0);
  }
};
