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
  uint8_t faces; // This never can be zero
} Cup;

bool cup_get_all_equal (const Cup* target);

bool cup_get_repeted (const Cup* target, size_t times);

uint16_t cup_get_total_value(const Cup* target);

size_t
cup_get_value_count(const Cup* target, uint8_t dice_number);

uint8_t cup_get_straight(const Cup* target, uint8_t s_count);

bool cup_get_full_house(const Cup* target);

void cup_throw(Cup* target);

void cup_lock(Cup* target, size_t dice_i);

void cup_lock_all(Cup* target);

void cup_unlock(Cup* target, size_t dice_i);

void cup_unlock_all(Cup* target);

Cup* cup_init(size_t dices_count, uint8_t dices_faces);

void cup_close(Cup* target);

void cup_sort(Cup* target);

int dice_compare(const void* a, const void* b);

#endif // DICE_H
