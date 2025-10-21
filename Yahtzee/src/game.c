#include "../include/player.h"
#include "../include/scores.h"
#include <stdlib.h>

void game(size_t players_count, GameRules* rules)
{
  uint8_t currrent_round = 1;
  Table* table = table_init(players_count);

  while (currrent_round < rules->max_round)
  {
    for (size_t i = 0; i < players_count; i++)
    {
      player_play(&table->players[i], rules);
    }
  }

  table_close(table);

  return;
}
