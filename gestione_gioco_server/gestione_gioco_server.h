#ifndef GESTIONE_GIOCO_SERVER_H
#define GESTIONE_GIOCO_SERVER_H
#include "../costanti/costanti.h"
#include "../mappa/mappa.h"
#include "../giocatore/giocatore.h"
#include "../costanti/costanti.h"
#include "../locazione/locazione.h"
#include "../ostacolo/ostacolo.h"
#include <stdbool.h>
#include <time.h>

typedef struct Gestione_gioco_server
{
    Mappa mappa;
    Giocatore giocatori[MAX_CLIENTS];
    Oggetto oggetti[NUMERO_OGGETTI];
    Locazione locazioni[NUMERO_LOCAZIONI];
    Ostacolo ostacoli[NUMERO_OSTACOLI];
    bool ostacoli_visibili_giocatore_uno[NUMERO_OSTACOLI];
    bool ostacoli_visibili_giocatore_due[NUMERO_OSTACOLI];
    bool ostacoli_visibili_giocatore_tre[NUMERO_OSTACOLI];
    int punti[MAX_CLIENTS];
    time_t ultima_richiesta[MAX_CLIENTS];
    time_t ora_creazione_partita;
}   
Gestione_gioco_server;

void init_gestione_gioco_server(Gestione_gioco_server *gioco);
int set_giocatore_connesso(Gestione_gioco_server *gioco, const char *account);
void set_giocatore_disconnesso(Gestione_gioco_server *gioco, int id);
bool is_giocatore_connesso_by_account(Gestione_gioco_server *gioco, const char *account);
bool is_giocatore_in_gioco_by_account(Gestione_gioco_server *gioco, const char *account);
bool is_giocatore_connesso_by_id(Gestione_gioco_server *gioco, int id);
bool is_giocatore_in_gioco_by_id(Gestione_gioco_server *gioco, int id);
const char *get_account_by_id(Gestione_gioco_server *gioco, int id);
void set_ultima_richiesta_al_tempo_corrente(Gestione_gioco_server *gioco, int id);
time_t get_ultima_richiesta(Gestione_gioco_server *gioco, int id);
void kick_off_account_disconnessi(Gestione_gioco_server *gioco);
void aggiungi_giocatore_in_partita(Gestione_gioco_server *gioco, int id);
void rimuovi_giocatore_dalla_partita(Gestione_gioco_server *gioco, int id);
void muovi_giocatore_su(Gestione_gioco_server *gioco, int id);
void muovi_giocatore_giu(Gestione_gioco_server *gioco, int id);
void muovi_giocatore_sinistra(Gestione_gioco_server *gioco, int id);
void muovi_giocatore_destra(Gestione_gioco_server *gioco, int id);
void prendi_oggetto_gestione_gioco_server(Gestione_gioco_server *gioco, int id);
void lascia_oggetto_gestione_gioco_server(Gestione_gioco_server *gioco, int id, const char *ip_address, const char *hostname);
void set_giocatori_tutti_non_in_gioco(Gestione_gioco_server *gioco);

#endif