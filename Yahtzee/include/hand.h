#pragma once
#ifndef HAND_H
#define HAND_H

#include "./definitions.h"

typedef struct Cup Cup;

typedef enum Hand
{
  NONE,
  ACE,
  TWO,
  THREE,
  FOUR,
  FIVE,
  SIX,
  THREE_OF_A_KIND,
  FOUR_OF_A_KIND,
  FULL_HOUSE,
  SM_STRAIGHT,
  LG_STRAIGHT,
  YAHTZEE,
  CHANCE,
  HANDS_COUNT,
} Hand;

Score hand_evaluate(Hand selection, const Score* hands, const Cup* cup);

#endif // HAND_H
