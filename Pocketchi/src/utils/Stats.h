#pragma once

struct Stats
{
private:
  size_t hp;
  size_t hpEnemy;
  size_t level;
  size_t userLevel;
  size_t distance;

  size_t arrowPosition;
  bool arrowDirection;

  size_t battleBarPoints[MAX_BATTLE_POINTS];
  size_t steps[7] = {4, 3, 4, 4, 5, 6, 4};
  size_t currentEnemyID;

public:
  void init()
  {
    hp = 2;
    hpEnemy = 0;
    level = 1;
    userLevel = level;
    distance = steps[level - 1];
    currentEnemyID = 0;
    startBattle();
  }

  void startBattle()
  {
    if (currentEnemyID > MAX_LIFE)
    {
      hpEnemy = 5;
    }
    else
    {
      hpEnemy = currentEnemyID;
    }

    refresh();
  }

  void refreshBattleBar()
  {
    bool bucleBattleBar = false;
    while (!bucleBattleBar)
    {
      size_t valid = 0;
      for (size_t i = 0; i < MAX_BATTLE_POINTS; i++)
      {
        battleBarPoints[i] = rand() % 100 < ((level + 2) * 10) ? 0 : 1;
        if (battleBarPoints[i] == 1)
        {
          valid++;
        }
      }

      if (valid > 3 || (currentEnemyID == MAX_LIFE - 1 && valid > 1) || (currentEnemyID == MAX_LIFE && valid > 2) || (currentEnemyID > MAX_LIFE))
      {
        bucleBattleBar = true;
      }
    }

    if (currentEnemyID > MAX_LIFE)
    {
      size_t position = rand() % MAX_BATTLE_POINTS;
      for (size_t i = 0; i < MAX_BATTLE_POINTS; i++)
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
    else if (currentEnemyID == 0)
    {
      currentEnemyID = (rand() % MAX_LIFE) + 2;
    }
  }

  size_t getLevel()
  {
    return userLevel;
  }

  size_t getDistance()
  {
    return distance;
  }

  size_t getHP()
  {
    return hp;
  }

  size_t getHPEnemy()
  {
    return hpEnemy;
  }

  size_t getCurrentEnemyID()
  {
    return currentEnemyID;
  }

  size_t getArrowPosition(bool modifyPosition)
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

  size_t getBar(size_t position)
  {
    return battleBarPoints[position];
  }

  void incLevel(size_t val)
  {
    level = min(level + val, MAX_LIFE);
    userLevel = min(userLevel + val, MAX_LEVEL);
  }

  void redDistance(size_t val)
  {
    distance = max(distance - val, 0);
    if (distance == 0)
    {
      refreshDistance();
      incHP(MAX_LIFE);
      incLevel(1);

      if (userLevel > MAX_LIFE)
      {
        distance = (rand() % 2 == 0) ? 3 : 4;
      }
    }
  }

  void refreshDistance()
  {
    distance = steps[level - 1];
    currentEnemyID = 0;
  }

  void incHP(size_t val)
  {
    hp = min(min(hp + val, level + 1), MAX_LIFE);
  }

  void decHP(size_t val)
  {
    hp = max(hp - val, 0);
  }

  void decHPEnemy(size_t val)
  {
    hpEnemy = max(hpEnemy - val, 0);
  }
};
