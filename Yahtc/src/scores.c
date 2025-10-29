#include "../include/scores.h"
#include "../include/cup.h"
#include "../include/errors.h"
#include <stdlib.h>

uint8_t score_evaluate(
    const enum Hands selection,
    const Cup* cup,
    ScoreSheet* target)
{
  if (!cup || !target)
    return -1;

  uint8_t score = 0;

  switch (selection)
  {
  case ACE:
  case TWO:
  case THREE:
  case FOUR:
  case FIVE:
  case SIX:
  case THREE_OF_A_KIND:
  case FOUR_OF_A_KIND:
  case FULL_HOUSE:
  case SM_STRAIGHT:
  case LG_STRAIGHT:
  case YAHTZEE:
  case CHANCE:
    target->hands[selection] = score;
    break;

  case NONE:
  case HANDS_COUNT:
    return -1;
  }

  return score;
}

ScoreSheet* score_init(void)
{
  ScoreSheet* new_score_sheet =
      (ScoreSheet*)malloc(sizeof(ScoreSheet));

  if (!new_score_sheet)
    memerr("score sheet");

  new_score_sheet->hands =
      calloc(HANDS_COUNT, sizeof(enum Hands));

  if (!new_score_sheet)
    memerr("hands in scoresheet");

  new_score_sheet->sum = 0;
  new_score_sheet->bonus = 0;
  new_score_sheet->yahtzees = 0;

  return new_score_sheet;
}

void score_close(ScoreSheet* target)
{
  free(target->hands);
  free(target);
  return;
}
