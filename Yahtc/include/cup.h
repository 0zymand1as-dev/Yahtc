#pragma once
#ifndef DICE_H
#define DICE_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/**
 * @brief Represents a single dice.
 * @field value The current face value of the dice.
 * @field locked A boolean indicating if the dice is locked
 * (true) or can be re-rolled (false).
 */
typedef struct Dice
{
  uint8_t value;
  bool locked;
} Dice;

/**
 * @brief Represents a cup containing multiple dice.
 * @field dices A pointer to an array of Dice structures.
 * @field count The number of dice in the cup.
 * @field faces The number of faces on each dice (e.g., 6
 * for a standard die).
 */
typedef struct Cup
{
  Dice* dices;
  size_t count;
  uint8_t faces; // This never can be zero
} Cup;

/**
 * @brief Checks if all dice in the cup have the same value.
 * @param target A pointer to the Cup structure.
 * @return True if all dice have the same value, false
 * otherwise.
 */
bool cup_get_all_equal(const Cup* target);

/**
 * @brief Checks if any dice value is repeated a specified
 * number of times.
 * @param target A pointer to the Cup structure.
 * @param times The minimum number of repetitions to check
 * for.
 * @return True if a value is repeated 'times' or more,
 * false otherwise.
 */
bool cup_get_repeted(const Cup* target, size_t times);

/**
 * @brief Calculates the sum of the values of all dice in
 * the cup.
 * @param target A pointer to the Cup structure.
 * @return The total sum of the dice values.
 */
uint16_t cup_get_total_value(const Cup* target);

/**
 * @brief Counts the occurrences of a specific dice value in
 * the cup.
 * @param target A pointer to the Cup structure.
 * @param dice_number The dice value to count.
 * @return The number of times 'dice_number' appears in the
 * cup.
 */
size_t
cup_get_value_count(const Cup* target, uint8_t dice_number);

/**
 * @brief Checks if the cup contains a straight of a
 * specified length.
 * @param target A pointer to the Cup structure.
 * @param s_count The required length of the straight.
 * @return True if a straight of 's_count' is found, false
 * otherwise.
 */
bool cup_get_straight(const Cup* target, size_t s_count);

/**
 * @brief Checks if the cup contains a full house (three of
 * a kind and a pair).
 * @param target A pointer to the Cup structure.
 * @return True if a full house is found, false otherwise.
 */
bool cup_get_full_house(const Cup* target);

/**
 * @brief Re-rolls all unlocked dice in the cup.
 * @param target A pointer to the Cup structure.
 */
void cup_throw(Cup* target);

/**
 * @brief Locks a specific dice in the cup by its index.
 * @param target A pointer to the Cup structure.
 * @param dice_i The index of the dice to lock.
 */
void cup_lock(Cup* target, size_t dice_i);

/**
 * @brief Locks all dice in the cup.
 * @param target A pointer to the Cup structure.
 */
void cup_lock_all(Cup* target);

/**
 * @brief Unlocks a specific dice in the cup by its index.
 * @param target A pointer to the Cup structure.
 * @param dice_i The index of the dice to unlock.
 */
void cup_unlock(Cup* target, size_t dice_i);

/**
 * @brief Unlocks all dice in the cup.
 * @param target A pointer to the Cup structure.
 */
void cup_unlock_all(Cup* target);

/**
 * @brief Toggles the lock status of a specific dice in the
 * cup.
 * @param target A pointer to the Cup structure.
 * @param dice_i The index of the dice to toggle its lock
 * status.
 */
void cup_toggle_lock(Cup* target, size_t dice_i);

/**
 * @brief Initializes a new Cup with a specified number of
 * dice and faces.
 * @param dices_count The number of dice to create in the
 * cup.
 * @param dices_faces The number of faces each dice will
 * have.
 * @return A pointer to the newly initialized Cup structure.
 */
Cup* cup_init(size_t dices_count, uint8_t dices_faces);

/**
 * @brief Frees the memory allocated for the Cup and its
 * dice.
 * @param target A pointer to the Cup structure to close.
 */
void cup_close(Cup* target);

/**
 * @brief Sorts the dice in the cup by their value.
 * @param target A pointer to the Cup structure.
 */
void cup_sort(Cup* target);

/**
 * @brief Comparison function for sorting Dice structures by
 * their value.
 * @param a A pointer to the first Dice to compare.
 * @param b A pointer to the second Dice to compare.
 * @return A negative value if a < b, zero if a == b, or a
 * positive value if a > b.
 */
int dice_compare(const void* a, const void* b);

#endif // DICE_H
