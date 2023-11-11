#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int coinToss (int n) {
  time_t t1;
  srand((unsigned)time(&t1));
  int random = rand() % n;

  return random;
}
