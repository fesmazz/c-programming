#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char ** write_input_to_arr(FILE * input, char ** arr, size_t line_lenght, size_t n_lines) {
  arr = (int **) arr; //convertendo tipo do array para aceitar todos os caracteres ASCI
  for (int i = 0; i < n_columns; i++) {
    if (i > n_lines) {
      fprintf(stderr, "Input file has too many lines!", i);
      exit (EXIT_FAILURE);
    }
    int line[line_lenght];   
    while (fgets(line, line_lenght, input) != NULL) {
      
      if (strchr(line, '\n') == NULL) {
	fprintf(stderr, "Line %d on input file is too long.", i);
	exit (EXIT_FAILURE);
      }
      if (*(strchr(line, '\n')) != line[line_lenght-1]) {
	fprintf(stderr, "Line %d on input file is too short.", i);
	exit (EXIT_FAILURE);
      }
      strcpy(arr[i][0], line[0]);
    }
  }
  arr = (char **) arr; // convertendo array de volta para o tipo original
  return arr; 
}


void rotate (char ** matrix) {
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
 
 void print_matrix (char ** matrix, size_t line_lenght, size_t n_columns) {

 }
 

int main (int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: rotateMatrix input_file\n");
    exit(EXIT_FAILURE);
  }
  FILE * input_file = fopen(argv[1], "r");
  if (input_file == NULL) {
    fprintf(stderr, "Could not open file: %s", argv[1]);
    exit(EXIT_FAILURE);
  }
  char matrix [10][11];
  write_input_to_arr(input_file, matrix, 11, 10);
  rotate(matrix);
  print_matrix(matrix);
  return 0;  
}
