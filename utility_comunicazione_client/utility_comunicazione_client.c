#include "utility_comunicazione_client.h"
#include "../messaggio_client/messaggio_client.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "../utility/utility.h"
#include "../console_utility/console_utility.h"
#include "../colori/colori.h"

//FUNZIONI VISIBILI
bool invia_stringa_al_server(int server_socket, char *stringa, int size_stringa)
{
    if(write(server_socket, stringa, size_stringa * sizeof(char)) != size_stringa * sizeof(char))
        return false;
    return true;
}

Messaggio_server get_messaggio_dal_server(int server_socket)
{
    Messaggio_server richiesta = ERRORE_SERVER;
    read(server_socket, &richiesta, sizeof(Messaggio_server));
    return richiesta;
}

void gestisci_errore_comunicazione(int server_socket)
{
    close(server_socket);
    pulisci_console();
    set_colore_console(ROSSO);
    stampa_aspetta("Errore di comunicazione con il server");
    turn_on_echo();
    mostra_cursore();
    exit(1);
}

bool invia_crea_account_al_server(int server_socket)
{
    Messaggio_client richiesta = CREA_ACCOUNT_CLIENT;
    if(write(server_socket, &richiesta, sizeof(Messaggio_client)) != sizeof(Messaggio_client))
        return false;
    return true;
}

int get_connessione_server(struct sockaddr_in *server_address)
{
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(server_socket == -1 || connect(server_socket, (struct sockaddr*)server_address, sizeof(*(server_address))) == -1)
    {
        pulisci_console();
        stampa_aspetta("Errore di comunicazione con il server");
        turn_on_echo();
        mostra_cursore();
        exit(1);
    }
    return server_socket;
}

bool invia_login_al_server(int server_socket)
{
    Messaggio_client richiesta = LOGIN_CLIENT;
    if(write(server_socket, &richiesta, sizeof(Messaggio_client)) != sizeof(Messaggio_client))
        return false;
    return true;
}

int get_id_dal_server(int server_socket)
{
    int id = -1;
    read(server_socket, &id, sizeof(int));
    return id;
}

bool invia_logout_al_server(int server_socket)
{
    Messaggio_client richiesta = LOGOUT_CLIENT;
    if(write(server_socket, &richiesta, sizeof(Messaggio_client)) != sizeof(Messaggio_client))
        return false;
    return true;
}

bool invia_id_al_server(int server_socket, int id)
{
    if(write(server_socket, &id, sizeof(int)) != sizeof(int))
        return false;
    return true;
}

bool get_info_giocatori_dal_server(int server_socket, Giocatore *giocatori, int size_giocatori)
{
    if(read(server_socket, giocatori, sizeof(Giocatore) * size_giocatori) != (sizeof(Giocatore) * size_giocatori))
        return false;
    return true;
}

bool get_info_oggetti_dal_server(int server_socket, Oggetto oggetti[], int size_oggetti)
{
    if(read(server_socket, oggetti, sizeof(Oggetto) * size_oggetti) != (sizeof(Oggetto) * size_oggetti))
        return false;
    return true;
}

bool get_info_locazioni_dal_server(int server_socket, Locazione locazioni[], int size_locazioni)
{
    if(read(server_socket, locazioni, sizeof(Locazione) * size_locazioni) != sizeof(Locazione) * size_locazioni)
        return false;
    return true;
}

bool get_info_ostacoli_dal_server(int server_socket, Ostacolo ostacoli[], int size_ostacoli)
{
    if(read(server_socket, ostacoli, sizeof(Ostacolo) * size_ostacoli) != sizeof(Ostacolo) * size_ostacoli)
        return false;
    return true;
}

bool get_ostacoli_visibili_dal_server(int server_socket, bool ostacoli_visibili[], int size_ostacoli_visibili)
{
    if(read(server_socket, ostacoli_visibili, sizeof(bool) * size_ostacoli_visibili) != sizeof(bool) * size_ostacoli_visibili)
        return false;
    return true;
}

bool get_punti_dal_server(int server_socket, int punti[], int size_punti)
{
    if(read(server_socket, punti, sizeof(int) * size_punti) != sizeof(int) * size_punti)
        return false;
    return true;
}

bool get_ora_creazione_partita_dal_server(int server_socket, time_t *ora)
{
    if(read(server_socket, ora, sizeof(time_t)) != sizeof(time_t))
        return false;
    return true;
}

bool invia_aggiorna_info_al_server(int server_socket)
{
    Messaggio_client richiesta = AGGIORNA_INFO_CLIENT;
    if(write(server_socket, &richiesta, sizeof(Messaggio_client)) != sizeof(Messaggio_client))
        return false;
    return true;
}

bool invia_muovi_su_al_server(int server_socket)
{
    Messaggio_client richiesta = MUOVI_SU_CLIENT;
    if(write(server_socket, &richiesta, sizeof(Messaggio_client)) != sizeof(Messaggio_client))
        return false;
    return true;
}

bool invia_muovi_giu_al_server(int server_socket)
{
    Messaggio_client richiesta = MUOVI_GIU_CLIENT;
    if(write(server_socket, &richiesta, sizeof(Messaggio_client)) != sizeof(Messaggio_client))
        return false;
    return true;
}

bool invia_muovi_sinistra_al_server(int server_socket)
{
    Messaggio_client richiesta = MUOVI_SINISTRA_CLIENT;
    if(write(server_socket, &richiesta, sizeof(Messaggio_client)) != sizeof(Messaggio_client))
        return false;
    return true;
}

bool invia_muovi_destra_al_server(int server_socket)
{
    Messaggio_client richiesta = MUOVI_DESTRA_CLIENT;
    if(write(server_socket, &richiesta, sizeof(Messaggio_client)) != sizeof(Messaggio_client))
        return false;
    return true;
}

bool invia_esci_dalla_partita_al_server(int server_socket)
{
    Messaggio_client richiesta = ESCI_DALLA_PARTITA_CLIENT;
    if(write(server_socket, &richiesta, sizeof(Messaggio_client)) != sizeof(Messaggio_client))
        return false;
    return true;
}

bool invia_entra_in_partita_al_server(int server_socket)
{
    Messaggio_client richiesta = ENTRA_IN_PARTITA_CLIENT;
    if(write(server_socket, &richiesta, sizeof(Messaggio_client)) != sizeof(Messaggio_client))
        return false;
    return true;
}

bool invia_prendi_oggetto_al_server(int server_socket)
{
    Messaggio_client richiesta = PRENDI_OGGETTO_CLIENT;
    if(write(server_socket, &richiesta, sizeof(Messaggio_client)) != sizeof(Messaggio_client))
        return false;
    return true;
}

bool invia_lascia_oggetto_al_server(int server_socket)
{
    Messaggio_client richiesta = LASCIA_OGGETTO_CLIENT;
    if(write(server_socket, &richiesta, sizeof(Messaggio_client)) != sizeof(Messaggio_client))
        return false;
    return true;
}

bool invia_update_lite_info_al_server(int server_socket)
{
    Messaggio_client richiesta = UPDATE_LITE_INFO_CLIENT;
    if(write(server_socket, &richiesta, sizeof(Messaggio_client)) != sizeof(Messaggio_client))
        return false;
    return true;
}

bool invia_fine_partita_al_server(int server_socket)
{
    Messaggio_client richiesta = FINE_PARTITA;
    if(write(server_socket, &richiesta, sizeof(Messaggio_client)) != sizeof(Messaggio_client))
        return false;
    return true;
}
