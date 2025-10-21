#pragma once
#ifndef GAME_H
#define GAME_H

#include "./definitions.h"
#include <stdint.h>
#include <stdlib.h>

typedef struct GameRules
{
  uint8_t players_count;
  uint8_t rerolls;
  uint8_t dices_count;
  uint8_t max_round;
  Score winner_score;
} GameRules;

void game(size_t players_count, GameRules* rules);

#endif // GAME_H
