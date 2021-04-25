#include "server.h"
#include "../utility/utility.h"
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include "../messaggio_client/messaggio_client.h"
#include <fcntl.h>
#include "../utility_comunicazione_server/utility_comunicazione_server.h"
#include "../costanti/costanti.h"
#include "../utility_gestione_accounts/utility_gestione_accounts.h"

//FUNZIONI NON VISIBILI
typedef struct Thread_args
{
    int client_socket;
    const char *client_hostname;
    const char *client_ip_address;
    Gestione_gioco_server *gestione_gioco;
}
Thread_args;

void crea_account_server(Thread_args *args)
{
    char account[SIZE_ACCOUNT] = "\0";
    char password[SIZE_PASSWORD] = "\0";
    if(get_account_dal_client(args->client_socket, account) && get_password_dal_client(args->client_socket, password) && 
       !is_account_esistente(account))
    {
        aggiungi_account(account, password);
        invia_successo_al_client(args->client_socket);
        registra_operazione_account(account, args->client_hostname, args->client_ip_address, "Operazione creazione account");
    }
    else
        invia_errore_al_client(args->client_socket);
}

void esegui_login_server(Thread_args *args)
{
    char account[SIZE_ACCOUNT] = "\0";
    char password[SIZE_PASSWORD] = "\0";
    if(get_account_dal_client(args->client_socket, account) && get_password_dal_client(args->client_socket, password) &&
       matching_account(account, password) && !is_giocatore_connesso_by_account(args->gestione_gioco, account))
    {
        int id = set_giocatore_connesso(args->gestione_gioco, account);
        set_ultima_richiesta_al_tempo_corrente(args->gestione_gioco, id);
        invia_successo_al_client(args->client_socket);
        invia_id_al_client(args->client_socket, id);
        registra_operazione_account(account, args->client_hostname, args->client_ip_address, "Operazione login account");
    }
    else
        invia_errore_al_client(args->client_socket);
}

void logout_server(Thread_args *args)
{
    int id = get_id_dal_client(args->client_socket);
    if(id == -1 || !is_giocatore_connesso_by_id(args->gestione_gioco, id))
        invia_errore_al_client(args->client_socket);
    else
    {
        set_giocatore_disconnesso(args->gestione_gioco, id);
        invia_successo_al_client(args->client_socket);
        registra_operazione_account(get_account_by_id(args->gestione_gioco, id), args->client_hostname, args->client_ip_address, "Operazione logout");
    }    
}

void entra_in_partita_server(Thread_args *args)
{
    int id = get_id_dal_client(args->client_socket);
    if(id == -1 || !is_giocatore_connesso_by_id(args->gestione_gioco, id))
        invia_errore_al_client(args->client_socket);
    else
    {
        set_ultima_richiesta_al_tempo_corrente(args->gestione_gioco, id);
        aggiungi_giocatore_in_partita(args->gestione_gioco, id);
        invia_successo_al_client(args->client_socket);
        registra_operazione_account(get_account_by_id(args->gestione_gioco, id), args->client_hostname, args->client_ip_address, "Operazione entra in partita");
    }
}

void esci_partita_server(Thread_args *args)
{
    int id = get_id_dal_client(args->client_socket);
    if(id == -1 || !is_giocatore_connesso_by_id(args->gestione_gioco, id))
        invia_errore_al_client(args->client_socket);
    else
    {
        set_ultima_richiesta_al_tempo_corrente(args->gestione_gioco, id);
        rimuovi_giocatore_dalla_partita(args->gestione_gioco, id);
        invia_successo_al_client(args->client_socket);
        registra_operazione_account(get_account_by_id(args->gestione_gioco, id), args->client_hostname, args->client_ip_address, "Operazione esci dalla partita");
    }
}

void muovi_su_server(Thread_args *args)
{
    int id = get_id_dal_client(args->client_socket);
    if(id == -1 || !is_giocatore_connesso_by_id(args->gestione_gioco, id))
        invia_errore_al_client(args->client_socket);
    else
    {
        set_ultima_richiesta_al_tempo_corrente(args->gestione_gioco, id);
        muovi_giocatore_su(args->gestione_gioco, id);
        invia_successo_al_client(args->client_socket);
    }
}

void muovi_giu_server(Thread_args *args)
{
    int id = get_id_dal_client(args->client_socket);
    if(id == -1 || !is_giocatore_connesso_by_id(args->gestione_gioco, id))
        invia_errore_al_client(args->client_socket);
    else
    {
        set_ultima_richiesta_al_tempo_corrente(args->gestione_gioco, id);
        muovi_giocatore_giu(args->gestione_gioco, id);
        invia_successo_al_client(args->client_socket);
    }
}

void muovi_sinistra_server(Thread_args *args)
{
    int id = get_id_dal_client(args->client_socket);
    if(id == -1 || !is_giocatore_connesso_by_id(args->gestione_gioco, id))
        invia_errore_al_client(args->client_socket);
    else
    {
        set_ultima_richiesta_al_tempo_corrente(args->gestione_gioco, id);
        muovi_giocatore_sinistra(args->gestione_gioco, id);
        invia_successo_al_client(args->client_socket);
    }
}

void muovi_destra_server(Thread_args *args)
{
    int id = get_id_dal_client(args->client_socket);
    if(id == -1 || !is_giocatore_connesso_by_id(args->gestione_gioco, id))
        invia_errore_al_client(args->client_socket);
    else
    {
        set_ultima_richiesta_al_tempo_corrente(args->gestione_gioco, id);
        muovi_giocatore_destra(args->gestione_gioco, id);
        invia_successo_al_client(args->client_socket);
    }
}

bool invia_ostacoli_visibili_al_client_server(int client_socket, Gestione_gioco_server *gioco, int id_giocatore)
{
    switch(id_giocatore)
    {
        case 0:
            return invia_ostacoli_visibili_al_client(client_socket, gioco->ostacoli_visibili_giocatore_uno, NUMERO_OSTACOLI);
        case 1:
            return invia_ostacoli_visibili_al_client(client_socket, gioco->ostacoli_visibili_giocatore_due, NUMERO_OSTACOLI);
        case 2:
            return invia_ostacoli_visibili_al_client(client_socket, gioco->ostacoli_visibili_giocatore_tre, NUMERO_OSTACOLI);
    }
}

void aggiorna_info_server(Thread_args *args)
{
    int id = get_id_dal_client(args->client_socket);
    if(id == -1 || !is_giocatore_connesso_by_id(args->gestione_gioco, id))
        invia_errore_al_client(args->client_socket);
    else
    {
        invia_successo_al_client(args->client_socket);
        if(invia_info_giocatori_al_client(args->client_socket, args->gestione_gioco->giocatori, MAX_CLIENTS))
            if(invia_info_oggetti_al_client(args->client_socket, args->gestione_gioco->oggetti, NUMERO_OGGETTI))
                if(invia_info_locazioni_al_client(args->client_socket, args->gestione_gioco->locazioni, NUMERO_LOCAZIONI))
                    if(invia_info_ostacoli_al_client(args->client_socket, args->gestione_gioco->ostacoli, NUMERO_OSTACOLI))
                        if(invia_ostacoli_visibili_al_client_server(args->client_socket, args->gestione_gioco, id))
                            if(invia_punti_al_client(args->client_socket, args->gestione_gioco->punti, MAX_CLIENTS))
                                invia_ora_creazione_partita_al_client(args->client_socket, args->gestione_gioco->ora_creazione_partita);
    }
}

void prendi_oggetto_server(Thread_args *args)
{
    int id = get_id_dal_client(args->client_socket);
    if(id == -1 || !is_giocatore_connesso_by_id(args->gestione_gioco, id))
        invia_errore_al_client(args->client_socket);
    else
    {
        set_ultima_richiesta_al_tempo_corrente(args->gestione_gioco, id);
        prendi_oggetto_gestione_gioco_server(args->gestione_gioco, id);
        invia_successo_al_client(args->client_socket);
    }
}

void lascia_oggetto_server(Thread_args *args)
{
    int id = get_id_dal_client(args->client_socket);
    if(id == -1 || !is_giocatore_connesso_by_id(args->gestione_gioco, id))
        invia_errore_al_client(args->client_socket);
    else
    {
        set_ultima_richiesta_al_tempo_corrente(args->gestione_gioco, id);
        lascia_oggetto_gestione_gioco_server(args->gestione_gioco, id, args->client_ip_address, args->client_hostname);
        invia_successo_al_client(args->client_socket);
    }
}

void update_lite_info_server(Thread_args *args)
{
    int id = get_id_dal_client(args->client_socket);
    if(id == -1 || !is_giocatore_connesso_by_id(args->gestione_gioco, id))
        invia_errore_al_client(args->client_socket);
    else
    {
        invia_successo_al_client(args->client_socket);
        if(invia_info_giocatori_al_client(args->client_socket, args->gestione_gioco->giocatori, MAX_CLIENTS))
            if(invia_info_oggetti_al_client(args->client_socket, args->gestione_gioco->oggetti, NUMERO_OGGETTI))
                 if(invia_ostacoli_visibili_al_client_server(args->client_socket, args->gestione_gioco, id))
                    invia_punti_al_client(args->client_socket, args->gestione_gioco->punti, MAX_CLIENTS);
    }
}

void fine_partita_server(Thread_args *args)
{
    int id = get_id_dal_client(args->client_socket);
    if(id == -1 || !is_giocatore_connesso_by_id(args->gestione_gioco, id))
        invia_errore_al_client(args->client_socket);
    else
    {
        set_ultima_richiesta_al_tempo_corrente(args->gestione_gioco, id);
        set_giocatori_tutti_non_in_gioco(args->gestione_gioco);
        invia_successo_al_client(args->client_socket);
    }
}

void gestisci_richiesta_client(Messaggio_client richiesta, Thread_args *args)
{
    switch(richiesta)
    {
        case LOGIN_CLIENT:
            esegui_login_server(args);
            break;
        case CREA_ACCOUNT_CLIENT:
            crea_account_server(args);
            break;
        case LOGOUT_CLIENT:
            logout_server(args);
            break;
        case ENTRA_IN_PARTITA_CLIENT:
            entra_in_partita_server(args);
            break;
        case ESCI_DALLA_PARTITA_CLIENT:
            esci_partita_server(args);
            break;
        case MUOVI_SU_CLIENT:
            muovi_su_server(args);
            break;
        case MUOVI_GIU_CLIENT:
            muovi_giu_server(args);
            break;
        case MUOVI_SINISTRA_CLIENT:
            muovi_sinistra_server(args);
            break;
        case MUOVI_DESTRA_CLIENT:
            muovi_destra_server(args);
            break;
        case AGGIORNA_INFO_CLIENT:
            aggiorna_info_server(args);
            break;
        case PRENDI_OGGETTO_CLIENT:
            prendi_oggetto_server(args);
            break;
        case LASCIA_OGGETTO_CLIENT:
            lascia_oggetto_server(args);
            break;
        case UPDATE_LITE_INFO_CLIENT:
            update_lite_info_server(args);
            break;
        case FINE_PARTITA:
            fine_partita_server(args);
            break;
    }
}

void* thread_richiesta_client(void *args)
{
    Thread_args *thread_args = (Thread_args*)args;
    kick_off_account_disconnessi(thread_args->gestione_gioco);
    Messaggio_client richiesta_client = ERRORE_CLIENT;
    richiesta_client = get_richiesta_dal_client(thread_args->client_socket);
    gestisci_richiesta_client(richiesta_client, thread_args);
    close(thread_args->client_socket);
    pthread_exit(NULL);
}

//FUNZIONI VISIBILI
bool init_server(Server *server, int porta, int quantita_client)
{
    signal(SIGPIPE, SIG_IGN);
    init_address_host(&server->my_address, "0", porta);
    server->socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if(server->socket_descriptor == -1)
        return false;
    int binding_response = bind(server->socket_descriptor, (struct sockaddr*)&server->my_address, sizeof(server->my_address));
    if(binding_response == -1)
        return false;
    int listening_response = listen(server->socket_descriptor, quantita_client);
    if(listening_response == -1)
        return false;
    init_gestione_gioco_server(&server->gestione_gioco);
    return true;
}

void esegui_server(Server *server)
{
    while(true)
    {
        struct sockaddr_in client_address;
        socklen_t len_client = sizeof(client_address);
        int client_socket = accept(server->socket_descriptor, (struct sockaddr*)&client_address, &len_client);
        if(client_socket == -1)
            exit(1);
        const char *client_hostname = get_hostname(&client_address);
        const char *client_ip_address = get_ip_address_host(&client_address);
        Thread_args args = { client_socket, client_hostname, client_ip_address, &server->gestione_gioco };
        pthread_t thread;
        pthread_create(&thread, NULL, thread_richiesta_client, &args);
    }
}