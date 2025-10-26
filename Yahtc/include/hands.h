#pragma once
#ifndef HAND_H
#define HAND_H

#include <stdint.h>

typedef struct Cup Cup;

typedef enum Hands
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

typedef struct ScoreSheet 
{
  Hands* hands;
  uint8_t sum;
  uint8_t bonus;
  uint8_t yahtzees;
} ScoreSheet;

uint8_t hand_evaluate(
    const Hand selection,
    const uint8_t* hands,
    const Cup* cup);

#endif // HAND_H
