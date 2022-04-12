#pragma once

struct Texts
{
  Tinyfont tinyfont = Tinyfont(Arduboy2::sBuffer, Arduboy2::width(), Arduboy2::height());

  void printLine(uint8_t x, uint8_t y, char *line)
  {
    tinyfont.setCursor(x, y);
    tinyfont.print(line);
  }

  void printValue(uint8_t x, uint8_t y, size_t value)
  {
    tinyfont.setCursor(x, y);
    tinyfont.print(value);
  }
};
