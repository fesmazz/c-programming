#include "cards.h"
#include <stdio.h>

int main(void) {

  card_t card1, card2, card3, card4;
  card1.value = 8;
  card1.suit = SPADES;
  card2.value = 6;
  card2.suit = CLUBS;
  card3.value = 12;
  card3.suit = HEARTS;
  card4.value = 14;
  card4.suit = DIAMONDS;

  printf("Starting tests...\n");
  assert_card_valid(card1);
  assert_card_valid(card2);
  assert_card_valid(card3);
  assert_card_valid(card4);
  printf("All entered cards are valid!\n");
  printf("Card 1 is ");
  print_card(card1);
  printf("\n");
  printf("Card 2 is ");
  print_card(card2);
  printf("\n");
  printf("Card 3 is ");
  print_card(card3);
  printf("\n");
  printf("Card 4 is ");
  print_card(card4);
  printf("\n");
  printf("Starting tests with card numbers...\n");
  for (int i = 0; i < 52; i++) {
    printf("Card number %d is ", i);
    print_card(card_from_num(i));
    printf("\n");
   
}
  return 0;
}

  
