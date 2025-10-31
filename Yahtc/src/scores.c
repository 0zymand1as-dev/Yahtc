#include "../include/scores.h"
#include "../include/cup.h"
#include "../include/errors.h"
#include "../include/game.h"
#include <stdint.h>
#include <stdlib.h>

uint8_t score_evaluate(
    const Rules* rules,
    const enum Hands selection,
    const Cup* cup,
    ScoreSheet* target)
{
  if (!cup || !target ||
      target->hands[selection] != UINT8_MAX)
    return UINT8_MAX;

  uint8_t score = 0;
  bool yahtzee = cup_get_all_equal(cup);
  bool joker_active = false;

  if (yahtzee &&
      selection != YAHTZEE) // Got a yahtzee but didn't
                            // select yahtzee
  {
    if (target->hands[YAHTZEE] ==
        50) // If already got a yahtzee, get a yahtzee bonus
    {
      target->yahtzee_bonus += rules->extra_yahtzee_bonus;
      joker_active = true;
    }
    else if (target->hands[YAHTZEE] == 0) // If haven got a
                                          // yahtzee, joker
                                          // is active
    {
      joker_active = true;
    }

    if (joker_active)
    {
      uint8_t die_value = cup->dices[0].value;

      // When joker is active, player must fill upper
      // section first (this is mandatory)
      if (die_value >= ACE && die_value <= SIX &&
          target->hands[die_value] == UINT8_MAX)
      {
        // if have joker but didn't select upper section:
        // nuh uh
        if (selection != die_value)
        {
          return UINT8_MAX;
        }
      }
    }
  }

  switch (selection)
  {
  case ACE:
  case TWO:
  case THREE:
  case FOUR:
  case FIVE:
  case SIX:
  {
    score = cup_get_value_count(cup, selection) * selection;
    target->hands[selection] = score;
    target->upper_sum += score;

    if (target->bonus == 0 &&
        target->upper_sum >= rules->upper_bonus_req)
    {
      target->bonus = rules->upper_bonus_amo;
    }
    break;
  }
  case THREE_OF_A_KIND:
  {
    score = (cup_get_repeted(cup, 3) || joker_active)
                ? cup_get_total_value(cup)
                : 0;
    target->hands[selection] = score;
    target->lower_sum += score;
    break;
  }
  case FOUR_OF_A_KIND:
  {
    score = (cup_get_repeted(cup, 4) || joker_active)
                ? cup_get_total_value(cup)
                : 0;
    target->hands[selection] = score;
    target->lower_sum += score;
    break;
  }
  case FULL_HOUSE:
  {
    score =
        (cup_get_full_house(cup) || joker_active) ? 25 : 0;
    target->hands[selection] = score;
    target->lower_sum += score;
    break;
  }
  case SM_STRAIGHT:
  {
    score =
        (cup_get_straight(cup, rules->sstraight_count) ||
         joker_active)
            ? 30
            : 0;
    target->hands[selection] = score;
    target->lower_sum += score;
    break;
  }
  case LG_STRAIGHT:
  {
    score =
        (cup_get_straight(cup, rules->lstraight_count) ||
         joker_active)
            ? 40
            : 0;
    target->hands[selection] = score;
    target->lower_sum += score;
    break;
  }
  case YAHTZEE:
  {
    if (yahtzee)
    {
      score = 50;
      target->yahtzees++;
    }
    target->hands[selection] = score;
    target->lower_sum += score;
    break;
  }
  case CHANCE:
  {
    score = cup_get_total_value(cup);
    target->hands[selection] = score;
    target->lower_sum += score;
    break;
  }
  case NONE:
  case HANDS_COUNT:
  default:
  {
    return UINT8_MAX;
  }
  }

  return score;
}

ScoreSheet* score_init(void)
{
  ScoreSheet* new_score_sheet =
      (ScoreSheet*)calloc(1, sizeof(ScoreSheet));

  if (!new_score_sheet)
    memerr("score sheet");

  new_score_sheet->hands =
      (uint8_t*)malloc(sizeof(uint8_t) * HANDS_COUNT);

  if (!new_score_sheet->hands)
    memerr("hands for score sheet");

  for (uint8_t i = 0; i < HANDS_COUNT; i++)
  {
    new_score_sheet->hands[i] = UINT8_MAX; // 255 I think
  }

  return new_score_sheet;
}

void score_close(ScoreSheet* target)
{
  free(target->hands);
  free(target);
  return;
}
