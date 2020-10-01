#include "eval.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int card_ptr_comp(const void * vp1, const void * vp2) { // compara duas cartas
  const card_t * const *cp1 = vp1; // converting pointer type from const void pointer to a const card_t pointer whose adress cannot be changed (as vp1's adress is also a const).
  const card_t * const *cp2 = vp2;   
  size_t v_comp = (**cp1).value - (**cp2).value; //subtrai valor da carta 1 pelo valor das carta 2 para ver quem é maior
  if (v_comp != 0) { //se as cartas não tiverem o mesmo valor
    return -1 * v_comp; // queremos ordenar de forma decrescente, mas a função qsort que será usada posteriormente ordena de forma crescente. Por isso, invertemos o sinal do return value 
  }
  else {
    size_t s_comp = (**cp1).suit - (**cp2).suit; // subtrai o naipe da carta 1 do naipe da carta 2 para ver quem é maior 
    if (s_comp != 0) { // se as cartas tiverem o mesmo valor, compare os naipes 
    return -1 * s_comp;
    }
    else { // se as cartas forem iguais 
      return 0;
    }
  }
}

suit_t flush_suit(deck_t * hand) { // verifica se há pelo menos cinco cartas do mesmo naipe (flush) e, caso haja, retorna o naipe. Se não houver, retorna NUM_SUITS
  int c_spades = 0, c_hearts = 0, c_diamonds = 0, c_clubs = 0;
  for (int i = 0; i < hand->n_cards; i++) {
    switch (hand->cards[i]->suit) {
    case SPADES: c_spades++; break;
    case HEARTS: c_hearts++; break;
    case DIAMONDS: c_diamonds++; break;
    case CLUBS: c_clubs ++; break;
    default: break;
    }
  }
  if (c_spades >= 5) {
    return SPADES;
  }
  else if (c_hearts >= 5) {
    return HEARTS;
  }
  else if (c_diamonds >= 5) {
    return DIAMONDS;
  }
  else if (c_clubs >= 5) {
    return CLUBS;
  }
  else {
    return NUM_SUITS;
  }
}

unsigned get_largest_element(unsigned * arr, size_t n) { // pega maior elemento em um array
  unsigned current_match = arr[0];
  unsigned best_match = arr[0];
  for (size_t i = 1; i < n; i++){
    const unsigned *p1 = &arr[i];
    if (*p1 > current_match){
      current_match = *p1;
      if (current_match > best_match){
	best_match = current_match;
      }
    }
  }
       
  return best_match;
}

size_t get_match_index(unsigned * match_counts, size_t n,unsigned n_of_akind){ //pega o índice do array em que está a primeira carta de uma série de cartas iguais (dupla, trio, quadra). o N dá série é o parametro n_of_a_kind
  for (size_t i = 0; i < n; i++){
      unsigned const *p1 = &match_counts[i];
      if (*p1 == n_of_akind) {
	return i; 
    }      
  }
  printf("n_of_a_kind is not present in match_counts. Aborting...");
  exit(EXIT_FAILURE);
}

size_t find_secondary_pair( deck_t * hand,
			     unsigned * match_counts,
			     size_t match_idx) {
  for (size_t i = 0; i < hand->n_cards; i++) {
    if (hand->cards[i]->value != hand->cards[match_idx]->value) { // se o valor da carta na posição i for diferente do valor da carta que já foi identificada como parte de uma sequência
      if (match_counts[i] > 1) { // se houver n_of_akind maior do que 1 na posição i
	return i; //indice = i
      }
    }
  }
  return -1;
}

int is_n_lenght_straight_at(deck_t *hand, size_t index, int n); //declarando a existencia da função is_n_lenght_straight_at, que ainda não foi definida

int is_ace_low_straight_at (deck_t *hand, size_t index) {
  if (hand->cards[index]->value == 14) {   
    for (size_t i = 0; i < hand->n_cards; i++){ //procure a primeira carta de valor 5 na mão
      if (hand->cards[i]->value == 5) {
	      if (is_n_lenght_straight_at(hand, i, 4) == 1) { //verifique se existe um straight de 4 cartas na nova mão
	        return -1; // se houver
      	}
      }  
    } // repita para todos os cincos que encontrar na mão
  }
  return 0;
}

int is_n_lenght_straight_at(deck_t *hand, size_t index, int n) {
  if (n == 1) { // se houver n cartas com valor seguido
      return 1; // straight de tamanho n    
    }
  else if (index == hand->n_cards - 1) { //se tivermos chegado ao fim do array sem ter passado por n = 1
    return 0; // não tem straight de tamanho n
    }
  else if (hand->cards[index]->value == hand->cards[index+1]->value +1) { //se o valor de hand->cards[index] for exatamente 1 a mais do que o valor da carta seguinte 
    return is_n_lenght_straight_at(hand, index+1, n-1);
  }
  else if  (hand->cards[index]->value == hand->cards[index+1]->value) { // se o valor de hand->cards[index] for igual ao da carta seguinte
    return is_n_lenght_straight_at(hand, index+1, n);
  }
  return 0; // não tem straight de tamanho n
}
  

int is_straight_at(deck_t * hand, size_t index, suit_t fs) {
  int straight = is_n_lenght_straight_at(hand, index, 5);
  if (hand->cards[index]->value == 14 && straight == 0) {
    straight = is_ace_low_straight_at(hand, index);
  }  
  if (fs == NUM_SUITS) { // proura por qqr straight
    return straight;
  }
  else { // procura por um straight flush 
    if (straight  == -1 && hand->cards[index]->suit == fs) { // se houver um ace low straight   
      int count = 0;
      for (size_t i = index; i < hand->n_cards; i++) {
	      unsigned curr_value = hand->cards[i]->value;
	        if ((curr_value == 14 || curr_value == 5 || curr_value == 4 || curr_value == 3 || curr_value == 2) && hand->cards[i]->suit == fs) {
	          count ++;
	        }
      }
      if (count >= 5) {
	return -1; //existe um ace low straight flush
      }
      else {
	return 0; //não existe um ace low straight flush	     
      }
    }
    else if (straight == 1) { // se houver um straight comum
      int count = 0;
      unsigned ref = hand->cards[index]->value; //referencia para encontrar cartas do straight no loop por valor
      if (hand->cards[index]->suit != fs){
	return 0;
      }
      else {	
	for (size_t i = index; i < hand->n_cards; i++) {
	  unsigned curr_value = hand->cards[i]->value;
	  if ((ref == curr_value || ref == curr_value +1 || ref == curr_value +2 || ref == curr_value +3 || ref == curr_value +4) && hand->cards[i]->suit == fs) {
	    count++;  
	  }
	}
	if (count == 5) {
	  return 1; //existe um straight flush comum
	}
	else {
	  return 0; //não existe um straight flush comum	
	}
      }
    }
    else {
      return 0;      
    }
  }
}
hand_eval_t build_hand_from_match(deck_t * hand, unsigned n, hand_ranking_t what, size_t idx) {
  hand_eval_t ans; //variável que contém melhor mão de 5 cartas do tipo N of a Kind e descrição do ranking
  ans.ranking = what;
  if (ans.ranking == NOTHING) {
    for (unsigned i = 0; i < 5; i++) {
      ans.cards[i] = hand->cards[i];
    }
  }
  else { 
    for (unsigned i = 0; i < n; i++){
      ans.cards[i] = hand->cards[idx+i];
      }
    if (n == 5) {
      return ans;
    }
    else { 
      unsigned remaining = 5 - n;
      unsigned tmp_idx = 0;
        for (unsigned i = 0; i < hand->n_cards; i++) {
          if (remaining == 0) {
            break;
          }    
          else if (i < idx || i >= (idx+n)) {
	          ans.cards[n+tmp_idx] = hand->cards[i];
	          tmp_idx++;
            remaining--;
	        }
        }
     }
  }
  return ans;
}


int compare_hands(deck_t * hand1, deck_t * hand2) {
  qsort(hand1->cards, hand1->n_cards, sizeof(card_t *), card_ptr_comp); //sorting hands
  qsort(hand2->cards, hand2->n_cards, sizeof(card_t *), card_ptr_comp);
  hand_eval_t eval_1 = evaluate_hand(hand1);
  hand_eval_t eval_2 = evaluate_hand(hand2);
  if (eval_1.ranking != eval_2.ranking) {
    if (eval_1.ranking < eval_2.ranking) {
      return 1;
    }
    else {
      return -1;
    }
  }
  else {
    for (int i = 0; i < 5; i++) {
      if (eval_1.cards[i]->value != eval_2.cards[i]->value) {
	      if (eval_1.cards[i]->value > eval_2.cards[i]->value) {
	        return 1;
	      }
	      else {
	        return -1;
	      }
      }
    }
    return 0;
  }
}

unsigned * get_match_counts(deck_t * hand) {
  unsigned * match_counts = malloc(hand->n_cards * sizeof(match_counts));
  for (size_t i = 0; i < hand->n_cards; i++){
    unsigned count = 0;
    for (size_t j = 0; j < hand->n_cards; j++) {
      if (hand->cards[i]->value == hand->cards[j]->value){
	      count++;
      }
    }
    match_counts[i] = count;
  }
  return match_counts;
}

// We provide the below functions.  You do NOT need to modify them
// In fact, you should not modify them!

//This function copies a straight starting at index "ind" from deck "from".
//This copies "count" cards (typically 5).
//into the card array "to"
//if "fs" is NUM_SUITS, then suits are ignored.
//if "fs" is any other value, a straight flush (of that suit) is copied.
void copy_straight(card_t ** to, deck_t *from, size_t ind, suit_t fs, size_t count) {
  assert(fs == NUM_SUITS || from->cards[ind]->suit == fs);
  unsigned nextv = from->cards[ind]->value;
  size_t to_ind = 0;
  while (count > 0) {
    assert(ind < from->n_cards);
    assert(nextv >= 2);
    assert(to_ind <5);
    if (from->cards[ind]->value == nextv &&
	(fs == NUM_SUITS || from->cards[ind]->suit == fs)){
      to[to_ind] = from->cards[ind];
      to_ind++;
      count--;
      nextv--;
    }
    ind++;
  }
}


//This looks for a straight (or straight flush if "fs" is not NUM_SUITS)
// in "hand".  It calls the student's is_straight_at for each possible
// index to do the work of detecting the straight.
// If one is found, copy_straight is used to copy the cards into
// "ans".
int find_straight(deck_t * hand, suit_t fs, hand_eval_t * ans) {
  if (hand->n_cards < 5){
    return 0;
  }
  for(size_t i = 0; i <= hand->n_cards -5; i++) {
    int x = is_straight_at(hand, i, fs);
    if (x != 0){
      if (x < 0) { //ace low straight
	assert(hand->cards[i]->value == VALUE_ACE &&
	       (fs == NUM_SUITS || hand->cards[i]->suit == fs));
	ans->cards[4] = hand->cards[i];
	size_t cpind = i+1;
	while(hand->cards[cpind]->value != 5 ||
	      !(fs==NUM_SUITS || hand->cards[cpind]->suit ==fs)){
	  cpind++;
	  assert(cpind < hand->n_cards);
	}
	copy_straight(ans->cards, hand, cpind, fs,4) ;
      }
      else {
	copy_straight(ans->cards, hand, i, fs,5);
      }
      return 1;
    }
  }
  return 0;
}


//This function puts all the hand evaluation logic together.
//This function is longer than we generally like to make functions,
//and is thus not so great for readability :(
hand_eval_t evaluate_hand(deck_t * hand) {
  suit_t fs = flush_suit(hand);
  hand_eval_t ans;
  if (fs != NUM_SUITS) {
    if(find_straight(hand, fs, &ans)) {
      ans.ranking = STRAIGHT_FLUSH;
      return ans;
    }
  }
  unsigned * match_counts = get_match_counts(hand);
  unsigned n_of_a_kind = get_largest_element(match_counts, hand->n_cards);
  assert(n_of_a_kind <= 4);
  size_t match_idx = get_match_index(match_counts, hand->n_cards, n_of_a_kind);
  ssize_t other_pair_idx = find_secondary_pair(hand, match_counts, match_idx);
  free(match_counts);
  if (n_of_a_kind == 4) { //4 of a kind
    return build_hand_from_match(hand, 4, FOUR_OF_A_KIND, match_idx);
  }
  else if (n_of_a_kind == 3 && other_pair_idx >= 0) {     //full house
    ans = build_hand_from_match(hand, 3, FULL_HOUSE, match_idx);
    ans.cards[3] = hand->cards[other_pair_idx];
    ans.cards[4] = hand->cards[other_pair_idx+1];
    return ans;
  }
  else if(fs != NUM_SUITS) { //flush
    ans.ranking = FLUSH;
    size_t copy_idx = 0;
    for(size_t i = 0; i < hand->n_cards;i++) {
      if (hand->cards[i]->suit == fs){
	ans.cards[copy_idx] = hand->cards[i];
	copy_idx++;
	if (copy_idx >=5){
	  break;
	}
      }
    }
    return ans;
  }
  else if(find_straight(hand,NUM_SUITS, &ans)) {     //straight
    ans.ranking = STRAIGHT;
    return ans;
  }
  else if (n_of_a_kind == 3) { //3 of a kind
    return build_hand_from_match(hand, 3, THREE_OF_A_KIND, match_idx);
  }
  else if (other_pair_idx >=0) {     //two pair
    assert(n_of_a_kind ==2);
    ans = build_hand_from_match(hand, 2, TWO_PAIR, match_idx);
    ans.cards[2] = hand->cards[other_pair_idx];
    ans.cards[3] = hand->cards[other_pair_idx + 1];
    if (match_idx > 0) {
      ans.cards[4] = hand->cards[0];
    }
    else if (other_pair_idx > 2) {  //if match_idx is 0, first pair is in 01
      //if other_pair_idx > 2, then, e.g. A A K Q Q
      ans.cards[4] = hand->cards[2];
    }
    else {       //e.g., A A K K Q
      ans.cards[4] = hand->cards[4];
    }
    return ans;
  }
  else if (n_of_a_kind == 2) {
    return build_hand_from_match(hand, 2, PAIR, match_idx);
  }
  return build_hand_from_match(hand, 0, NOTHING, 0);
}
