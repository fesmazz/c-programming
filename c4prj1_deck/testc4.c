#include <stdio.h>
#include <stdlib.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"

void create_hand_n(deck_t * hand, size_t n) {
    for (size_t i = 0; i < n; i++){
        unsigned r = random() % 51;
        card_t c = card_from_num(r);
        add_card_to(hand, c);
    }
    print_hand(hand);
    fprintf(stdout,"\nHand has %ld cards \n", hand->n_cards);
}

int main(void){

deck_t * hand1 = malloc(sizeof(*hand1));
deck_t * hand2 = malloc(sizeof(*hand2));
deck_t * hand3 = malloc(sizeof(*hand3));

hand1->cards = hand2->cards = hand3->cards = NULL;
hand1->n_cards = hand2->n_cards = hand3->n_cards = 0;

fprintf(stdout, "Criando mão 1: ");
create_hand_n(hand1, 5);
fprintf(stdout, "Criando mão 2: ");
create_hand_n(hand2, 5);
fprintf(stdout, "Criando mão 3: ");
create_hand_n(hand3, 5);

deck_t * hands[3] = {hand1, hand2, hand3};
fprintf(stdout, "Retirando as cartas das mãos 1 a 3, o deck restante é: \n");
deck_t * test_deck = build_remaining_deck(hands, 3);
print_hand(test_deck);
fprintf(stdout,"\n");

free_deck(hand1);
free_deck(hand2);
free_deck(hand3);
free_deck(test_deck);
}