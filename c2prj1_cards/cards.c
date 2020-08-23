#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "cards.h"


void assert_card_valid(card_t c) {
  assert(c.value >= 2 && c.value <= VALUE_ACE);
  assert(c.suit >= SPADES && c.suit <= CLUBS);
}

const char * ranking_to_string(hand_ranking_t r) {
  char *str;
  switch (r) {
  case STRAIGHT_FLUSH: str = "STRAIGHT_FLUSH"; break;
  case FOUR_OF_A_KIND: str = "FOUR_OF_A_KIND"; break;
  case FULL_HOUSE: str = "FULL_HOUSE"; break;
  case FLUSH: str = "FLUSH"; break;
  case STRAIGHT: str = "STRAIGHT"; break;
  case THREE_OF_A_KIND: str = "THREE_OF_A_KIND"; break;
  case TWO_PAIR: str = "TWO_PAIR"; break;
  case PAIR: str = "PAIR"; break;
  case NOTHING: str = "NOTHING"; break;
  }
  return str;
}

char value_letter(card_t c) {
  char x;
  switch (c.value) {
  case 2: x = 50; break;
  case 3: x = 51; break;
  case 4: x = 52; break;
  case 5: x = 53; break;
  case 6: x = 54; break;
  case 7: x = 55; break;
  case 8: x = 56; break;
  case 9: x = 57; break;
  case 10: x = 48; break;
  case 11: x = 74; break;
  case 12: x = 81; break;
  case 13: x = 75; break;
  case 14: x = 65; break;
  }		      
		 
  return x;
}


char suit_letter(card_t c) {
  char x;
  switch (c.suit) {
  case SPADES: x = 115; break;
  case HEARTS: x = 104; break;
  case DIAMONDS: x = 100; break;
  case CLUBS: x = 99; break;
  case NUM_SUITS: printf("invalid suit. Exiting..."); exit (EXIT_FAILURE);
  }
  return x;
  
}
void print_card(card_t c) {
  char value = value_letter(c);
  char suit = suit_letter(c);
  printf("%c%c", value, suit);
}

card_t card_from_letters(char value_let, char suit_let) {
  card_t temp;
  unsigned x;
  suit_t y;
  if (((value_let >= 50 && value_let <= 57) || value_let == 48 || value_let == 74 || value_let == 81 || value_let == 75 || value_let == 65) && (suit_let == 99 || suit_let == 100 || suit_let == 104 || suit_let == 115)){
    switch (value_let){
      case 50: x = 2; break;
      case 51: x = 3; break;
      case 52: x = 4; break;
      case 53: x = 5; break;
      case 54: x = 6; break;
      case 55: x = 7; break;
      case 56: x = 8; break;
      case 57: x = 9; break;
      case 48: x = 10; break;
      case 74: x = 11; break;
      case 81: x = 12; break;
      case 75: x = 13; break;
      case 65: x = 14; break;
    }
    switch (suit_let){
      case 115: y = SPADES; break;
      case 104: y = HEARTS; break;
      case 100: y = DIAMONDS; break;
      case 99: y = CLUBS; break;
    }
    temp.value = x;
    temp.suit = y;
  }
    else {
      printf("Card entered is not valid. Exiting...");
      exit(EXIT_FAILURE);
    }
  
  return temp;
}

card_t card_from_num(unsigned c) {
  card_t temp;
  if (c >= 0 && c < 52) {
  temp.value = c % 13 + 2;
    if (c >= 0 && c < 13) {
    temp.suit = SPADES;
    }
    if (c >= 13 && c < 26) {
    temp.suit = HEARTS;
    }
    if (c >= 26 && c < 39) {
    temp.suit = DIAMONDS;
    }
    if (c >= 39 && c < 52) {
    temp.suit = CLUBS;
    }
  }
  
  return temp;
}
