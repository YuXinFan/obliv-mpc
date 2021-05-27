#pragma once

#include <obliv.h>
typedef struct vector{
  int size;
  int* arr;
} vector;

typedef struct protocolIO{
  vector input;
  vector output;
} protocolIO;

void mpcQsort(void* args);