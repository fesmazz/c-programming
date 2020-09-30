#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"

void print_card_to_file(card_t c, FILE * filename) {
  char value = value_letter(c);
  char suit = suit_letter(c);
  fprintf(filename, "%c%c ", value, suit);
}


int main(int argc, char ** argv) {

  if (argc < 2 || argc > 3) {
    fprintf(stderr, "Usage: %s input.txt numTrials\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  size_t num_trials = 10000; 

  if (argc == 3) {
    char * check_num;
    size_t temp = strtol(argv[2], &check_num, 0); //converte argv[2] para uma long em base 10
    //if (check_num == NULL) {
      num_trials = temp;
    //}
    //else {
      //fprintf(stderr, "numTrials must be a number. Exiting...\n");
      //exit(EXIT_FAILURE);
    //}
  }

/* Esta porção do código é responsável por abrir o arquivo indicado na execução do programa, definir e iniciliazar
as variáveis responsáveis por armazenar as informações obtidas, e criar as variáveis de trabalho do programa. */

  FILE * input = fopen(argv[1], "r");
  if (input == NULL) {
    fprintf(stderr, "Failed to open file %s\n", argv[1]);
    exit(EXIT_FAILURE);
    }

//debug -->
  FILE * debug = fopen("debug.txt", "w");
  if (input == NULL) {
    fprintf(stderr, "Failed to open file debug\n");
    exit(EXIT_FAILURE);
    }
// <-- debug

  future_cards_t fc;
    fc.decks = NULL;
    fc.n_decks = 0;

  size_t n_hands = 0;

  deck_t ** hands = read_input(input, &n_hands, &fc);

  deck_t * remaining_deck = build_remaining_deck(hands, n_hands);

  size_t win_count[n_hands+1]; 
  for (size_t i = 0; i <= n_hands+1; i++) {
    win_count[i] = 0;
  }

// Esta porção do código roda as simulações

  if (n_hands < 2) {
    fprintf(stderr, "At least 2 hands are needed to make a comparison\n");
    exit(EXIT_FAILURE);
  }
  for (size_t i = 0; i < num_trials; i++) {
    shuffle(remaining_deck);
    future_cards_from_deck(remaining_deck, &fc);
//debug -->
    for (size_t i = 0; i < n_hands; i++) {
      for (size_t j = 0; j < hands[i]->n_cards; j++) {
        print_card_to_file(*(hands[i]->cards[j]), debug);
      }
      fprintf(debug, ";");
    }
    fprintf(debug, "\n");
// <-- debug
    int best_hand = 0;
    int curr_hand = 0;
    int tie = -1;
    for (int i = 0; i < n_hands; i++) {
      if (compare_hands(hands[i], hands[curr_hand]) == 1) {
        curr_hand = i;
        if (compare_hands(hands[curr_hand], hands[best_hand]) == 1) {
          best_hand = i;
        }
      }
      else if (compare_hands(hands[i], hands[curr_hand]) == 0 ) {
        tie = i;
      }
    }
  if (tie > 0) {
    if (compare_hands(hands[best_hand], hands[tie]) == 1) {
      win_count[best_hand]++;
    }
    else {
      win_count[n_hands+1]++;
    }
  }
  else {
    win_count[best_hand]++;
    }
  } 
// Esta porção do código exibe os resultados 

  for (size_t i = 0; i < n_hands; i++) {
    float ratio = (float) win_count[i] / (float) num_trials * 100;
    fprintf(stdout, "Hand %zu won %lu / %lu times (%.2f%%)\n", i, win_count[i], num_trials, ratio);
  }
  fprintf(stdout, "And there were %lu ties\n", win_count[n_hands+1]);
  
//fechando arquivos e liberando memória alocada

  if (fclose(input) != 0) { 
    fprintf(stderr, "Error closing file %s\n", argv[1]);
    }
//debug -->
  if (fclose(debug) != 0) { 
    fprintf(stderr, "Error closing file %s\n", argv[1]);
    }  
// <-- debug
  for(size_t i = 0; i < fc.n_decks; i++) {
        free(fc.decks[i].cards);
    }
  free (fc.decks);

  for(size_t i = 0; i < n_hands; i++) {
        free_deck(hands[i]);
    }
  free(hands);

  free_deck(remaining_deck);

  return EXIT_SUCCESS;
}
