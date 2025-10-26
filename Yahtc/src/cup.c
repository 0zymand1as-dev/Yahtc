#include "../include/cup.h"
#include "../include/utils.h"
#include <stdio.h>
#include <stdlib.h>

uint8_t cup_throw(Cup* target)
{
  if (!target)
    return 1;

  if (!target->dices)
    return 2;

  for (uint8_t i = 0; i < target->count; i++)
  {
    target->dices[i].value = (target->dices[i].locked)
                                 ? target->dices[i].value
                                 : get_random_int(6, 0);
  }

  return 0;
}

uint8_t cup_lock(Cup* target, size_t dice_i)
{
  if (!target)
    return 1;

  if (!target->dices)
    return 2;

  if (dice_i < 0 || dice_i > target->count)
    return 3;

  target->dices[dice_i].locked = true;

  return 0;
}

uint8_t cup_lock_all(Cup* target)
{
  if (!target)
    return 1;

  if (!target->dices)
    return 2;

  for (uint8_t i = 0; i < target->count; i++)
  {
    target->dices[i].locked = true;
  }

  return 0;
}

uint8_t cup_unlock(Cup* target, size_t dice_i)
{
  if (!target)
    return 1;

  if (!target)
    return 2;

  target->dices[dice_i].locked = false;

  return 0;
}

uint8_t cup_unlock_all(Cup* target)
{
  if (!target)
    return 1;

  if (!target->dices)
    return 2;

  for (uint8_t i = 0; i < target->count; i++)
  {
    target->dices[i].locked = false;
  }

  return 0;
}

Cup* cup_init(size_t dices_count)
{
  Cup* new_cup = (Cup*)malloc(sizeof(Cup));

  if (!new_cup)
  {
    fprintf(
        stderr, "No enough memory to allocate object: Cup");
    exit(1);
  }

  new_cup->dices = (Dice*)calloc(dices_count, sizeof(Dice));

  if (!new_cup->dices)
  {
    fprintf(
        stderr, "No enough memory to allocate object: Cup");
    exit(1);
  }

  new_cup->count = dices_count;

  return new_cup;
}

void cup_close(Cup* target)
{

  if (!target)
    return;

  free(target->dices);
  free(target);
  return;
}
