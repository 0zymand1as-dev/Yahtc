#include "../include/game.h"
#include "../include/cup.h"
#include "../include/errors.h"
#include "../include/player.h"
#include <stdio.h>

State* game_init(Rules* rules)
{
  State* new_state = (State*)malloc(sizeof(State));
  if (!new_state)
  {
    memerr("game state");
  }

  new_state->table = table_init(rules->players_count);

  new_state->cup =
      cup_init(rules->dices_count, rules->dices_faces);

  new_state->rules = rules;
  new_state->round = 0;
  new_state->rerolls_left = 0;
  new_state->current_player = NULL;
  new_state->current_player_i = -1;

  if (!new_state->cup)
    return NULL;

  return new_state;
}

uint8_t game_sit_player(
    State* target,
    uint8_t position,
    HandSelectionHandler* menu)
{
  ScoreSheet* player_score_sheet = score_init();

  if (!player_score_sheet)
  {
    memerr("player score sheet");
  }

  return table_sit(
      target->table,
      position,
      (Player){.play_menu = menu,
               .score = 0,
               .score_sheet = player_score_sheet});
}

void game_start(State* target, MenuHandler* menu)
{
  if (!target)
    return;

  // This is a count, not a index, thats
  // why it start at 1
  target->round = 1;
  target->rerolls_left = target->rules->rerolls;
  target->current_player_i = 0;
  target->current_player = &(target->table->players[0]);

  if (menu)
    menu->function(target, menu->info);

  return;
}

void game_next(State* target, MenuHandler* menu)
{
  if (!target)
    return;

  // Incrementing round if all players played
  if (target->current_player_i ==
      target->rules->players_count - 1)
    target->round++;

  // Looping through each of the players, 0 if end is
  // reached
  target->current_player_i =
      (target->current_player_i + 1) %
      target->rules->players_count;

  // getting new current player
  target->current_player =
      &(target->table->players[target->current_player_i]);

  target->rerolls_left = target->rules->rerolls;

  cup_unlock_all(target->cup);

  if (menu)
    menu->function(target, menu->info);

  return;
}

void game_round(State* target, MenuHandler* menu)
{
  HandSelectionHandler* play_menu =
      target->current_player->play_menu;
  enum Hands current_hand;

  do
  {
    cup_throw(target->cup);
    current_hand = play_menu->function(
        target, target->cup, play_menu->info);
  } while (current_hand == NONE &&
           target->rerolls_left-- > 0);

  target->current_player->score += score_evaluate(
      target->rules,
      current_hand,
      target->cup,
      target->current_player->score_sheet);

  if (menu)
    menu->function(target, menu->info);

  return;
}

bool game_done(State* target, MenuHandler* menu)
{
  if (target->round >= target->rules->max_round)
  {
    if (menu)
      menu->function(target, menu->info);
    return true;
  }

  for (uint8_t i = 0; i < target->rules->players_count; i++)
  {
    if (target->table->players[i].score >
        target->rules->winner_score)
    {
      if (menu)
        menu->function(target, menu->info);

      return true;
    }
  }

  if (menu)
    menu->function(target, menu->info);

  return false;
}

void game_end(State* target, MenuHandler* menu)
{
  if (menu)
    menu->function(target, menu->info);

  target->current_player = NULL;
  target->round = 0;

  return;
}

void game_close(State* target)
{
  table_close(target->table);
  cup_close(target->cup);

  free(target);
  return;
}
