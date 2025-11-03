#pragma once
#include "./scores.h"
#ifndef GAME_H
#define GAME_H

#include "./player.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/**
 * @brief Defines the rules and settings for a Yahtzee game.
 */
typedef struct Rules
{
  /**
   * @field players_count The number of players in the game.
   */
  uint8_t players_count;
  /**
   * @field max_round The maximum number of rounds to be
   * played.
   */
  uint8_t max_round;
  /**
   * @field winner_score The score required to win the game.
   */
  uint16_t winner_score;
  /**
   * @field rerolls The number of rerolls allowed per turn.
   */
  uint8_t rerolls;
  /**
   * @field dices_count The number of dice used in the game.
   */
  size_t dices_count;
  /**
   * @field dices_faces The number of faces on each die.
   */
  uint8_t dices_faces;
  /**
   * @field sstraight_count The number of dice required for
   * a small straight.
   */
  uint8_t sstraight_count;
  /**
   * @field lstraight_count The number of dice required for
   * a large straight.
   */
  uint8_t lstraight_count;
  /**
   * @field upper_bonus_req The required score in the upper
   * section to get a bonus.
   */
  uint8_t upper_bonus_req;
  /**
   * @field upper_bonus_amo The amount of the upper section
   * bonus.
   */
  uint8_t upper_bonus_amo;
  /**
   * @field extra_yahtzee_bonus The bonus points for
   * additional Yahtzees.
   */
  uint8_t extra_yahtzee_bonus;
  /**
   * @field full_house_points The points awarded for a full
   * house.
   */
  uint8_t full_house_points;
  /**
   * @field sstraight_points The points awarded for a small
   * straight.
   */
  uint8_t sstraight_points;
  /**
   * @field lstraight_points The points awarded for a large
   * straight.
   */
  uint8_t lstraight_points;
  /**
   * @field yahtzee_points The points awarded for a Yahtzee.
   */
  uint8_t yahtzee_points;
} Rules;

/**
 * @brief Represents the current state of the game.
 */
typedef struct State
{
  /**
   * @field rules Pointer to the game rules.
   */
  Rules* rules;
  /**
   * @field current_player Pointer to the player whose turn
   * it is.
   */
  Player* current_player;
  /**
   * @field table Pointer to the game table containing
   * players.
   */
  Table* table;
  /**
   * @field cup Pointer to the dice cup.
   */
  Cup* cup;
  /**
   * @field current_player_i Index of the current player.
   */
  uint8_t current_player_i;
  /**
   * @field round The current round number.
   */
  uint8_t round;
  /**
   * @field rerolls_left The number of rerolls remaining for
   * the current turn.
   */
  uint8_t rerolls_left;
} State;

/**
 * @brief Callback function for menu interactions.
 * @param state A pointer to the current game state.
 * @param info A pointer to additional information for the
 * callback.
 */
typedef void (*MenuCallback)(const State*, void* info);

/**
 * @brief Handles menu interactions by associating a
 * callback function with custom information.
 */
typedef struct MenuHandler
{
  /**
   * @field function The menu callback function to be
   * executed.
   */
  MenuCallback function;
  /**
   * @field info A pointer to custom data passed to the menu
   * callback function.
   */
  void* info;
} MenuHandler;

/**
 * @brief Initializes a new game state with the given rules.
 * @param rules A pointer to the game rules to be used.
 * @return A pointer to the newly created game state, or
 * NULL if initialization fails.
 */
State* game_init(Rules*);

/**
 * @brief Starts the game, setting up initial round,
 * rerolls, and current player.
 * @param target A pointer to the game state.
 * @param menu A pointer to the menu handler for game start
 * events.
 */
void game_start(State* target, MenuHandler* menu);

/**
 * @brief Sits a player at a specified position in the game.
 * @param target A pointer to the game state.
 * @param position The desired position for the player.
 * @param menu A pointer to the hand selection handler for
 * the player.
 * @return 0 on success, 1 on failure.
 */
uint8_t game_sit_player(
    State* target,
    uint8_t position,
    HandSelectionHandler* menu);

/**
 * @brief Advances the game to the next player or round.
 * @param target A pointer to the game state.
 * @param menu A pointer to the menu handler for next turn
 * events.
 */
void game_next(State*, MenuHandler*);

/**
 * @brief Executes a single round of the game for the
 * current player.
 * @param target A pointer to the game state.
 * @param menu A pointer to the menu handler for round
 * events.
 */
void game_round(State*, MenuHandler*);

/**
 * @brief Checks if the game has met its ending conditions.
 * @param target A pointer to the game state.
 * @param menu A pointer to the menu handler for game done
 * events.
 * @return True if the game is done, false otherwise.
 */
bool game_done(State*, MenuHandler*);

/**
 * @brief Ends the game, performing any necessary cleanup or
 * final actions.
 * @param target A pointer to the game state.
 * @param menu A pointer to the menu handler for game end
 * events.
 */
void game_end(State*, MenuHandler*);

/**
 * @brief Frees all resources associated with the game
 * state.
 * @param target A pointer to the game state to be closed.
 */
void game_close(State*);

#endif // GAME_H
