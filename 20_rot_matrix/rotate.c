#include <stdio.h>
#include <string.h>

void rotate (char matrix[10] [10]) {
  char temp[10] [10];
  for (int line = 0; line < 10; line++) {
    for (int column = 0; column < 10; column++) {
      temp[line] [9-column] = matrix[line] [column];
    }
  }
  for (int line = 0; line < 10; line++) {
    strcpy (matrix[line], temp[line]);
      }
  return;
}

  
