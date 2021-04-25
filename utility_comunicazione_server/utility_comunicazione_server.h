#ifndef UTILITY_COMUNICAZIONE_SERVER_H
#define UTILITY_COMUNICAZIONE_SERVER_H
#include "../messaggio_client/messaggio_client.h"
#include <stdbool.h>
#include "../giocatore/giocatore.h"
#include "../locazione/locazione.h"
#include "../ostacolo/ostacolo.h"
#include <time.h>

Messaggio_client get_richiesta_dal_client(int client_socket);
bool get_account_dal_client(int client_socket, char *account);
bool get_password_dal_client(int client_socket, char *password);
void invia_errore_al_client(int client_socket);
void invia_successo_al_client(int client_socket);
bool invia_id_al_client(int client_socket, int id);
int get_id_dal_client(int client_socket);
bool invia_info_giocatori_al_client(int client_socket, Giocatore giocatori[], int size_giocatori);
bool invia_info_oggetti_al_client(int client_socket, Oggetto oggetti[], int size_oggetti);
bool invia_info_locazioni_al_client(int client_socket, Locazione locazioni[], int size_locazioni);
bool invia_info_ostacoli_al_client(int client_socket, Ostacolo ostacoli[], int size_ostacoli);
bool invia_ostacoli_visibili_al_client(int client_socket, bool ostacoli_visibili[], int size_ostacoli_visibili);
bool invia_punti_al_client(int client_socket, int punti[], int size_punti);
bool invia_ora_creazione_partita_al_client(int client_socket, time_t ora_creazione_partita);

#endif