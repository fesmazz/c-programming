#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"

char * get_key(char * line, size_t line_number) { 
  char * key = malloc(1+(strlen(line)) * sizeof(*key));
  strcpy(key, line);
  strtok(key, "="); //divide a string no sinal de =
    if (key == NULL) {
      fprintf(stderr,"Input format on line %ld is wrong. Couldn't find \"=\" separator\n", line_number);
	exit(EXIT_FAILURE);
	}
    return key;
}

char * get_value(char * line) {
  char * temp = strchr(line, '=') + 1;
  char * value = malloc((1+strlen(temp)) * sizeof(*value));
  strcpy (value, temp);
  *(strchr(value, '\n')) = '\0';
  return value;
}
  
kvarray_t * readKVs(const char * fname) {
  FILE * input = fopen(fname, "r");
  if (input == NULL) {
    fprintf(stderr, "Couldn't open file %s. Check the file name and try again\n", fname);
    exit(EXIT_FAILURE);
  }
  char * curr_line = NULL;
  size_t sz = 0;
  kvarray_t * pairs = malloc(sizeof(*pairs)); 
  pairs->array = malloc(sizeof(*pairs));
  pairs->lenght = 0;
  while ((getline(&curr_line, &sz, input) >= 0)) {
    pairs->array = realloc(pairs->array, (1+ pairs->lenght) * sizeof(*pairs));
    pairs->array[pairs->lenght] = malloc(sizeof(*pairs)); 
    pairs->array[pairs->lenght]->key = get_key(curr_line, pairs->lenght);
    pairs->array[pairs->lenght]->value = get_value(curr_line);
    pairs->lenght++;
  }
  free(curr_line);
  fclose(input);
  return pairs;
}

void freeKVs(kvarray_t * pairs) {
  for (size_t i = 0; i < pairs->lenght; i++) {
    free(pairs->array[i]->key);
    free(pairs->array[i]->value);
    free(pairs->array[i]);
   }
  free(pairs->array);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  for (size_t i = 0; i < pairs->lenght; i++) {
    printf("key = '%s' value = '%s'\n", pairs->array[i]->key, pairs->array[i]->value);    
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  for (size_t i = 0; i < pairs->lenght; i++) {
    if (strcmp(pairs->array[i]->key, key) == 0) {
      return pairs->array[i]->value;
    }
  }
  return NULL;
}
