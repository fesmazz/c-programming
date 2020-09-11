#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void check_characters(FILE * input) {
  int c;
  while ((c = fgetc(input)) != EOF) {
    if (c > 255) {
	fprintf(stderr, "Invalid characters detected on file");
      	exit (EXIT_FAILURE);
    }
  }
  rewind(input);
}

void  write_input_to_arr(FILE * input, char arr[10][12], size_t lines, size_t line_lenght) {
  int i = 0;
  char line[line_lenght]; 
  while (fgets(line, line_lenght, input) != NULL) {
    if (i > lines) {
      fprintf(stderr, "Input file has too many lines!");
      exit (EXIT_FAILURE);
    }    
    if (strchr(line, '\n') == NULL) {
      	fprintf(stderr, "Line %d on input file is too long.\n", i);
      	exit (EXIT_FAILURE);
       }
     if (strchr(line, '\n') != & line[10]) {
     	fprintf(stderr, "Line %d on input file is too short.\n", i);
     	exit (EXIT_FAILURE);
      }
    strcpy(arr[i], line);
    i++;
  }
  // print_matrix(arr, lines, line_lenght); 
}


void rotate (char matrix[10][12]) {
  char temp[10] [11];
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
 
 void print_matrix (char matrix [10][12], size_t lines) {   
     for (int i = 0; i < lines; i++) {
       fprintf(stdout, "%s", matrix[i]);
     }	        
 }
 

int main (int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: rotateMatrix input_file\n");
    exit(EXIT_FAILURE);
  }
  FILE * input_file = fopen(argv[1], "r");
  if (input_file == NULL) {
    fprintf(stderr, "Could not open file: %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }
  char matrix [10][12];
  check_characters(input_file);
  write_input_to_arr(input_file, matrix, 10, 12);
  rotate(matrix);
  print_matrix(matrix, 10);
  return 0;  
}
