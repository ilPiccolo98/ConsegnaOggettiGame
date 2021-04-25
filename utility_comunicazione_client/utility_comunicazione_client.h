#ifndef UTILITY_COMUNICAZIONE_CLIENT_H
#define UTILITY_COMUNICAZIONE_CLIENT_H
#include <stdbool.h>
#include <netinet/in.h>
#include "../messaggio_server/messaggio_server.h"
#include "../giocatore/giocatore.h"
#include "../locazione/locazione.h"
#include "../ostacolo/ostacolo.h"
#include <time.h>

bool invia_stringa_al_server(int server_socket, char *stringa, int size_stringa);
Messaggio_server get_messaggio_dal_server(int server_socket);
void gestisci_errore_comunicazione(int server_socket);
bool invia_crea_account_al_server(int server_socket);
int get_connessione_server(struct sockaddr_in *server_address);
bool invia_login_al_server(int server_socket);
int get_id_dal_server(int server_socket);
bool invia_logout_al_server(int server_socket);
bool invia_id_al_server(int server_socket, int id);
bool get_info_giocatori_dal_server(int server_socket, Giocatore giocatori[], int size_giocatori);
bool get_info_oggetti_dal_server(int server_socket, Oggetto oggetti[], int size_oggetti);
bool get_info_locazioni_dal_server(int server_socket, Locazione locazioni[], int size_locazioni);
bool get_info_ostacoli_dal_server(int server_socket, Ostacolo ostacoli[], int size_ostacoli);
bool get_ostacoli_visibili_dal_server(int server_socket, bool ostacoli_visibili[], int size_ostacoli_visibili);
bool get_punti_dal_server(int server_socket, int punti[], int size_punti);
bool get_ora_creazione_partita_dal_server(int server_socket, time_t *ora);
bool invia_aggiorna_info_al_server(int server_socket);
bool invia_muovi_su_al_server(int server_socket);
bool invia_muovi_giu_al_server(int server_socket);
bool invia_muovi_sinistra_al_server(int server_socket);
bool invia_muovi_destra_al_server(int server_socket);
bool invia_esci_dalla_partita_al_server(int server_socket);
bool invia_entra_in_partita_al_server(int server_socket);
bool invia_prendi_oggetto_al_server(int server_socket);
bool invia_lascia_oggetto_al_server(int server_socket);
bool invia_update_lite_info_al_server(int server_socket);
bool invia_fine_partita_al_server(int server_socket);

#endif