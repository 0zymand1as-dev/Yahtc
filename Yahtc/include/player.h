#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "./scores.h"
#include <stdint.h>
#include <stdlib.h>

typedef struct State State;
typedef struct Cup Cup;

typedef enum Hands (*HandSelectionCallback)(
    const State*, Cup* cup, void* info);

typedef struct HandSelectionHandler
{
  HandSelectionCallback function;
  void* info;
} HandSelectionHandler;

typedef struct Player
{
  uint16_t total_score;
  HandSelectionHandler* play_menu;
  ScoreSheet* score_sheet;
} Player;

typedef struct Table
{
  Player* players;
  uint8_t count;
} Table;

uint8_t
table_sit(Table* target, uint8_t position, Player player);

Table* table_init(uint8_t players_count);

void table_close(Table* table);

#endif // PLAYER_H
