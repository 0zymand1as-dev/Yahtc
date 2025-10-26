#include "../include/utils.h"
#include <stdlib.h>

int get_random_int(uint8_t max, uint8_t min)
{
  return (rand() % (max - min + 1)) + min;
}
