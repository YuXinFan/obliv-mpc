#pragma once

#include <obliv.h>

typedef struct protocolIO
{ int median; // -1,0, or 1
  int larger;
  int smaller;
} protocolIO;

void median4(void* args);