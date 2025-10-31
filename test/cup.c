#include "../Yahtc/include/cup.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void cup_print(Cup* cup);

int main(void)
{
  srand(time(NULL));
  Cup* cup = cup_init(5, 6);

  printf("Initialized:\n");
  cup_print(cup);

  printf("\n\n");
  printf("Throwing and getting info!\n");
  printf("Commands:\n");
  printf(
      "  - Enter dice indices to lock/unlock (separated by "
      "spaces or commas, e.g., 0 2 4)\n");
  printf("  - Press Enter alone to throw all dice\n");
  printf("  - Type 'q' and press Enter to quit\n\n");

  bool sort_dices = false;

  char input[256];
  while (1)
  {
    printf("================================\n");

    // Leer entrada del usuario
    printf("> ");
    if (fgets(input, sizeof(input), stdin) == NULL)
      break;

    // Verificar si el usuario quiere salir
    if (input[0] == 'q' || input[0] == 'Q')
    {
      printf("Exiting game...\n");
      break;
    }

    // Procesar índices si la línea no está vacía (ignorar
    // solo '\n')
    if (input[0] != '\n')
    {
      // Verificar comandos especiales
      if (input[0] == 'u' || input[0] == 'U')
      {
        cup_unlock_all(cup);
        printf("Unlocked all dice\n");
      }
      else if (input[0] == 'l' || input[0] == 'L')
      {
        cup_lock_all(cup);
        printf("Locked all dice\n");
      }
      else if (input[0] == 's' || input[0] == 'S')
      {
        printf("Sorting dices...\n");
        sort_dices = true;
      }
      else
      {
        // Separar por espacios, comas, tabs y newlines
        char* token = strtok(input, " ,\t\n");
        while (token != NULL)
        {
          // Convertir a entero
          int dice_index = atoi(token);

          // Verificar si el índice es válido (asumiendo 5
          // dados: 0-4)
          if (dice_index >= 0 && dice_index < 5)
          {
            cup_toggle_lock(cup, dice_index);
            printf("Toggled lock on dice %d\n", dice_index);
          }
          else
          {
            printf(
                "Invalid index: %d (must be 0-4)\n",
                dice_index);
          }

          token = strtok(NULL, " ,\t\n");
        }
      }
    }

    printf("Throwing...\n");
    cup_throw(cup);

    if (sort_dices)
      cup_sort(cup);

    cup_print(cup);
    printf("Total value: %d\n", cup_get_total_value(cup));

    printf("\n");
    printf("Are all equal: %d\n", cup_get_all_equal(cup));
    printf(
        "Repeated four times: %d\n",
        cup_get_repeted(cup, 4));
    printf("Straight of 4: %d\n", cup_get_straight(cup, 4));
    printf("Full house: %d\n", cup_get_full_house(cup));
    printf("\n");
    printf("One: %zu\n", cup_get_value_count(cup, 1));
    printf("Two: %zu\n", cup_get_value_count(cup, 2));
    printf("Three: %zu\n", cup_get_value_count(cup, 3));
    printf("Four: %zu\n", cup_get_value_count(cup, 4));
    printf("Five: %zu\n", cup_get_value_count(cup, 5));
    printf("Six: %zu\n", cup_get_value_count(cup, 6));
    printf("\n");

    sort_dices = false;
  }

  printf("Game ended.\n");

  cup_close(cup);
  return EXIT_SUCCESS;
}

void cup_print(Cup* cup)
{
  if (!cup || !cup->dices)
  {
    printf("Cup is empty\n");
  }

  printf("Cup\n");
  printf("faces: %hhu\n", cup->faces);
  printf("dices: %zu\n", cup->count);

  for (size_t i = 0; i < cup->count; i++)
  {
    printf(
        "[%zu] - value: %hhu, locked: %hhu\n",
        i,
        cup->dices[i].value,
        cup->dices[i].locked);
  }
}
