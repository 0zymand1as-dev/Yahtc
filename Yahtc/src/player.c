#include "../include/player.h"
#include <stdlib.h>

Table* table_init(uint8_t players_count)
{
  Table* new_table = (Table*)malloc(sizeof(Table));
  if (!new_table)
    return NULL;

  new_table->players =
      (Player*)malloc(sizeof(Player) * players_count);

  if (!new_table->players)
    return NULL;

  new_table->count = players_count;

  return new_table;
}

uint8_t
table_sit(Table* target, uint8_t index, Player player)
{
  if (!target || !target->players)
    return 1;

  target->players[index] = player;

  return 0;
}

void table_close(Table* table)
{
  if (!table)
    return;

  for (uint8_t i = 0; i < table->count; i++)
  {
    free(table->players[i].hands);
  }

  free(table->players);

  free(table);

  return;
}
