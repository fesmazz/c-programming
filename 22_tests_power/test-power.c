#include <stdio.h>
#include <stdlib.h>

unsigned power (unsigned x, unsigned y);
//void run_check (unsigned x, unsigned y, unsigned expected_ans);
void test (unsigned x, unsigned y, unsigned expected_ans) {
  unsigned temp = power(x, y);
  if (temp != expected_ans) {
    exit (EXIT_FAILURE);
  }
  
}

  

int main (void) {

  char x = 2;
  char y = 4;
  
  test (1, 2, 1);
  test (1, 1, 1);
  test (2, 2, 4);
  test (1, 0, 1);
  test (0, 1, 0);
  test (10000, 0, 1);
  test (12345, 1, 12345);
  test (x, y, 16);
  //  test (1, -1, 1);
  //  test (2, -1, 0.5);
  //  test (4, -2, 0.0625);
  test (-2, 2, 4);
  test (-2, 3, -8);
  test (0, 0, 1);

  printf ("\nAll tests ok\n");
  
  return 0;
}
  
