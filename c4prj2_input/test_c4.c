#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "future.h"
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "input.h"

struct empty_hands_tag {
    deck_t * hands;
    card_t ** cards;
};
typedef struct empty_hands_tag empty_hands_t;

void create_empty_hands(empty_hands_t * hands, size_t n) {
    hands->hands = malloc(n * sizeof(*(hands->hands)));
    for(size_t i = 0; i < n; i++) {
        hands->hands[i].cards = NULL;
        hands->hands[i].n_cards = 0;
    }
    hands->cards = malloc(5*n * sizeof(*(hands->cards)));
    for(size_t i = 0; i < 5*n; i++) {
        hands->cards[i] = NULL;
    }
    size_t curr_card = 0;
    for (size_t i = 0; i < n; i++){
        for (size_t count = 0; count < 5; count++) {
            hands->cards[curr_card] = add_empty_card(&(hands->hands[i]));
            curr_card++;
        }
    }
    return;       
}

void create_hand_n(deck_t * hand, size_t n) {
    for (size_t i = 0; i < n; i++){
        unsigned r = random() % 51;
        card_t c = card_from_num(r);
        add_card_to(hand, c);
    }
    print_hand(hand);
    fprintf(stdout,"\nA mão tem %ld cartas \n", hand->n_cards);
    return;
}

void print_info (deck_t * hand, size_t id) {
    fprintf(stdout, "A mão %ld tem as seguintes %ld cartas: ", id, hand->n_cards);
    print_hand(hand);
    fprintf(stdout,"\n");
    return;
}

void print_runtest(char * text) {
    printf("----------------------------------------------\n");
    printf("-             Running test %s                 -\n", text);
    printf("----------------------------------------------\n");
    printf("\n");
}

void test1(void) {

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
fprintf(stdout, "----------------------------------------------------------------------------------------------------------------------------\n");
fprintf(stdout, "Agora, vamos adicionar cartas vazias às mãos 1, 2 e 3....\n");

card_t * unk_1 = add_empty_card(hand1);
card_t * unk_2 = add_empty_card(hand2);
card_t * unk_3 = add_empty_card(hand3);

print_card(*unk_1);
fprintf(stdout,"\n");
print_card(*unk_2);
fprintf(stdout,"\n");
print_card(*unk_3);
fprintf(stdout,"\n");
fprintf(stdout, "Feito!\n\n");
fprintf(stdout, "Verificando se há cartas desconhecidas nas mãos...\n");
print_info(hand1, 1);
print_info(hand2, 2);
print_info(hand3, 3);
fprintf(stdout,"\n");

fprintf(stdout, "Digamos que a carta desconhecida da mão 1 é a mesma da mão 2, mas é diferente daquela da mão 3. Vamos testar as funções que definem estas cartas: \n\n");

fprintf(stdout, "Criando array de cartas desconhecidas... \n");
future_cards_t * fc = malloc(sizeof(*fc));
fc->decks = NULL;
fc->n_decks = 0;
add_future_card(fc, 0, unk_1);
fprintf(stdout, "Carta 1 adicionada\n");
add_future_card(fc, 0, unk_2);
fprintf(stdout, "Carta 2 adicionada\n");
add_future_card(fc, 1, unk_3);
fprintf(stdout, "Carta 3 adicionada\n");

fprintf(stdout, "Cartas desconhecidas referenciadas no array \n");
fprintf(stdout, "Defindo cartas desconhecidas... \n");
future_cards_from_deck(test_deck, fc);
fprintf(stdout, "Feito!\n\n");

fprintf(stdout, "Verificando as mãos novamente...\n");
print_info(hand1, 1);
print_info(hand2, 2);
print_info(hand3, 3);
fprintf(stdout,"\n\n");


fprintf(stdout, "Liberando memória alocada no Heap....\n");
free_deck(hand1);
free_deck(hand2);
free_deck(hand3);
free_deck(test_deck);

for(size_t i = 0; i < fc->n_decks; i++) {
    printf("Liberado fc->deck[%ld].cards\n", i);
    free(fc->decks[i].cards);
}
free (fc->decks);
free (fc);

fprintf(stdout, "Teste 1 completo\n");

return;
}

void test2(void) {
    fprintf(stdout,"Criando 4 mãos vazias\n");
    fprintf(stdout,"\n");
    empty_hands_t * h = malloc(sizeof(*h));
    create_empty_hands(h, 4);
    for(int i = 0; i < 4; i++){
        fprintf(stdout,"Mão %d: \n", i);
        print_hand(&(h->hands[i]));
        fprintf(stdout,"\n");
    }

    fprintf(stdout,"\n");
    fprintf(stdout,"Criando um baralho de 52 cartas...\n");
    deck_t * deck = malloc(sizeof(*deck));
    deck->cards = NULL;
    deck->n_cards = 0;
    for(unsigned i = 0; i < 52; i++){
        card_t c = card_from_num(i);
        add_card_to(deck, c);
    }
    print_hand(deck);
    fprintf(stdout,"\n");
    fprintf(stdout,"Embaralhando 100 vezes... ");

    for (unsigned i = 0; i < 100; i++) {
      shuffle(deck);
    }

    fprintf(stdout," Feito! O resultado é:\n");
    print_hand(deck);
    fprintf(stdout,"\n");

    fprintf(stdout, "Criando array para as cartas desconhecidas... \n");
    future_cards_t * fc = malloc(sizeof(*fc));
    fc->decks = NULL;
    fc->n_decks = 0;

    fprintf(stdout, "Distribuindo as cartas pelo array...\n");
    //int index = 0;
    for(size_t i = 0; i < 20; i++) {
        //if (index > 5) {index = 0;};
        add_future_card(fc, i, h->cards[i]);
        //index++;
    }
    fprintf(stdout, "Defindo cartas desconhecidas... \n");
    future_cards_from_deck(deck, fc);
    fprintf(stdout, "Verificando as mãos: \n\n");

    for(int i = 0; i < 4; i++){
        fprintf(stdout,"Mão %d: \n", i);
        print_hand(&(h->hands[i]));
        fprintf(stdout,"\n");
    }

    fprintf(stdout,"\n");
    fprintf(stdout, "Liberando memória alocada no Heap....\n\n");

    for(size_t i = 0; i < 4; i++) {
        //printf("Liberado mão %ld \n", i);
        free(h->hands[i].cards);
    }
    for(size_t i = 0; i < 20; i++) {
        //printf("Liberado carta %ld \n", i);
        free(h->cards[i]);
    }
    free(h->hands);
    free(h->cards);
    free(h);

    for(size_t i = 0; i < fc->n_decks; i++) {
        //printf("Liberado fc->deck[%ld].cards\n", i);
        free(fc->decks[i].cards);
    }
    free (fc->decks);
    free (fc);
    free_deck(deck);


    fprintf(stdout,"\n");
    fprintf(stdout, "Teste 2 completo\n");

}

void test3 (char * filename) {
    fprintf(stdout, "Abrindo arquivo %s\n", filename);
    FILE * input = fopen(filename, "r");
    if (input == NULL) {
        fprintf(stderr, "Falha ao abrir o arquivo %s. O teste será encerrado\n", filename);
        exit(EXIT_FAILURE);
    }

    fprintf(stdout, "Definindo e inicializando variáveis...\n");
    size_t n_hands = 0;
    future_cards_t * fc = malloc(sizeof(*fc));
    fc->decks= NULL;
    fc->n_decks= 0;
    deck_t ** decks = NULL;

    fprintf(stdout, "Lendo arquivo %s...\n", filename);
    decks = read_input(input, &n_hands, fc);
    fprintf(stdout, "%s foi lido com sucesso!\n\nVerificando se as mãos foram registradas corretamente...\n\n", filename);
    fprintf(stdout, "Criando um baralho sem as cartas já existentes...\n");
    deck_t * deck = build_remaining_deck(decks, n_hands);
    shuffle(deck);
    print_hand(deck); printf("\n");
    fprintf(stdout, "\nVerificando fc->decks\n");
    for(size_t i = 0; i < n_hands; i++) {
        print_info(fc->decks, i);
    }
    fprintf(stdout, "Definindo cartas desconhecidas\n\n");
    future_cards_from_deck(deck, fc);
    fprintf(stdout, "\nVerificando fc->decks\n");
     for(size_t i = 0; i < n_hands; i++) {
        print_info(fc->decks, i);
    }
    for(size_t i = 0; i < n_hands; i++) {
        print_info(decks[i], i);
    }
    fprintf(stdout, "\nLiberando memória alocada no Heap....\n\n");

    if (fclose(input) != 0) { fprintf(stderr, "Erro ao fechar arquivo %s\n", filename);}

    for(size_t i = 0; i < fc->n_decks; i++) {
        free(fc->decks[i].cards);
    }
    free (fc->decks);
    free (fc);
    for(size_t i = 0; i < n_hands; i++) {
        free_deck(decks[i]);
    }
    free_deck(deck);

    return;
}

int main(int argc, char ** argv) {
    print_runtest("1");
    test1();
    print_runtest("2");
    test2();
    fprintf(stdout,"\n");
    if (argc != 2) {
        fprintf(stdout, "O teste 3 necessita de uma lista de mãos no formato *.txt \n");
        fprintf(stdout, "O teste 3 será pulado\n");
    }
    else {
        print_runtest("3");
        test3(argv[1]);
        fprintf(stdout, "\n\nTodos os testes concluídos!!\n");
    }

return EXIT_SUCCESS;
}