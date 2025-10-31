#include "../Yahtc/Yahtc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//                                  Menus
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

void clear_screen(void);

void print_cup(const Cup* cup);

void print_scoresheet(const Player* player);

void handle_game_state_change(
    const State* state, void* info);

enum Hands handle_player_turn(
    const State* state, Cup* cup, void* player_name);

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//                             Implementations
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#include <ctype.h>
#include <stdbool.h>
#include <string.h>

// Contains all the info needed by the player menu callback
typedef struct
{
  const char* name;
  bool* quit_flag;
} PlayerMenuInfo;

int

main(void)

{

  srand(time(NULL));

  // A single, local quit flag for the entire game.

  bool should_quit = false;

  Rules rules = {
      .players_count = 2,
      .max_round = 13,
      .winner_score = 1000,
      .rerolls = 3,
      .dices_count = 5,
      .dices_faces = 6,
      .sstraight_count = 4,
      .lstraight_count = 5,
      .upper_bonus_req = 63,
      .upper_bonus_amo = 35,
      .extra_yahtzee_bonus = 100};

  // Setup the menu info structs for each player

  PlayerMenuInfo playerA_info = {
      .name = "Frederico", .quit_flag = &should_quit};

  PlayerMenuInfo playerB_info = {
      .name = "Gonzalo", .quit_flag = &should_quit};

  HandSelectionHandler playerA_menu = {
      .function = handle_player_turn,

      .info = &playerA_info};

  HandSelectionHandler playerB_menu = {
      .function = handle_player_turn,

      .info = &playerB_info};

  MenuHandler game_menu = {
      .function = handle_game_state_change,

      .info = "Yahtzee Game"};

  State* game = game_init(&rules);

  game_sit_player(game, 0, &playerA_menu);

  game_sit_player(game, 1, &playerB_menu);

  game_start(game, &game_menu);

  while (!game_done(game, NULL) && !should_quit)

  {

    game_round(game, NULL);

    if (should_quit)

      break;

    game_next(game, &game_menu);
  }

  if (should_quit)

  {

    printf("\nQuitting game...\n");
  }

  else

  {

    game_end(game, &game_menu);
  }

  game_close(game);

  printf("Game finished. Thanks for playing!\n");

  return EXIT_SUCCESS;
}

void handle_game_state_change(
    const State* state, void* info)
{
  clear_screen();
  printf("=================================\n");
  printf("            %s\n", (const char*)info);
  printf("=================================\n");

  if (state->round == 0)
  { // Game has ended
    printf("\n--- FINAL SCORES ---\n");
    for (uint8_t i = 0; i < state->table->count; i++)
    {
      PlayerMenuInfo* p_info =
          (PlayerMenuInfo*)state->table->players[i]
              .play_menu->info;
      printf(
          "Player %d (%s): %d points\n",
          i + 1,
          p_info->name,
          state->table->players[i].total_score);
    }
    return;
  }

  printf(
      "Current Round: %d / %d\n",
      state->round,
      state->rules->max_round);
  printf("\n--- SCORES ---\n");
  for (uint8_t i = 0; i < state->table->count; i++)
  {
    printf(
        "Player %d: %d points\n",
        i + 1,
        state->table->players[i].total_score);
  }

  PlayerMenuInfo* p_info =
      (PlayerMenuInfo*)
          state->current_player->play_menu->info;
  printf("\nIt's %s's turn!\n", p_info->name);
  printf("Press Enter to continue...");
  getchar();
}

enum Hands prompt_for_hand(const Player* player)
{
  char input[10];
  int choice = -1;

  while (1)
  {
    printf("\nSelect hand to score:\n");
    print_scoresheet(player);
    printf(">>> ");

    if (fgets(input, sizeof(input), stdin))
    {
      choice = atoi(input);
      if (choice > 0 && choice < HANDS_COUNT &&
          player->score_sheet->hands[choice] == UINT8_MAX)
      {
        return (enum Hands)choice;
      }
    }
    printf(
        "Invalid selection. Please choose an empty "
        "slot.\n");
  }
}

enum Hands
handle_player_turn(const State* state, Cup* cup, void* info)
{
  PlayerMenuInfo* menu_info = (PlayerMenuInfo*)info;
  char input[256];

  while (1)
  {
    cup_sort(cup);
    clear_screen();
    printf("=================================\n");
    printf("        %s's Turn\n", menu_info->name);
    printf("=================================\n");
    printf("Rerolls left: %d\n\n", state->rerolls_left);

    print_cup(cup);

    if (state->rerolls_left == 0)
    {
      printf("No rerolls left. You must score.\n");
      return prompt_for_hand(state->current_player);
    }

    printf(
        "\nEnter dice indices to toggle lock (e.g., 1 3 4) "
        "and press Enter to reroll.\n");
    printf(
        "Or enter a command: [s] Score, [q] Quit, [v] View "
        "Scores\n");
    printf(">>> ");

    if (fgets(input, sizeof(input), stdin))
    {
      bool has_letter = false;
      bool has_digit = false;
      char first_letter = '\0';
      char temp_input[256];
      strcpy(temp_input, input);

      // 1. Validation Pass
      for (int i = 0; temp_input[i] != '\0'; i++)
      {
        if (isalpha(temp_input[i]))
        {
          if (first_letter == '\0')
            first_letter = tolower(temp_input[i]);
          has_letter = true;
        }
        if (isdigit(temp_input[i]))
        {
          has_digit = true;
        }
      }

      // 2. Process based on validation
      if (has_letter && has_digit)
      {
        printf("Error: Do not mix letters and numbers.\n");
      }
      else if (has_letter)
      {
        char* command = strtok(temp_input, " \t\n");
        if (command != NULL && strlen(command) == 1)
        {
          if (first_letter == 's')
            return prompt_for_hand(state->current_player);
          if (first_letter == 'q')
          {
            *(menu_info->quit_flag) = true;
            return CHANCE;
          }
          if (first_letter == 'v')
          {
            clear_screen();
            printf("--- Your Current Scores ---\n");
            print_scoresheet(state->current_player);
            printf(
                "\nPress Enter to return to your turn...");
            getchar();
            continue; // Loop back to the turn prompt
          }
        }
        printf(
            "Error: Invalid command. Use 's', 'q', or "
            "'v'.\n");
      }
      else
      { // Has digits or is empty
        char* token = strtok(input, " \t\n");
        while (token != NULL)
        {
          int dice_index = atoi(token);
          if (dice_index >= 1 &&
              dice_index <= (int)cup->count)
          {
            cup_toggle_lock(cup, dice_index - 1);
          }
          token = strtok(NULL, " \t\n");
        }
        return NONE; // Reroll
      }

      // If we reach here, there was an error.
      printf("Press Enter to continue...");
      getchar();
      continue;
    }
  }
}

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//                                  Utils
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

void clear_screen(void)
{
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

void print_cup(const Cup* cup)
{
  if (!cup || !cup->dices)
    return;

  // Note: These are multi-byte UTF-8 characters.
  const char* unlocked_dice[] = {
      "",
      "󰇊 ",
      "󰇋 ",
      "󰇌 ",
      "󰇍 ",
      "󰇎 ",
      "󰇏 "};
  const char* locked_dice[] = {
      "",
      "󱅊 ",
      "󱅋 ",
      "󱅌 ",
      "󱅍 ",
      "󱅎 ",
      "󱅏 "};

  printf("Your Dice:\n");
  for (size_t i = 0; i < cup->count; i++)
  {
    uint8_t val = cup->dices[i].value;
    const char* die_char = "[?]"; // Fallback

    if (val > 0 && val <= 6)
    {
      die_char = cup->dices[i].locked ? locked_dice[val]
                                      : unlocked_dice[val];
    }

    printf("  (%zu) %s\n", i + 1, die_char);
  }
}

void print_scoresheet(const Player* player)
{
  const char* hand_names[] = {
      "",
      "Aces",
      "Twos",
      "Threes",
      "Fours",
      "Fives",
      "Sixes",
      "3 of a Kind",
      "4 of a Kind",
      "Full House",
      "Sm. Straight",
      "Lg. Straight",
      "YAHTZEE",
      "Chance"};

  printf("--- Upper Section ---\n");
  for (int i = ACE; i <= SIX; i++)
  {
    if (player->score_sheet->hands[i] == UINT8_MAX)
    {
      printf("  [%2d] %-12s: [ ]\n", i, hand_names[i]);
    }
    else
    {
      printf(
          "  [%2d] %-12s: %d\n",
          i,
          hand_names[i],
          player->score_sheet->hands[i]);
    }
  }
  printf("--- Lower Section ---\n");
  for (int i = THREE_OF_A_KIND; i <= CHANCE; i++)
  {
    if (player->score_sheet->hands[i] == UINT8_MAX)
    {
      printf("  [%2d] %-12s: [ ]\n", i, hand_names[i]);
    }
    else
    {
      printf(
          "  [%2d] %-12s: %d\n",
          i,
          hand_names[i],
          player->score_sheet->hands[i]);
    }
  }
}
