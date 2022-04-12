#pragma once

#include <stdint.h>
#include <stdlib.h>

#include <Arduboy2.h>
#include <Tinyfont.h>

#include "const/Common.h"
#include "const/Pet.h"
#include "const/Title.h"
#include "helpers/CharDraw.h"
#include "helpers/UIDraw.h"
#include "helpers/Texts.h"

struct Utils
{
public:
  uint8_t cycle = CYCLE_MAX;
  CharDraw charDraw;
  UIDraw uiDraw;
  Texts texts;

  void tick()
  {
    cycle--;
    if (cycle < 1)
    {
      cycle = CYCLE_MAX;
    }
  }
};

#include "Stats.h"
