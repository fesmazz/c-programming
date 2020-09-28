#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"

deck_t * hand_from_string(const char * str, future_cards_t * fc) { 
    deck_t * hand = malloc(sizeof(*hand));
    hand->cards = NULL;
    hand->n_cards = 0;
    char * tokbuffer = strdup(str);
    char * tokbuffer_ptr = tokbuffer;
    *(strchr(tokbuffer, '\n')) = '\0'; //excluindo newline do buffer
    for (char * p = strtok(tokbuffer, " "); p != NULL; p = strtok(NULL, " ")) {
        //printf("DEBUG: p inside the loop is = %s\n", p);
        char value_let = p[0];
        char suit_let = p[1];
        if (value_let == '?'){
            int unk_index = suit_let - '0'; //converte o valor de suit_let para int
            card_t * future_card = add_empty_card(hand);
            add_future_card(fc, unk_index, future_card);
            future_card = NULL;
        }
        else {
        card_t c = card_from_letters(value_let, suit_let);
        add_card_to(hand, c);
        }
    }
    free(tokbuffer_ptr);
    return hand;
}

deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc) {
    deck_t ** ans = malloc(sizeof(**ans));
    ans = NULL;
    char * curr_line = NULL;
    size_t sz = 0;
    size_t count_hands = 0; 
    while ((getline(&curr_line, &sz, f)) >= 0 ) {
        ans = realloc(ans, (count_hands+1) * sizeof(*ans));
        deck_t * hand = hand_from_string(curr_line, fc);
        if (hand->n_cards < 5) {
            fprintf(stderr, "Hand on line %ld has less than 5 cards. Aborting...\n", count_hands);
            exit(EXIT_FAILURE);
        }
        ans[count_hands] = hand;
        count_hands++;
    }
    free(curr_line);
    *n_hands = count_hands; //retornando o valor de mãos lidas no input por meio deste pointer
    return ans; 
}