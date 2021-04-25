#include "utility_comunicazione_server.h"
#include "../costanti/costanti.h"
#include "../messaggio_server/messaggio_server.h"
#include <unistd.h>
#include <stdio.h>

//FUNZIONI VISIBILI
Messaggio_client get_richiesta_dal_client(int client_socket)
{
    Messaggio_client messaggio = ERRORE_CLIENT;
    read(client_socket, &messaggio, sizeof(Messaggio_client));
    return messaggio;
}

bool get_account_dal_client(int client_socket, char *account)
{
    if(read(client_socket, account, SIZE_ACCOUNT * sizeof(char)) == SIZE_ACCOUNT * sizeof(char))
        return true;
    return false;
}

bool get_password_dal_client(int client_socket, char *password)
{
    if(read(client_socket, password, SIZE_PASSWORD * sizeof(char)) == SIZE_PASSWORD * sizeof(char)) 
        return true;
    return false;
}   

void invia_errore_al_client(int client_socket)
{
    Messaggio_server messaggio = ERRORE_SERVER;
    write(client_socket, &messaggio, sizeof(Messaggio_server));
}

void invia_successo_al_client(int client_socket)
{
    Messaggio_server messaggio = SUCCESSO_SERVER;
    write(client_socket, &messaggio, sizeof(Messaggio_server));
}

bool invia_id_al_client(int client_socket, int id)
{
    if(write(client_socket, &id, sizeof(int)) != sizeof(int))
        return false;
    return true;
}

int get_id_dal_client(int client_socket)
{
    int id = -1;
    read(client_socket, &id, sizeof(int));
    return id;
}

bool invia_info_giocatori_al_client(int client_socket, Giocatore giocatori[], int size_giocatori)
{
    if(write(client_socket, giocatori, sizeof(Giocatore) * size_giocatori) != (sizeof(Giocatore) * size_giocatori))
        return false;
    return true;
}

bool invia_info_oggetti_al_client(int client_socket, Oggetto oggetti[], int size_oggetti)
{
    if(write(client_socket, oggetti, sizeof(Oggetto) * size_oggetti) != (sizeof(Oggetto) * size_oggetti))
        return false;
    return true;
}

bool invia_info_locazioni_al_client(int client_socket, Locazione locazioni[], int size_locazioni)
{
    if(write(client_socket, locazioni, sizeof(Locazione) * size_locazioni) != sizeof(Locazione) * size_locazioni)
        return false;
    return true;
}

bool invia_info_ostacoli_al_client(int client_socket, Ostacolo ostacoli[], int size_ostacoli)
{
    if(write(client_socket, ostacoli, sizeof(Ostacolo) * size_ostacoli) != sizeof(Ostacolo) * size_ostacoli)
        return false;
    return true;
}

bool invia_ostacoli_visibili_al_client(int client_socket, bool ostacoli_visibili[], int size_ostacoli_visibili)
{
    if(write(client_socket, ostacoli_visibili, sizeof(bool) * size_ostacoli_visibili) != sizeof(bool) * size_ostacoli_visibili)
        return false;
    return true;
}

bool invia_punti_al_client(int client_socket, int punti[], int size_punti)
{
    if(write(client_socket, punti, sizeof(int) * size_punti) != sizeof(int) * size_punti)
        return false;
    return true;
}

bool invia_ora_creazione_partita_al_client(int client_socket, time_t ora_creazione_partita)
{
    if(write(client_socket, &ora_creazione_partita, sizeof(time_t)) != sizeof(time_t))
        return false;
    return true;
}
