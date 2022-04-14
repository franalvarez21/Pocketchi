#pragma once

struct Texts
{
  Tinyfont tinyfont = Tinyfont(Arduboy2::sBuffer, Arduboy2::width(), Arduboy2::height());

  void printLine(size_t x, size_t y, char *line)
  {
    tinyfont.setCursor(x, y);
    tinyfont.print(line);
  }

  void printValue(size_t x, size_t y, size_t value)
  {
    tinyfont.setCursor(x, y);
    tinyfont.print(value);
  }
};
