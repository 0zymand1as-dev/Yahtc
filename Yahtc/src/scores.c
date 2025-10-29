#include "../include/scores.h"
#include "../include/cup.h"
#include "../include/errors.h"
#include "../include/game.h"
#include <stdlib.h>

uint8_t score_evaluate(
    const Rules* rules,
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
    score +=
        cup_get_value_count(cup, selection) * selection;
    target->sum += score;
    break;

  case THREE_OF_A_KIND:
    score += cup_get_repeted(cup, 3)
                 ? cup_get_total_value(cup)
                 : 0;

  case FOUR_OF_A_KIND:
    score += cup_get_repeted(cup, 4)
                 ? cup_get_total_value(cup)
                 : 0;
    break;

  case FULL_HOUSE:
    score += cup_get_full_house(cup) ? 25 : 0;
    break;

  case SM_STRAIGHT:
    score += cup_get_straight(cup, rules->sstraight_count)
                 ? 30
                 : 0;
    break;

  case LG_STRAIGHT:
    score += cup_get_straight(cup, rules->lstraight_count)
                 ? 40
                 : 0;
    break;

  case YAHTZEE:
    score = cup_get_all_equal(cup);
    break;

  case CHANCE:
    score = cup_get_total_value(cup);
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
