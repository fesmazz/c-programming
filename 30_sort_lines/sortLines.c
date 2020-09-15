#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

int main(int argc, char ** argv) {
  char ** lines = NULL;
  char * curr_line = NULL;
  size_t sz = 0;
  size_t line_count = 0;
  if (argc == 1) {
    while (getline(&curr_line, &sz, stdin) >= 0) {
      lines = realloc(lines, (line_count + 1) * sizeof(*lines));
      lines[line_count] = malloc(sz * sizeof(**lines));
      strcpy(lines[line_count], curr_line);
      line_count++;
    }
  }
  else {
    for (int i = 1; i <= argc-1; i++) {
      FILE * input = fopen(argv[i], "r");
      if (input == NULL) {
         fprintf(stderr, "Error opening file: %s\n", argv[i]);
         free (curr_line);
         for (int i = 0; i < line_count; i++) {
            free(lines[i]);
          }
          free(lines); 
         exit(EXIT_FAILURE);
      }
       while (getline(&curr_line, &sz, input) >= 0) {
        lines = realloc(lines, (line_count + 1) * sizeof(*lines));
        lines[line_count] = malloc(sz * sizeof(**lines));
        strcpy(lines[line_count], curr_line);
        line_count++;
      }
      fclose(input);
    } 
  }
  free(curr_line);
  if (lines == NULL) {
    fprintf(stderr, "No lines found to sort\n");   
    exit(EXIT_FAILURE);
  }
  sortData(lines, line_count);
  for (int i = 0; i < line_count; i++) {
    fprintf(stdout, "%s", lines[i]);
    free(lines[i]);
  }
  free (lines);  
  return EXIT_SUCCESS;
}
