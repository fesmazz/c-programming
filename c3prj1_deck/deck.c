#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"
void print_card(card_t c);

void print_hand(deck_t * hand){
  for (size_t i = 0; i < hand->n_cards; i++) {
    print_card(*hand->cards[i]);
    printf (" ");
  }
}


int deck_contains(deck_t * d, card_t c) {
  for (size_t i = 0; i < d->n_cards; i++) {
    if (d->cards[i]->value == c.value) { // se o valor da carta na posição i do array for o mesmo da carta c
      if (d->cards[i]->suit == c.suit) {
	return 1;                //retorne 1 (i.e, o deck contém a carta)
      }
    }
  }
  return 0; // o deck não contém a carta 
  
}

void shuffle(deck_t * d){
  for (size_t i = 0; i < 15; i++) { // troca duas cartas de posição 15 vezes
    card_t * p1; // pointer para armazenar valor que será substituído
    size_t t1 = random() % d->n_cards;
    size_t t2 = random() % d->n_cards; //gera dois números aleatórios entre 0 e d.n_cards-1 
    p1 = d->cards[t1];    
    d->cards[t1] = d->cards[t2];
    d->cards[t2] = p1;
  }
}
   
void assert_full_deck(deck_t * d) {
  if (d->n_cards == 1) {
    return;
  }
  else {    
      deck_t tmp; //cria um novo deck sem a carta *(d->cards[0])
      tmp.cards = d->cards + 1;
      tmp.n_cards = d->n_cards - 1;
      deck_t * tmp_ptr = &tmp; // cria um pointer para o novo deck
      int v1 = deck_contains (tmp_ptr, *(d->cards[0]));
      if (v1 == 1) { //se *(d->cards[0]) estiver presente em tmp.cards 
	printf("Duplicate cards found on deck");
	assert(v1 == 0);
      }
      else { 
	assert_full_deck(tmp_ptr);
      }
    }
}

void add_card_to(deck_t * deck, card_t c){
  deck->n_cards++;
  deck->cards = realloc(deck->cards, deck->n_cards * sizeof(*(deck->cards)));
  deck->cards[deck->n_cards - 1] = malloc(sizeof(deck->cards[deck->n_cards - 1]));
  *(deck->cards[deck->n_cards - 1]) = c;
}

card_t * add_empty_card (deck_t * deck) {
  card_t c;
  c.value = 0;
  c.suit = 0;
  add_card_to(deck, c);
  return deck->cards[deck->n_cards - 1];
}

deck_t * make_deck_exclude(deck_t * excluded_cards){
  deck_t * deck = malloc(sizeof(*deck));
  deck->cards = NULL;
  deck->n_cards = 0;
  for(unsigned i = 0; i < 52; i++){
    card_t c = card_from_num(i);
    if (deck_contains(excluded_cards, c) != 1){
      add_card_to(deck, c);
    }
  }
  return deck;
}

deck_t * build_remaining_deck(deck_t ** hands, size_t n_hands) {
  deck_t * excluded_cards = malloc(sizeof(*excluded_cards));
  excluded_cards->cards = NULL;
  excluded_cards->n_cards = 0;
  for (size_t i = 0; i < n_hands; i++) {
    for(size_t j = 0; j < hands[i]->n_cards; j++) {
        add_card_to(excluded_cards, *(hands[i]->cards[j]));
    }
  }
  deck_t * remaining_deck = make_deck_exclude(excluded_cards);
  free_deck(excluded_cards);
  return remaining_deck;
}

void free_deck(deck_t * deck) {
  if(deck == NULL) {
    return;
  }
  else if (deck->cards == NULL) {
    free(deck);
    return;
    }
  for(size_t i = 0; i < deck->n_cards; i++) {
    free(deck->cards[i]);
  }
  free(deck->cards);
  free(deck);
  return;
}
