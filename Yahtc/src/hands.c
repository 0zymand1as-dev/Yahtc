#include "../include/hands.h"

uint8_t hand_evaluate(
    const Hand selection,
    const uint8_t* hands,
    const Cup* cup)
{
  if (!hands || !cup)
    return -1;

  if (selection == YAHTZEE)
    return 100;

  return 10;
}
