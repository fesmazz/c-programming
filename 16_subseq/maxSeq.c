#include <stdlib.h>
#include <stdio.h>

size_t maxSeq (int *array, size_t n) {
  if (n <= 0 || array == NULL) {
    int except = 0;
    return except;
  }
  int best_count = 1;
  int curr_count = 1;
  int curr_e;
  int next_e;
  for (int i = 0; i < n; i++) {
    if (i < n - 1){  
      curr_e = array[i];
      next_e = array[i+1];
      if (next_e > curr_e) {
	curr_count++;
	if (curr_count > best_count) {best_count = curr_count;}
      }
      else {curr_count = 1;}
    }
  }
  return best_count;
}

    
