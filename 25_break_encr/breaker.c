#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

unsigned get_largest_element_index(unsigned * arr, size_t n) { // pega o indice do maior elemento em um array
  unsigned current_match = arr[0];
  unsigned best_match = arr[0];
  unsigned best_index = 0; 
  for (size_t i = 0; i < n; i++){
    const unsigned *p1 = &arr[i];
    if (*p1 > current_match){
      current_match = *p1;
      if (current_match > best_match){
	best_match = current_match;
	best_index = i;
      }
    }
  }
  return best_index;
}

char freq_count(FILE * f) { // retorna a letra que aparece com maior frequencia
  int c;
  unsigned freq_arr[26] = {0}; // array para armazenar contagem de letras 
  while ((c = fgetc(f)) != EOF) { // enquanto não encontrarmos o sinalizador de END OF FILE
    if (isalpha(c)) { // se c pertence ao alfabeto
      c = tolower(c); // tranforma c em lower-case
      c -= 'a'; // retirnado o valor de a, para que c fique entre 0 e 25
      freq_arr[c] += 1; // adiciona um à posição do array cujo índice corresponde à letra lida por fgetc
    }
  }
  unsigned index = get_largest_element_index(freq_arr, 26);
  char ans = (char) index + 'a';
  return ans;
}

int break_encr (char c){
  int key = c - 'e';
  if (key >= 0) {
    return key;
  }
  else {
    key += 26;
    return key;
  }
}


int main (int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s input_file\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  FILE * input_file = fopen(argv[1], "r");
  if (input_file == NULL) {
    fprintf(stderr, "Could not open file: %s", argv[1]);
    exit(EXIT_FAILURE);
  }

  char x = freq_count(input_file); // retorna a letra que aparece com maior frequência em input_file
  int key = break_encr(x); // retorna a chave a partir da qual o texto foi codificado
  fprintf(stdout, "%d\n", key);
  return 0;
}
