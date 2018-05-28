#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void delay(ms) {
  clock_t end_time = clock() / CLOCKS_PER_SEC * 1000 + ms;

  while ((clock() / CLOCKS_PER_SEC * 1000) < end_time);
}

int main () {
  int j = 0;

  printf("Hello Mac  ");
  delay(1000);

  for (int i = 0; i < 60; i++) {
    j = i % 4;

    switch (j) {
      case 0:
        printf("\b|");
        break;
      case 1:
        printf("\b/");
        break;
      case 2:
        printf("\b-");
        break;
      default:
        printf("\b\\");
        break;
    }
    delay(17);
  }

  printf("\bDone!\n");

  return 0;
}
