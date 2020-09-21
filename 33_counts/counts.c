#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"
counts_t * createCounts(void) {
  counts_t * c = malloc(sizeof(*c));
  c->strings = NULL;
  c->numStrings = 0;
  c->numUnknown = 0;
  return c;
}
void addCount(counts_t * c, const char * name) {
  if (name == NULL) {
    c->numUnknown++;
    return;
  }
  for (size_t i = 0; i < c->numStrings; i++) {
    if (strcmp(c->strings[i]->string, name) == 0){
      c->strings[i]->count++;
      return;
    }
  }
  size_t index = c->numStrings;
  //alocando espaço para nova string/contagem
  c->strings = realloc(c->strings, (c->numStrings +1) * sizeof(c->strings));
  c->strings[index] = malloc(sizeof(*(c->strings[index])));
  c->strings[index]->string = malloc((1 + strlen(name)));
  //fim dos alocamentos de memória
  strcpy(c->strings[index]->string, name);
  c->strings[index]->count = 1;
  c->numStrings++;    
  return;
}

void printCounts(counts_t * c, FILE * outFile) {
  if (c->strings == NULL) {
    fprintf(stderr, "Dados não encontrados\n");
    exit(EXIT_FAILURE);
  }
  for (size_t i = 0; i < c->numStrings; i++) {
    fprintf(outFile, "%s: %ld\n", c->strings[i]->string, c->strings[i]->count);
  }
  if (c->numUnknown > 0) {
    fprintf(outFile, "<unknown> : %ld\n", c->numUnknown);
  }
  return;
}

void freeCounts(counts_t * c) {
  for (size_t i = 0; i < c->numStrings; i++) {
    free(c->strings[i]->string);
    free(c->strings[i]);
  }
  free(c->strings);
  free(c);
  return;
}
