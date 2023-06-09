#ifndef gameCtrl_H
#define gameCtrl_H
#include "deck.h"
#include "jogador.h"

typedef struct gameCtrl{
    int qtdJogadores;
    deck_t deck;
    jogador_t* jogadores;
    deck_t table;
} gameCtrl_t;

gameCtrl_t new_gameCtrl(int qtdJogadores);

void print_gameCtrl(gameCtrl_t gameCtrl);

// Adiciona uma carta na mesa
int put_card(gameCtrl_t gameCtrl, int value, int amount, int playerId);

// Compara o valor das cartas na mesa e retorna o vencedor
int check_round_winner(gameCtrl_t gameCtrl);

void destroy_gameCtrl(gameCtrl_t gameCtrl);

void distribute_cards(gameCtrl_t gameCtrl);

void print_jogadores(gameCtrl_t gameCtrl);

void fillDeck();

void distribuiCartas(int* deck, int* playerDeck, int);

int jogadorTemCarta(int* playerDeck);

// Checa se o jogador tem alguma jogada valida
int jogadorPodeJogar(int* playerDeck, char jog0, char jog1);

// Checa se a jogada escolhida pelo jogador eh valida
int jogadaEhValida(int* playerDeck, int jog0, int jog1, char numCards, char maxValue);

int convertCharToInt(char c);   


#endif
