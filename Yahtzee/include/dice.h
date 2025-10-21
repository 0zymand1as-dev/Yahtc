#pragma once
#include <stdint.h>
#ifndef DICE_H
#define DICE_H

#include "./definitions.h"
#include <stdbool.h>
#include <stdlib.h>

typedef struct Dice
{
    uint8_t value;
    bool locked;
} Dice;

typedef struct Cup
{
    Dice* dices;
    size_t capacity;
} Cup;

Dice* cup_throw(Dice* locked);

Cup* cup_init(size_t capacity);

void cup_close(Cup* target);

#endif // DICE_H
