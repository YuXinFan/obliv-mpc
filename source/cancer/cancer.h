#pragma once

#include <obliv.h>
typedef struct protocolIO{
  int UniformityofCellSize;
  int UniformityofCellShape;
  int BareNuclei;
  int BlandChromatin;
  int SingleEpithelialCellSize;
  int ClumpThickness;
  int NormalNucleoli;
  int MarginalAdhesion;
  int Mitoses;
  bool benign;
} protocolIO;

void analyze(void* args);