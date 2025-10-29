#include "../Yahtc/Yahtc.h"
#include <stdio.h>
#include <time.h>

void initial_menu(const State*, void* screen);

enum Hands player_select_hand(
    const State* state, Cup* cup, void* screen);

enum Hands ai_select_hand(const State*, Cup* cup, void* screen);

int main(void)
{
  srand(time(NULL));

  Rules rules = {
      .players_count = 2,
      .max_round = 4,
      .winner_score = 250,
      .rerolls = 3,
      .dices_count = 6,
      .dices_faces = 6};

  HandSelectionHandler player_menu = {
      .function = player_select_hand, .info = "Frederico"};

  HandSelectionHandler ai_menu = {
      .function = ai_select_hand, .info = "Gonzalo"};

  MenuHandler general_menu = {
      .function = initial_menu, .info = "General Menu"};

  State* game = game_init(&rules);

  game_sit_player(game, 0, &player_menu);
  game_sit_player(game, 1, &ai_menu);

  game_start(game, NULL);

  while (!game_done(game, &general_menu))
  {
    game_round(game, NULL);
    game_next(game, NULL);
  }

  game_end(game, NULL);
  game_close(game);
  return EXIT_SUCCESS;
}

void initial_menu(const State* state, void* screen)
{
  printf("\n");
  printf("=================================\n");
  printf("%s\n", (const char*)screen);
  printf("Current round: %d\n", state->round);

  for (uint8_t i = 0; i < state->table->count; i++)
  {
    printf(
        "Player %d have %d points\n",
        i,
        state->table->players[i].score);
  }

  printf("Current player hands: \n");

  for (uint8_t i = 0; i < HANDS_COUNT; i++)
  {
    printf(
        "Hand in %d: %d\n",
        i + 1,
        state->current_player->score_sheet->hands[i]);
  }
  getchar();

  return;
}

enum Hands ai_select_hand(
    const State* state, Cup* cup, void* screen)
{
  if (!state || !cup)
    return NONE;

  printf("\n");
  printf("================================\n");
  printf("Current player: %s\n", (char*)screen);

  getchar();

  return FULL_HOUSE;
}

enum Hands player_select_hand(
    const State* state, Cup* cup, void* screen)
{
  if (!state || !cup)
    return NONE;

  printf("\n");
  printf("================================\n");
  printf("AI turn: %s\n", (char*)screen);

  getchar();

  return FULL_HOUSE;
}
