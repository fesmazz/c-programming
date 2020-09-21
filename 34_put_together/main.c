#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  FILE * input = fopen(filename, "r");
  if (input == NULL) {
    fprintf(stderr, "Couldn't open file %s. Check the file name and try again\n", filename);
    exit(EXIT_FAILURE);
  }
  counts_t * c = createCounts();
  char * curr_line = NULL;
  size_t sz = 0;
  while ((getline(&curr_line, &sz, input) >= 0)) {
    *(strchr(curr_line, '\n')) = '\0';
    size_t isOnList = 0;
    for(int i = 0; i < kvPairs->lenght; i++){
      if (strcmp(kvPairs->array[i]->key, curr_line) == 0 ) {
        addCount(c, kvPairs->array[i]->value);
        isOnList++;
      }
    }
    if (isOnList == 0) {
    addCount(c, NULL);
    }
  }   
  free(curr_line);
  fclose(input);
  return c;
}

int main(int argc, char ** argv) {
  if(argc < 3){
    fprintf(stderr, "Uso: chaves.txt lista.txt\n");
    exit(EXIT_FAILURE);
  }
  kvarray_t * kv = readKVs(argv[1]);
  for (int i = 2; i < argc; i++) {
    counts_t * c = countFile(argv[i], kv);
    char * outName = computeOutputFileName(argv[i]);
    FILE * f = fopen(outName,"w");
    if (f == NULL){
      fprintf(stderr, "Não foi possível criar o arquivo %s", outName);
    }
    printCounts(c, f);
    fclose(f);
    free(outName);
    freeCounts(c);
  }
  freeKVs(kv);
  return EXIT_SUCCESS;
}
