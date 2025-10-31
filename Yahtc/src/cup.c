#include "../include/cup.h"
#include "../include/errors.h"
#include "../include/utils.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void cup_toggle_lock(Cup* target, size_t dice_i)
{
  if (!target || !target->dices || dice_i < 0 ||
      dice_i > target->count - 1)
  {
    return;
  }

  target->dices[dice_i].locked =
      !target->dices[dice_i].locked;
}

bool cup_get_repeted(const Cup* target, size_t times)
{
  if (!target || !target->dices || times < 1)
    return false;

  size_t freq_table[256] = {0};

  for (uint8_t i = 0; i < target->count; i++)
  {
    freq_table[target->dices[i].value]++;
  }

  for (size_t i = 1; i <= target->faces; i++)
  {
    if (freq_table[i] >= times)
      return true;
  }

  return false;
}

bool cup_get_all_equal(const Cup* target)
{
  if (!target || !target->dices)
    return false;

  uint8_t value = target->dices[0].value;

  for (size_t i = 0; i < target->count; i++)
  {
    if (target->dices[i].value != value)
      return false;
  }

  return true;
}

uint16_t cup_get_total_value(const Cup* target)
{
  if (!target || !target->dices)
    return 0;

  uint16_t value = 0;

  for (uint8_t i = 0; i < target->count; i++)
  {
    value += target->dices[i].value;
  }

  return value;
}

size_t
cup_get_value_count(const Cup* target, uint8_t dice_number)
{
  size_t count = 0;

  for (uint8_t i = 0; i < target->count; i++)
  {
    count += (target->dices[i].value == dice_number);
  }

  return count;
}

bool cup_get_straight(const Cup* target, size_t s_count)
{
  if (!target || !target->dices || target->count < s_count)
    return false;

  uint8_t freq_table[256] = {0};

  for (uint8_t i = 0; i < target->count; i++)
  {
    // Using 1 instead "++" optimize 3 lines of asm
    // ... 
    // Oh nevermind, i was using the -O0 flag 
    freq_table[target->dices[i].value] = 1;
  }

  size_t count = 0;

  for (uint8_t i = 1; i <= target->faces; i++)
  {
    if (freq_table[i])
    {
      count++;
      if (count >= s_count)
      {
        return true;
      }
    }
    else
    {
      count = 0;
    }
  }

  return false;
}

bool cup_get_full_house(const Cup* target)
{
  if (!target || !target->dices || target->faces == 0 ||
      target->count < 5)
    return false;

  size_t freq_table[256] = {0};

  for (size_t i = 0; i < target->count; i++)
  {
    freq_table[target->dices[i].value]++;
  }

  bool has_three = false, has_two = false;

  size_t six_percent = target->count * 0.60;
  size_t four_percent = target->count * 0.40;

  for (size_t i = 1; i <= target->faces; i++)
  {
    if (freq_table[i] == six_percent)
      has_three = true;
    else if (freq_table[i] == four_percent)
      has_two = true;
  }

  return (has_two && has_three);
}

void cup_throw(Cup* target)
{
  if (!target || !target->dices)
    return;

  for (uint8_t i = 0; i < target->count; i++)
  {
    target->dices[i].value =
        (target->dices[i].locked)
            ? target->dices[i].value
            : (uint8_t)get_random_int(target->faces, 1);
  }
}

void cup_lock(Cup* target, size_t dice_i)
{
  if (!target)
    return;

  if (!target->dices)
    return;

  if (dice_i < 0 || dice_i > target->count)
    return;

  target->dices[dice_i].locked = true;

  return;
}

void cup_lock_all(Cup* target)
{
  if (!target)
    return;

  if (!target->dices)
    return;

  for (uint8_t i = 0; i < target->count; i++)
  {
    target->dices[i].locked = true;
  }

  return;
}

void cup_unlock(Cup* target, size_t dice_i)
{
  if (!target || !target->dices)
    return;

  target->dices[dice_i].locked = false;

  return;
}

void cup_unlock_all(Cup* target)
{
  if (!target || !target->dices)
    return;

  for (size_t i = 0; i < target->count; i++)
  {
    target->dices[i].locked = false;
  }
}

Cup* cup_init(size_t dices_count, uint8_t dices_faces)
{
  Cup* new_cup = (Cup*)malloc(sizeof(Cup));

  if (!new_cup)
  {
    memerr("cup");
  }

  new_cup->dices =
      (Dice*)malloc(sizeof(Dice) * dices_count);

  if (!new_cup->dices)
  {
    memerr("dice");
  }

  new_cup->count = dices_count;
  new_cup->faces = dices_faces;

  for (size_t i = 0; i < dices_count; i++)
  {
    new_cup->dices[i].value = 1;
    new_cup->dices[i].locked = false;
  }

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

void cup_sort(Cup* target)
{
  if (!target || !target->dices)
    return;

  qsort(
      target->dices,
      target->count,
      sizeof(target->dices[0]),
      dice_compare);
}

int dice_compare(const void* a, const void* b)
{
  // if (!a || !b)
  //   return 0;
  return ((Dice*)a)->value - ((Dice*)b)->value;
}
