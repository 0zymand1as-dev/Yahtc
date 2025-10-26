#pragma once
#ifndef SCORE_H
#define SCORE_H

#include <stdlib.h>

typedef struct Player Player;
typedef struct Table Table;

Player* evaluate_winner_score(Table* table);
Player* evaluate_max_score(Table* table);

#endif // SCORE_H
