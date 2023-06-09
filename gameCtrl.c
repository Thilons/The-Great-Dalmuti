#include "gameCtrl.h"

gameCtrl_t new_gameCtrl(int qtdJogadores){
    gameCtrl_t gameCtrl;

    gameCtrl.qtdJogadores = qtdJogadores;
    gameCtrl.jogadores = malloc(sizeof(jogador_t) * qtdJogadores);
    
    for(int i = 0; i < qtdJogadores; i++){
        gameCtrl.jogadores[i] = new_jogador(i+1);
    }

    gameCtrl.deck = new_deck();
    gameCtrl.table = new_table();

    return gameCtrl;
}


void print_gameCtrl(gameCtrl_t gameCtrl){
    print_deck(gameCtrl.deck);
}


void destroy_gameCtrl(gameCtrl_t gameCtrl){
    destroy_deck(gameCtrl.deck);
}

// Distribui as cartas aleatoriamente para os jogadores
void distribute_cards(gameCtrl_t gameCtrl) {
    int qtdCartas = gameCtrl.deck.size;
    int qtdJogadores = gameCtrl.qtdJogadores;
    int qtdCartasPorJogador = qtdCartas / qtdJogadores;

    for (int i = 0; i < gameCtrl.qtdJogadores; i++) {
        int cartasDistribuidas = 0;  // Movido para dentro do loop for

        while (cartasDistribuidas < qtdCartasPorJogador) {  // Corrigido para < em vez de <=
            int cardType = rand() % 13;

            while (gameCtrl.deck.cards[cardType].amount <= 0) {
                cardType = rand() % 13;
            }

            gameCtrl.jogadores[i].deck.cards[cardType].value = cardType;
            gameCtrl.jogadores[i].deck.cards[cardType].amount++;
            gameCtrl.jogadores[i].deck.size++;
            gameCtrl.deck.cards[cardType].amount--;
            cartasDistribuidas++;
            gameCtrl.deck.size--;
        }
    }

}

void print_jogadores(gameCtrl_t gameCtrl){
    for(int i = 0; i < gameCtrl.qtdJogadores; i++){
        print_jogador(gameCtrl.jogadores[i]);
    }
}

int put_card(gameCtrl_t gameCtrl, int value, int amount, int playerId){

    if((playerId == 1)||((playerId > 0) && (amount >= gameCtrl.table.cards[playerId-1].amount) && (value >= gameCtrl.table.cards[playerId-1].value))){
        gameCtrl.table.cards[playerId].amount = amount;
        gameCtrl.table.cards[playerId].value = value;
        return 1;
    }

    return 0;

}

int check_round_winner(gameCtrl_t gameCtrl){
    int winner = 0;
    
    for(int i = 1; i <= gameCtrl.qtdJogadores; i++){
        if(gameCtrl.table.cards[i].value != -1)
            winner = i;
    }

    return winner;
}
 
void fillDeck(int* deck){
    for(int i = 0; i < CARD_MAX_VALUE; i++){
        deck[i] = i+1;
    }

    deck[CARD_MAX_VALUE] = 2;
}

void distribuiCartas(int* deck, int* playerDeck, int numPlayers){
    int aux;
    int cartasPorJogador = DECK_SIZE / numPlayers;

    // Reseta o vetor de cartas do jogador
    for(int i = 0; i <= CARD_MAX_VALUE; i++){
        playerDeck[i] = 0;
    }

    // Distribui as cartas aleatoriamente
    for(int i = 0; i < cartasPorJogador; i++){
        aux = rand() % (CARD_MAX_VALUE + 1);
        while(deck[aux] == 0){
            aux = rand() % CARD_MAX_VALUE + 1;
        }
        playerDeck[aux]++;
        deck[aux]--;
    }
}

int jogadorTemCarta(int* playerDeck){
    for(int i = 0; i <= CARD_MAX_VALUE; i++){
        if(playerDeck[i] > 0){
            return 1;
        }
    }

    return 0;
}

int jogadorPodeJogar(int* playerDeck, char jog0, char jog1){
    int quantidade = jog0;
    int valor = jog1;
    
    for(int i = valor-1; i > 1; i--){
        
        if(playerDeck[i-1] + playerDeck[CARD_MAX_VALUE] >= quantidade){
            return 1;
        }
    }

    return 0;
}
                                                                    //basicos
int jogadaEhValida(int* playerDeck, int jog0, int jog1, char numCards, char maxValue){
    //int quantidade = jog0;
    //int valor = jog1;

    if(jog1>=maxValue)
        return 0;

    if(jog0==0||playerDeck[jog1-1]==0){
        return 0;
    }

    int aux;

    if(playerDeck[jog1-1]>=jog0){

        playerDeck[jog1-1]-=jog0;  
        return 1;        
    }else if(playerDeck[jog1-1]+playerDeck[12]>=jog0 && jog1-1!=12){
        aux=jog0-playerDeck[jog1-1];
        playerDeck[jog1-1]=0;  
        playerDeck[12]-=aux;
        return 1;        

    }   


    return 0;
}

int convertCharToInt(char c){
    int i = c - '0';
    return i;
}
