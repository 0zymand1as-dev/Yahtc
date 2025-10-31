#pragma once
#ifndef HAND_H
#define HAND_H

#include <stdbool.h>
#include <stdint.h>

typedef struct Cup Cup;
typedef struct Rules Rules;

enum Hands
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
};

typedef struct ScoreSheet
{
  uint8_t* hands;
  uint16_t upper_sum;
  uint16_t lower_sum;
  uint8_t bonus;
  uint16_t yahtzee_bonus;
  uint8_t yahtzees;
} ScoreSheet;

uint8_t score_evaluate(
    const Rules* rules,
    const enum Hands selection,
    const Cup* cup,
    ScoreSheet* target);

ScoreSheet* score_init(void);

void score_close(ScoreSheet* target);

#endif // HAND_H
