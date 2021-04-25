#ifndef GAME_CLIENT_H
#define GAME_CLIENT_H
#include "../costanti/costanti.h"
#include <netinet/in.h>
#include "../mappa/mappa.h"
#include "../giocatore/giocatore.h"
#include "../locazione/locazione.h"
#include <stdbool.h>
#include "../ostacolo/ostacolo.h"

typedef struct Game_client
{
    struct sockaddr_in *server_address;
    int id_giocatore;
    Mappa mappa;
    Giocatore giocatori[MAX_CLIENTS];
    Oggetto oggetti[NUMERO_OGGETTI];
    Locazione locazioni[NUMERO_LOCAZIONI];
    Ostacolo ostacoli[NUMERO_OSTACOLI];
    int punti[MAX_CLIENTS];
    bool ostacoli_visibili[NUMERO_OSTACOLI];
    bool run_game;
    time_t ora_creazione_partita;
}
Game_client;

void init_game_client(Game_client *game, struct sockaddr_in *server_address, int id_giocatore);
void esegui_game_client(Game_client *game);

#endif 