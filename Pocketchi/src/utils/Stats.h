#pragma once

struct Stats
{
  uint8_t hp;
  uint8_t hpEnemy;
  uint8_t hurt;
  uint8_t hurtEnemy;
  uint8_t level;
  uint8_t distance;

  void init()
  {
    hp = MAX_LIFE;
    hpEnemy = 0;
    hurt = 0;
    hurtEnemy = 0;
    level = 1;
    distance = MAX_MOVEMENT_STEPS;
    startBattle();
  }

  void startBattle()
  {
    hurt = 0;
    hurtEnemy = 0;
    if (distance > 0)
    {
      hpEnemy = level;
    }
    else
    {
      hpEnemy = MAX_LIFE;
    }
  }

  void incHP(uint8_t val)
  {
    hp = min(hp + val, MAX_LIFE);
    hurt = 0;
  }

  void decHP(uint8_t val)
  {
    hp = max(hp - val, 0);
    hurt = MAX_ANIMATION_FRAMES;
  }

  void displayHub()
  {
    /*
    timeTick();

    Arduboy2Base::drawBitmap(0, pos * ELEMENT_SIZE, Common::life, ELEMENT_SIZE, ELEMENT_SIZE, WHITE);
    Arduboy2Base::drawBitmap(0, pos * ELEMENT_SIZE, Common::life, ELEMENT_SIZE, ELEMENT_SIZE, WHITE);

    if (hurt > 0 && hurt % 2 == 0)
    {
      displayHeart(hp);
    }

    if (hurtEnemy > 0 && hurtEnemy % 2 == 0)
    {
      displayHeartEnemy(hpEnemy);
    }
    */
  }

private:
  void timeTick()
  {
    if (hurt > 0)
    {
      hurt--;
    }

    if (hurtEnemy > 0)
    {
      hurtEnemy--;
    }
  }

  void displayHeart(uint8_t pos)
  {
    /*
    for (uint8_t pos = 0; pos < hp; pos++)
    {
      Arduboy2Base::drawBitmap(0, pos * ELEMENT_SIZE, Common::life, ELEMENT_SIZE, ELEMENT_SIZE, WHITE);
    }
    */
  }

  void displayHeartEnemy(uint8_t pos)
  {
    /*
    for (uint8_t pos = 0; pos < hp; pos++)
    {
      Arduboy2Base::drawBitmap(0, pos * ELEMENT_SIZE, Common::life, ELEMENT_SIZE, ELEMENT_SIZE, WHITE);
    }
    */
  }
};
