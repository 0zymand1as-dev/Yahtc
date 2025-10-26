#pragma once
#ifndef DICE_H
#define DICE_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct Dice
{
  uint8_t value;
  bool locked;
} Dice;

typedef struct Cup
{
  Dice* dices;
  size_t count;
} Cup;

uint8_t cup_throw(Cup* target);

uint8_t cup_lock(Cup* target, size_t dice_i);

uint8_t cup_lock_all(Cup* target);

uint8_t cup_unlock(Cup* target, size_t dice_i);

uint8_t cup_unlock_all(Cup* target);

Cup* cup_init(size_t capacity);

void cup_close(Cup* target);

#endif // DICE_H
