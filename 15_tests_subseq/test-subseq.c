#include <stdio.h>
#include <stdlib.h>
size_t maxSeq(int * array, size_t n);

int main(void) {
  int array1[4] = {-1, 0, 0, 1};
  int array2[4] = {0, 0, 1, 2};
  int array3[9] = {1, 2, 3, 4, 1, 2, 3, 4, 5};
  int array4[13] = {1, 1, 1, 1, 1, 2, 1, 2, 2, 3, 1, 2, 3};
  int array5[] = {1, 10, 40, 90, -1, -20, -40, -60};
  int array6[] = {10000, 20, 90, 300, 4, 2, 52345, 34573478, 0, 50, 60, 70, 80};
  int array7[] = {0, 0};
  int array8[] = {};
  
 
  size_t n;
  n = maxSeq(array1, 4);
  if (n != 2) {exit(EXIT_FAILURE);}
  n = maxSeq(array1, 1);
  if (n != 1) {exit(EXIT_FAILURE);}
  n = maxSeq(array2, 4);
  if (n != 3) {exit(EXIT_FAILURE);}
  n = maxSeq(array3, 9);
  if (n != 5) {exit(EXIT_FAILURE);}
  n = maxSeq(array4, 13);
  if (n != 3) {exit(EXIT_FAILURE);}
  n = maxSeq(array5, 8);
  if (n != 4 ) {exit(EXIT_FAILURE);}
  n = maxSeq(array6, 13);
  if (n != 5 ) {exit(EXIT_FAILURE);}
  n = maxSeq(array7, 2);
  if (n != 1 ) {exit(EXIT_FAILURE);}
  n = maxSeq(array8, 0);
  if (n != 0 ) {exit(EXIT_FAILURE);}
  
  return EXIT_SUCCESS;
}

