#include "../include/errors.h"
#include <stdio.h>
#include <stdlib.h>

void memerr(const char* error_message)
{
  fprintf(
      stderr,
      "No enough memory left for: %s\n",
      error_message);
  exit(1);
}

void apierr(const char* error_message)
{
  fprintf(
      stderr, "Error using Yahtc api: %s\n", error_message);
  exit(1);
}
