#include <stdio.h>

void rotate (char matrix[10] [10]) {
  char temp[10] [10];
  for (int line = 0; line < 10; line++) {                // cria uma copia de matrix em temp rotacionada 90º
    for (int column = 0; column < 10; column++) {
      temp[column] [9-line] = matrix[line] [column];     
    }
  }
  for (int line = 0; line < 10; line++) {               //copia temp para matrix
     for (int column = 0; column < 10; column++) {
       matrix[line] [column] = temp[line] [column];
     }
  }
  return;
}

  
