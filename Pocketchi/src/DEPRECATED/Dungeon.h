
#include "Cutscene.h"

class Dungeon
{
public:
  size_t level;
  size_t lastCutscene;
  Cutscene cutscene;

protected:
  uint8_t map[SQUARE_AMOUNT_WEIGHT][SQUARE_AMOUNT_HEIGHT];
  uint8_t playerXPosition;
  uint8_t playerYPosition;
  uint8_t switchOffAmount;
  uint8_t movementOrientation;
  bool hasMove;

  uint8_t (*mapPointer[52])[CHALLENGE_MAP_X][CHALLENGE_MAP_Y] = {
      &Maps::map_0,
      &Maps::map_1,
      &Maps::map_2,
      &Maps::map_3,
      &Maps::map_4,
      &Maps::map_5,
      &Maps::map_6,
      &Maps::map_7,
      &Maps::map_8,
      &Maps::map_9,
      &Maps::map_10,
      &Maps::map_11,
      &Maps::map_12,
      &Maps::map_13,
      &Maps::map_14,
      &Maps::map_15,
      &Maps::map_16,
      &Maps::map_17,
      &Maps::map_18,
      &Maps::map_19,
      &Maps::map_20,
      &Maps::map_21,
      &Maps::map_22,
      &Maps::map_23,
      &Maps::map_24,
      &Maps::map_25,
      &Maps::map_26,
      &Maps::map_27,
      &Maps::map_28,
      &Maps::map_29,
      &Maps::map_30,
      &Maps::map_31,
      &Maps::map_32,
      &Maps::map_33,
      &Maps::map_34,
      &Maps::map_35,
      &Maps::map_36,
      &Maps::map_37,
      &Maps::map_38,
      &Maps::map_39,
      &Maps::map_40,
      &Maps::map_41,
      &Maps::map_42,
      &Maps::map_43,
      &Maps::map_44,
      &Maps::map_45,
      &Maps::map_46,
      &Maps::map_47,
      &Maps::map_48,
      &Maps::map_49,
      &Maps::map_50,
      &Maps::map_51,
  };

public:
  void refresh(Stats *stats, uint8_t mode)
  {
    timer = 0;
    level = 0;
    lastCutscene = 0;
    hasMove = false;
    reset(stats, mode);
  }

  void cutsceneStart(bool start)
  {
    cutscene.start(start);
    lastCutscene = level;
  }

  bool canContinue()
  {
    return switchOffAmount == 0;
  }

  bool hasMoved()
  {
    return hasMove;
  }

  bool cutsceneDone()
  {
    return lastCutscene == level;
  }

  uint8_t movePlayer(Utils *utils, Stats *stats)
  {
    uint8_t value = 0;

    if (pressed(RIGHT_BUTTON))
    {
      movementOrientation = 0;
      value = move(1, 0);
    }

    if (pressed(LEFT_BUTTON))
    {
      movementOrientation = 1;
      value = move(-1, 0);
    }

    if (pressed(DOWN_BUTTON))
    {
      movementOrientation = 2;
      value = move(0, 1);
    }

    if (pressed(UP_BUTTON))
    {
      movementOrientation = 3;
      value = move(0, -1);
    }

    return value;
  }

  bool moveLeft()
  {
    if (playerXPosition - 1 > 1)
    {
      if (map[playerXPosition - 1][playerYPosition] == 0)
      {
        playerXPosition--;
        return true;
      }
    }
    return false;
  }

  bool moveRight()
  {
    if (playerXPosition + 1 < SQUARE_AMOUNT_WEIGHT - 2)
    {
      if (map[playerXPosition + 1][playerYPosition] == 0)
      {
        playerXPosition++;
        return true;
      }
    }
    return false;
  }

  bool moveTop()
  {
    if (playerYPosition - 1 > 0)
    {
      if (map[playerXPosition][playerYPosition - 1] == 0)
      {
        playerYPosition--;
        return true;
      }
    }
    return false;
  }

  bool moveDown()
  {
    if (playerYPosition + 1 < SQUARE_AMOUNT_HEIGHT - 2)
    {
      if (map[playerXPosition][playerYPosition + 1] == 0)
      {
        playerYPosition++;
        return true;
      }
    }
    return false;
  }

  uint8_t moveWalker()
  {
    uint8_t can_continue = 10;
    uint8_t move = 0;

    while (move == 0 && can_continue > 0)
    {
      switch (rand() % 4)
      {
      case 0:
        if (moveTop())
        {
          move = 1;
        }
        break;
      case 1:
        if (moveRight())
        {
          move = 2;
        }
        break;
      case 2:
        if (moveDown())
        {
          move = 3;
        }
        break;
      case 3:
        if (moveLeft())
        {
          move = 4;
        }
        break;
      }
      can_continue--;
    }
    return move;
  }

  void increaseLevel()
  {
    level++;
  }

  void reset(Stats *stats, uint8_t mode)
  {
    clearMap();
    hasMove = false;
    uint8_t cell[CHALLENGE_MAP_X][CHALLENGE_MAP_Y];

    if (mode == 0)
    {
      restorePlayerPosition();
      map[playerXPosition][playerYPosition] = 3;
      walkerCircle();
      unfairMap(stats);
      unblockPathMap();
      fragilePathMap();

      if (switchOffAmount < 3)
      {
        reset(stats, 0);
      }
    }
    else if (mode == 1)
    {
      switchOffAmount = 0;
      memcpy_P(&cell, mapPointer[level], sizeof(cell));
    }
    else
    {
      switchOffAmount = 0;
      memcpy_P(&cell, mapPointer[level + MAX_CHALLENGE_LEVEL], sizeof(cell));
    }

    if (mode > 0)
    {
      for (uint8_t i = 0; i < CHALLENGE_MAP_X; i++)
      {
        for (uint8_t j = 0; j < CHALLENGE_MAP_Y; j++)
        {
          map[i + 2][j + 1] = cell[i][j];
          switch (cell[i][j])
          {
          case 10:
            playerXPosition = i + 2;
            playerYPosition = j + 1;
            map[i + 2][j + 1] = 2;
            break;
          case 11:
            playerXPosition = i + 2;
            playerYPosition = j + 1;
            map[i + 2][j + 1] = 9;
            break;
          case 7:
            switchOffAmount++;
            break;
          }
        }
      }
    }
  }

  void displayLevel(Numbers *numbers)
  {
    numbers->print(26, 5, min(level, MAX_LEVEL));
    Arduboy2Base::drawBitmap(36, 5, Digits::back, 10, 10, BLACK);
    Arduboy2Base::drawBitmap(18, 5, Lines::hubLevel, 24, 5, WHITE);
  }

  void borders(uint8_t weight = MAX_SQUARE_AMOUNT_WEIGHT, uint8_t height = MAX_SQUARE_AMOUNT_HEIGHT)
  {
    for (uint8_t y = 0; y < height - 1; y++)
    {
      Arduboy2Base::drawFastVLine(ELEMENT_SIZE + 1, y * ELEMENT_SIZE, ELEMENT_SIZE, WHITE);
      Arduboy2Base::drawFastVLine(ELEMENT_SIZE + 2, y * ELEMENT_SIZE, ELEMENT_SIZE, WHITE);
      Arduboy2Base::drawFastVLine(ELEMENT_SIZE + 3, y * ELEMENT_SIZE, ELEMENT_SIZE, WHITE);
    }
  }

  void display(uint8_t cycle, uint8_t mode)
  {
    uint8_t camX = (playerXPosition < 5) ? 1 : playerXPosition - 4;
    uint8_t camY = (playerYPosition < 3) ? 1 : playerYPosition - 2;
    camX = (playerXPosition > 12) ? 9 : camX;

    for (uint8_t x = camX, i = 1; i < 8 && x < SQUARE_AMOUNT_WEIGHT - 1; x++, i++)
    {
      for (uint8_t y = camY - 1, j = 0; j < 7 && y < SQUARE_AMOUNT_HEIGHT - 1; y++, j++)
      {
        displayElements(mode, x, y, i, j, cycle);
        if (x == playerXPosition && y == playerYPosition)
        {
          if (hasMove)
          {
            Arduboy2Base::drawBitmap(SQUARE_SIZE * i - 2, SQUARE_SIZE * j - 6 - SQUARE_SIZE, Common::player_1, SQUARE_SIZE, SQUARE_SIZE, BLACK);
            Arduboy2Base::drawBitmap(SQUARE_SIZE * i - 2, SQUARE_SIZE * j - 6 - SQUARE_SIZE, Common::player_2, SQUARE_SIZE, SQUARE_SIZE, WHITE);
            hasMove = false;
          }
          else
          {
            Arduboy2Base::drawBitmap(SQUARE_SIZE * i - 2, SQUARE_SIZE * j - 2 - SQUARE_SIZE, Common::player_1, SQUARE_SIZE, SQUARE_SIZE, BLACK);
            Arduboy2Base::drawBitmap(SQUARE_SIZE * i - 2, SQUARE_SIZE * j - 2 - SQUARE_SIZE, Common::player_2, SQUARE_SIZE, SQUARE_SIZE, WHITE);
          }
        }
      }
    }
  }

  void displayGameOver(Stats *stats, Numbers *numbers)
  {
    Arduboy2Base::drawBitmap(25, 24, Lines::gameover, 78, 8, WHITE);
    numbers->print(25, 36, stats->getScore());
    Arduboy2Base::drawBitmap(79, 36, Lines::hubScore, 24, 5, WHITE);
  }

  void displayEnding(Stats *stats, Numbers *numbers)
  {
    Arduboy2Base::drawBitmap(0, 0, Title::title_ending, 128, 36, WHITE);
    numbers->print(25, 40, stats->getScore());
    Arduboy2Base::drawBitmap(79, 40, Lines::hubScore, 24, 5, WHITE);
  }

  void displayLevelStart(Utils *utils, Effects *effects)
  {
    timer = (timer == 0) ? 10 : timer - 1;

    switch (timer)
    {
    case 1:
      Arduboy2Base::drawBitmap(10, 25, Common::hourglass_0, 48, 39, WHITE);
      break;
    case 2:
      Arduboy2Base::drawBitmap(10, 25, Common::hourglass_3, 48, 39, WHITE);
      break;
    case 3:
      Arduboy2Base::drawBitmap(10, 25, Common::hourglass_2, 48, 39, WHITE);
      break;
    case 4:
      Arduboy2Base::drawBitmap(10, 25, Common::hourglass_1, 48, 39, WHITE);
      break;
    default:
      Arduboy2Base::drawBitmap(10, 25, Common::hourglass_0, 48, 39, WHITE);
      break;
    }

    Arduboy2Base::drawBitmap(90, 0, Title::title_border, 38, 38, WHITE);
  }

private:
  bool pressed(uint8_t button)
  {
    if (Arduboy2Base::justPressed(button))
    {
      return true;
    }
    return false;
  }

  void clearMap()
  {
    for (uint8_t i = 0; i < SQUARE_AMOUNT_WEIGHT; i++)
    {
      for (uint8_t j = 0; j < SQUARE_AMOUNT_HEIGHT; j++)
      {
        map[i][j] = 0;
      }
    }
  }

  void refreshMap()
  {
    for (uint8_t i = 0; i < SQUARE_AMOUNT_WEIGHT; i++)
    {
      for (uint8_t j = 0; j < SQUARE_AMOUNT_HEIGHT; j++)
      {
        if (map[i][j] == 1)
        {
          map[i][j] = 3;
        }
      }
    }
  }

  void unfairMap(Stats *stats)
  {
    if (stats->getHP() > 5)
    {
      for (uint8_t i = 0; i < SQUARE_AMOUNT_WEIGHT; i++)
      {
        for (uint8_t j = 0; j < SQUARE_AMOUNT_HEIGHT; j++)
        {
          if (map[i][j] == 4)
          {
            map[i][j] = 6;
          }
        }
      }
    }
  }

  void unblockPathMap()
  {
    for (uint8_t i = 1; i < SQUARE_AMOUNT_WEIGHT - 1; i++)
    {
      for (uint8_t j = 1; j < SQUARE_AMOUNT_HEIGHT - 1; j++)
      {
        uint8_t amount = 0;
        if (map[i - 1][j] == 0)
        {
          amount++;
        }
        if (map[i + 1][j] == 0)
        {
          amount++;
        }
        if (map[i][j - 1] == 0)
        {
          amount++;
        }
        if (map[i][j + 1] == 0)
        {
          amount++;
        }

        if (map[i][j] == 7 && amount == 2)
        {
          if (map[i - 1][j] == 0 && i > 2)
          {
            map[i - 1][j] = 2;
          }
          else if (map[i][j - 1] == 0 && j > 1)
          {
            map[i][j - 1] = 2;
          }
          else if (map[i + 1][j] == 0 && i < SQUARE_AMOUNT_WEIGHT - 3)
          {
            map[i + 1][j] = 2;
          }
          else if (map[i][j + 1] == 0 && j < SQUARE_AMOUNT_HEIGHT - 3)
          {
            map[i][j + 1] = 2;
          }
        }
      }
    }
  }

  void fragilePathMap()
  {
    for (uint8_t i = 1; i < SQUARE_AMOUNT_WEIGHT - 1; i++)
    {
      for (uint8_t j = 1; j < SQUARE_AMOUNT_HEIGHT - 1; j++)
      {
        if (map[i][j] == 3)
        {
          uint8_t amount = 0;
          if (map[i - 1][j] != 0)
          {
            amount++;
          }
          if (map[i + 1][j] != 0)
          {
            amount++;
          }
          if (map[i][j - 1] != 0)
          {
            amount++;
          }
          if (map[i][j + 1] != 0)
          {
            amount++;
          }

          if (amount == 3)
          {
            map[i][j] = 2;
          }
        }
      }
    }
  }

  uint8_t getWalkerCiclesByLevel()
  {
    switch (level)
    {
    case 0 ... 20:
      return 10;
    case 21 ... 40:
      return 15;
    case 41 ... 60:
      return 20;
    case 61 ... 80:
      return 25;
    case 81 ... 100:
      return 30;
    case 101 ... 200:
      return 35;
    case 201 ... 300:
      return 40;
    case 301 ... 400:
      return 45;
    case 401 ... 500:
      return 50;
    case 501 ... 600:
      return 55;
    case 601 ... 700:
      return 60;
    case 701 ... 800:
      return 65;
    case 801 ... 900:
      return 70;
    default:
      return 75;
    }
  }

  uint8_t getMaxAmountsByLevel()
  {
    switch (level)
    {
    case 0 ... 20:
      return 3;
    case 21 ... 40:
      return 5;
    case 41 ... 60:
      return 7;
    case 61 ... 80:
      return 10;
    case 81 ... 100:
      return 13;
    case 101 ... 200:
      return 16;
    default:
      return 19;
    }
  }

  void walkerCircle()
  {
    for (uint8_t i = 0; i < getWalkerCiclesByLevel(); i++)
    {
      if (i % 10 == 0)
      {
        restorePlayerPosition();
      }

      bool trap = false;
      switch (moveWalker())
      {
      case 1: // Top
        if (playerYPosition > 1 && map[playerXPosition][playerYPosition - 1] == 3)
        {
          trap = true;
        }
        break;
      case 2: // Right
        if (playerXPosition < SQUARE_AMOUNT_WEIGHT - 2 && map[playerXPosition + 1][playerYPosition] == 3)
        {
          trap = true;
        }
        break;
      case 3: // Bottom
        if (playerYPosition < SQUARE_AMOUNT_HEIGHT - 2 && map[playerXPosition][playerYPosition + 1] == 3)
        {
          trap = true;
        }
        break;
      case 4: // Left
        if (playerXPosition > 1 && map[playerXPosition - 1][playerYPosition] == 3)
        {
          trap = true;
        }
        break;
      }

      if (!trap)
      {
        map[playerXPosition][playerYPosition] = 3;
      }
      else
      {
        map[playerXPosition][playerYPosition] = 6;
      }
    }

    spawnObjects();
    restorePlayerPosition();
    if (map[playerXPosition][playerYPosition] != 3)
    {
      if (map[playerXPosition][playerYPosition] == 7)
      {
        switchOffAmount--;
      }
    }
    map[playerXPosition][playerYPosition] = 3;
  }

  void restorePlayerPosition()
  {
    playerXPosition = 6;
    playerYPosition = 3;
  }

  void spawnObjects()
  {
    if (level < MAX_LEVEL)
    {
      switchOffAmount = 0;
      for (uint8_t i = 0; i < (1 + rand() % getMaxAmountsByLevel()); i++)
      {
        if (rand() % 2 == 0)
        {
          spawnObject(6);
        }
        else
        {
          spawnObject(4 + (rand() % 2));
        }
      }

      for (uint8_t i = 0; i < getMaxAmountsByLevel(); i++)
      {
        if (spawnObject(7))
        {
          switchOffAmount++;
        }
      }
    }
  }

  bool spawnObject(uint8_t item)
  {
    switch (rand() % 4)
    {
    case 0:
      for (uint8_t i = 1; i < SQUARE_AMOUNT_WEIGHT - 1; i++)
      {
        for (uint8_t j = 1; j < SQUARE_AMOUNT_HEIGHT - 1; j++)
        {
          if (canSetItem(i, j))
          {
            map[i][j] = item;
            return true;
          }
        }
      }
      break;
    case 1:
      for (uint8_t i = 1; i < SQUARE_AMOUNT_WEIGHT - 1; i++)
      {
        for (uint8_t j = SQUARE_AMOUNT_HEIGHT - 2; j > 0; j--)
        {
          if (canSetItem(i, j))
          {
            map[i][j] = item;
            return true;
          }
        }
      }
      break;
    case 2:
      for (uint8_t i = SQUARE_AMOUNT_WEIGHT - 2; i > 0; i--)
      {
        for (uint8_t j = SQUARE_AMOUNT_HEIGHT - 2; j > 0; j--)
        {
          if (canSetItem(i, j))
          {
            map[i][j] = item;
            return true;
          }
        }
      }
      break;
    case 3:
      for (uint8_t i = SQUARE_AMOUNT_WEIGHT - 2; i > 0; i--)
      {
        for (uint8_t j = 0; j < SQUARE_AMOUNT_HEIGHT - 1; j++)
        {
          if (canSetItem(i, j))
          {
            map[i][j] = item;
            return true;
          }
        }
      }
      break;
    }

    return false;
  }

  bool canSetItem(uint8_t i, uint8_t j)
  {
    return (map[i][j] == 3 && map[i - 1][j] < 4 && map[i][j - 1] < 4 && map[i + 1][j] < 4 && map[i][j + 1] < 4);
  }

  void displayElements(uint8_t mode, uint8_t x, uint8_t y, uint8_t i, uint8_t j, uint8_t cycle)
  {
    switch (map[x][y])
    {
    case 1:
      Arduboy2Base::drawBitmap(SQUARE_SIZE * i - 2, SQUARE_SIZE * j - SQUARE_SIZE, Common::empty_position, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      break;
    case 2:
      Arduboy2Base::drawBitmap(SQUARE_SIZE * i - 2, SQUARE_SIZE * j - SQUARE_SIZE, Common::half_position, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      break;
    case 3:
      Arduboy2Base::drawBitmap(SQUARE_SIZE * i - 2, SQUARE_SIZE * j - SQUARE_SIZE, Common::full_position, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      break;
    case 4:
      Arduboy2Base::drawBitmap(SQUARE_SIZE * i - 2, SQUARE_SIZE * j - SQUARE_SIZE, Common::heal_position, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      break;
    case 5:
      Arduboy2Base::drawBitmap(SQUARE_SIZE * i - 2, SQUARE_SIZE * j - SQUARE_SIZE, (cycle <= 5) ? Common::refresh_position : Common::refresh_position_2, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      break;
    case 6:
      Arduboy2Base::drawBitmap(SQUARE_SIZE * i - 2, SQUARE_SIZE * j - SQUARE_SIZE, (cycle <= 5) ? Common::spike_position : Common::spike_position_2, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      break;
    case 7:
      if (mode == 1)
      {
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i - 2, SQUARE_SIZE * j - SQUARE_SIZE, (switchOffAmount == 1) ? Common::flag_position : Common::goal_position, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
      else
      {
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i - 2, SQUARE_SIZE * j - SQUARE_SIZE, (switchOffAmount == 1) ? Common::crown_position : Common::goal_position, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
      break;
    case 8:
      Arduboy2Base::drawBitmap(SQUARE_SIZE * i - 2, SQUARE_SIZE * j - SQUARE_SIZE, Common::goal_position_2, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      break;
    case 9:
      Arduboy2Base::drawBitmap(SQUARE_SIZE * i - 2, SQUARE_SIZE * j - SQUARE_SIZE, Common::hard_position, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      break;
    }
  }

  uint8_t move(const int extX, const int extY)
  {
    uint8_t value = map[playerXPosition + extX][playerYPosition + extY];
    if (value > 0)
    {
      hasMove = true;

      if (map[playerXPosition][playerYPosition] == 3)
      {
        map[playerXPosition][playerYPosition] = 2;
      }
      else if (map[playerXPosition][playerYPosition] == 2)
      {
        map[playerXPosition][playerYPosition] = 1;
      }

      playerXPosition += extX;
      playerYPosition += extY;

      if (map[playerXPosition][playerYPosition] == 1)
      {
        return 1;
      }
      else if (map[playerXPosition][playerYPosition] == 4)
      {
        map[playerXPosition][playerYPosition] = 3;
        return 2;
      }
      else if (map[playerXPosition][playerYPosition] == 5)
      {
        refreshMap();
        return 3;
      }
      else if (map[playerXPosition][playerYPosition] == 6)
      {
        return 4;
      }
      else if (map[playerXPosition][playerYPosition] == 7)
      {
        switchOffAmount--;
        map[playerXPosition][playerYPosition] = 8;
        return 5;
      }
      else if (map[playerXPosition][playerYPosition] == 8)
      {
        switchOffAmount++;
        map[playerXPosition][playerYPosition] = 7;
        return 6;
      }
    }
    return 0;
  }

private:
  uint8_t timer;
};
