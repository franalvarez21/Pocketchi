#pragma once

#include <stdint.h>
#include <stdlib.h>

#include <Arduboy2.h>

#include "const/Common.h"
#include "const/Pet.h"
#include "const/Title.h"

struct Utils
{
  uint8_t cycle = CYCLE_MAX;

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
