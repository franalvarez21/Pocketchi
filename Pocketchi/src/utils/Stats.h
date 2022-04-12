#pragma once

struct Stats
{
private:
  uint8_t hp;
  uint8_t hpEnemy;
  uint8_t level;
  uint8_t userLevel;
  uint8_t distance;
  uint8_t arrowPosition;
  uint8_t battleBarPoints[MAX_BATTLE_POINTS];
  uint8_t steps[7] = {4, 6, 8, 10, 10, 12, 12};
  bool arrowDirection;

public:
  void init()
  {
    hp = 2;
    hpEnemy = 0;
    level = 1;
    userLevel = level;
    distance = steps[level - 1];
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

    refresh();
  }

  void refreshBattleBar()
  {
    bool bucleBattleBar = false;
    while (!bucleBattleBar)
    {
      uint8_t valid = 0;
      for (uint8_t i = 0; i < MAX_BATTLE_POINTS; i++)
      {
        battleBarPoints[i] = rand() % 100 < ((level + 2) * 10) ? 0 : 1;
        if (battleBarPoints[i] == 1)
        {
          valid++;
        }
      }
      if (valid > 2)
      {
        bucleBattleBar = true;
      }
    }
  }

  void refresh()
  {
    refreshBattleBar();

    arrowPosition = 0;
    arrowDirection = true;
  }

  uint8_t getLevel()
  {
    return userLevel;
  }

  uint8_t getDistance()
  {
    return distance;
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

  void incLevel(uint8_t val)
  {
    level = min(level + val, MAX_LIFE);
    userLevel = min(userLevel + val, MAX_LEVEL);
  }

  void redDistance(uint8_t val)
  {
    distance = max(distance - val, 0);
    if (distance == 0)
    {
      refreshDistance();
      incHP(MAX_LIFE);
      incLevel(1);
    }
  }

  void refreshDistance()
  {
    distance = steps[level - 1];
  }

  void incHP(uint8_t val)
  {
    hp = min(min(hp + val, level + 1), MAX_LIFE);
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
