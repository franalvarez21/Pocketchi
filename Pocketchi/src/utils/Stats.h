#pragma once

struct Stats
{
private:
  uint8_t hp;
  uint8_t hpEnemy;
  uint8_t level;
  size_t userLevel;
  uint8_t distance;

  uint8_t arrowPosition;
  bool arrowDirection;

  uint8_t battleBarPoints[MAX_BATTLE_POINTS];
  uint8_t steps[7] = {4, 6, 8, 10, 10, 12, 12};
  uint8_t currentEnemyID;

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

    if (currentEnemyID == 8)
    {
      uint8_t position = rand() % MAX_BATTLE_POINTS;
      for (uint8_t i = 0; i < MAX_BATTLE_POINTS; i++)
      {
        battleBarPoints[i] = 0;
      }
      battleBarPoints[position] = 1;
    }
  }

  void refresh()
  {
    refreshBattleBar();

    arrowPosition = 0;
    arrowDirection = true;
  }

  void refreshEnemy()
  {
    if (userLevel <= MAX_LIFE)
    {
      currentEnemyID = userLevel;
    }
    else
    {
      currentEnemyID = (rand() % (MAX_LIFE + 1)) + 1;
    }
  }

  size_t getLevel()
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

  uint8_t getCurrentEnemyID()
  {
    return currentEnemyID;
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
