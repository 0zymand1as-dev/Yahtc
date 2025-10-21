#pragma once
#ifndef SCORE_H
#define SCORE_H

#include <stdlib.h>

typedef struct Table Table;

size_t evaluate_scores(Table* table, unsigned int winner_score);

#endif // SCORE_H
