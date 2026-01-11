#pragma once
#ifndef HAND_H
#define HAND_H

#include <stdbool.h>
#include <stdint.h>

typedef struct Cup Cup;
typedef struct Rules Rules;

/**
 * @brief Represents the different possible hands or scoring
 * categories in Yahtzee.
 */
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

/**
 * @brief Represents a player's score sheet, tracking scores
 * for each hand category.
 * @field hands An array storing the score for each hand
 * category. UINT8_MAX indicates an unplayed hand.
 * @field upper_sum The total score for the upper section
 * (Aces through Sixes).
 * @field lower_sum The total score for the lower section
 * (Three of a Kind through Chance).
 * @field bonus The bonus awarded for achieving a certain
 * score in the upper section.
 * @field yahtzee_bonus Additional points for subsequent
 * Yahtzees after the first.
 * @field yahtzees The count of Yahtzees scored.
 */
typedef struct ScoreSheet
{
  uint8_t hands[HANDS_COUNT];
  uint16_t upper_sum;
  uint16_t lower_sum;
  uint8_t bonus;
  uint16_t yahtzee_bonus;
  uint8_t yahtzees;
} ScoreSheet;

/**
 * @brief Evaluates the score for a selected hand based on
 * the current dice in the cup and updates the score sheet.
 * @param rules A pointer to the game rules, used for
 * scoring values and bonuses.
 * @param selection The hand category to evaluate (e.g.,
 * ACE, THREE_OF_A_KIND, YAHTZEE).
 * @param cup A pointer to the Cup structure containing the
 * current dice values.
 * @param target A pointer to the ScoreSheet to update with
 * the calculated score.
 * @return The score obtained for the selected hand, or
 * UINT8_MAX if the selection is invalid or already played.
 */
uint8_t score_evaluate(
    const Rules* rules,
    const enum Hands selection,
    const Cup* cup,
    ScoreSheet* target);

/**
 * @brief Initializes a new ScoreSheet structure, setting
 * all hand scores to unplayed (UINT8_MAX) and sums to zero.
 * @return A pointer to the newly initialized ScoreSheet
 * structure.
 */
ScoreSheet* score_init(void);

/**
 * @brief Frees the memory allocated for a ScoreSheet
 * structure.
 * @param target A pointer to the ScoreSheet structure to
 * close.
 */
void score_close(ScoreSheet* target);

#endif // HAND_H
