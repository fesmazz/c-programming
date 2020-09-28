#include <stdio.h>
#include <stdlib.h>
#include "future.h"

void add_future_card(future_cards_t *fc, size_t index, card_t * ptr){
    if (fc->decks == NULL) {
        fc->n_decks = index+1;
        fc->decks = malloc(fc->n_decks * sizeof(*(fc->decks)));
      for (size_t i = 0; i < fc->n_decks; i++){ //inicializando structs deck_t criadas no malloc acima
            fc->decks[i].cards = malloc(sizeof(*(fc->decks[i].cards)));
            fc->decks[i].n_cards = 0;    
        }
    }
    if (fc->n_decks <= index) { // se o número de elementos no array for menor que o índice, redimensione o array para o tamanho do índice
        fc->decks = realloc(fc->decks, (index+1) * sizeof(*(fc->decks)));
        for (size_t i = fc->n_decks; i <= index; i++){  //inicializando structs deck_t criadas no realloc acima
            fc->decks[i].cards = malloc(sizeof(*(fc->decks[i].cards)));
            fc->decks[i].n_cards = 0;
        }
        fc->n_decks = index+1;
    }
        fc->decks[index].cards = realloc(fc->decks[index].cards, (fc->decks[index].n_cards + 1) * sizeof(*(fc->decks[index].cards)));
        fc->decks[index].cards[fc->decks[index].n_cards] = ptr;
        fc->decks[index].n_cards++;
        return;
}

void future_cards_from_deck(deck_t * deck, future_cards_t * fc) {
    if(fc->n_decks == 0) {
        return;
    }
    size_t card_n = 0;
    for (size_t i = 0; i < fc->n_decks; i++){
        for (size_t j = 0; j < fc->decks[i].n_cards; j++) {
            if (fc->decks[i].cards[j] == NULL) {
                fprintf(stderr, "Error: card %ld on index %ld is empty\n", j, i);
                break;
            }
            fc->decks[i].cards[j]->value = deck->cards[card_n]->value;
            fc->decks[i].cards[j]->suit = deck->cards[card_n]->suit; 
        }
        card_n++;
    }
    return;
}
