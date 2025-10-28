#include "../include/errors.h"
#include <stdio.h>
#include <stdlib.h>

void memerr(const char* error)
{
  fprintf(stderr, "No enough memory left for: %s\n", error);
  exit(1);
}
