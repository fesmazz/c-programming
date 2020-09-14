#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
  char * outname_buffer = malloc((strlen(inputName) + 8) * sizeof(*outname_buffer));  
  strcpy(outname_buffer, inputName);
  strcat(outname_buffer, ".counts");
  return outname_buffer;
}
