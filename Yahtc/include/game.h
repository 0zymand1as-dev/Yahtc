#pragma once
#include "./scores.h"
#ifndef GAME_H
#define GAME_H

#include "./player.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct Rules
{
  uint8_t players_count;
  uint8_t max_round;
  uint16_t winner_score;
  uint8_t rerolls;
  size_t dices_count;
  uint8_t dices_faces;
  uint8_t sstraight_count;
  uint8_t lstraight_count;
  uint8_t upper_bonus_req;
  uint8_t upper_bonus_amo;
  uint8_t extra_yahtzee_bonus;
} Rules;

typedef struct State
{
  Rules* rules;
  Player* current_player;
  Table* table;
  Cup* cup;
  uint8_t current_player_i;
  uint8_t round;
  uint8_t rerolls_left;
} State;

typedef void (*MenuCallback)(const State*, void* info);

typedef struct MenuHandler
{
  MenuCallback function;
  void* info;
} MenuHandler;

State* game_init(Rules*);

void game_start(State* target, MenuHandler* menu);

uint8_t game_sit_player(
    State* target,
    uint8_t position,
    HandSelectionHandler* menu);

void game_next(State*, MenuHandler*);

void game_round(State*, MenuHandler*);

bool game_done(State*, MenuHandler*);

void game_end(State*, MenuHandler*);

void game_close(State*);

#endif // GAME_H
