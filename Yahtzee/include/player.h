#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "./definitions.h"
#include "./game.h"
#include "./hand.h"
#include <stdlib.h>

typedef struct Cup Cup;

typedef struct Player
{
  Score score;
  Score* hands;
  Hand (*select_hand)(struct Player* self, GameRules*, Cup*, uint8_t rerolls);
  void (*show_error)(uint8_t);
} Player;

typedef struct Table
{
  Player* players;
  size_t players_count;
} Table;

void player_play(Player* target, GameRules* rules);

Player* player_init(void);

void player_close(Player* player);

Table* table_init(size_t players_count);

void table_close(Table* target);

#endif // PLAYER_H
