#include "../include/scores.h"
#include "../include/player.h"

size_t evaluate_scores(Table* table, unsigned int winner_score)
{
  if (!table)
    return -1;

  for (size_t i = 0; i < table->players_count; i++)
    if (table->players[i].score >= winner_score)
      return i;

  return -1;
}
