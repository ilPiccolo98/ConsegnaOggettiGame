#include "game_client.h"
#include "../utility_comunicazione_client/utility_comunicazione_client.h"
#include <unistd.h>
#include "../console_utility/console_utility.h"
#include "../utility/utility.h"
#include "../colori/colori.h"
#include "../keys/keys.h"
#define MAPPA_POSIZIONE_X 10
#define MAPPA_POSIZIONE_Y 5
#define POSIZIONE_X_ACCOUNT_GIOCATORE_UNO 35
#define POSIZIONE_X_ACCOUNT_GIOCATORE_DUE 35
#define POSIZIONE_X_ACCOUNT_GIOCATORE_TRE 35
#define POSIZIONE_Y_ACCOUNT_GIOCATORE_UNO 5
#define POSIZIONE_Y_ACCOUNT_GIOCATORE_DUE 7
#define POSIZIONE_Y_ACCOUNT_GIOCATORE_TRE 9


//FUNZIONI NON VISIBILI
void update_info_giocatori_game_client(Game_client *game, int server_socket)
{
    if(!get_info_giocatori_dal_server(server_socket, game->giocatori, MAX_CLIENTS))
        gestisci_errore_comunicazione(server_socket);
}

void update_info_oggetti_game_client(Game_client *game, int server_socket)
{
    if(!get_info_oggetti_dal_server(server_socket, game->oggetti, NUMERO_OGGETTI))
        gestisci_errore_comunicazione(server_socket);
}

void update_info_locazioni_game_client(Game_client *game, int server_socket)
{
    if(!get_info_locazioni_dal_server(server_socket, game->locazioni, NUMERO_LOCAZIONI))
        gestisci_errore_comunicazione(server_socket);
}

void update_info_ostacoli_game_client(Game_client *game, int server_socket)
{
    if(!get_info_ostacoli_dal_server(server_socket, game->ostacoli, NUMERO_OSTACOLI))
        gestisci_errore_comunicazione(server_socket);
}

void update_ostacoli_visibili_game_client(Game_client *game, int server_socket)
{
    if(!get_ostacoli_visibili_dal_server(server_socket, game->ostacoli_visibili, NUMERO_OSTACOLI))
        gestisci_errore_comunicazione(server_socket);
}

void update_punti_game_client(Game_client *game, int server_socket)
{
    if(!get_punti_dal_server(server_socket, game->punti, MAX_CLIENTS))
        gestisci_errore_comunicazione(server_socket);
}

void update_ora_creazione_partita(Game_client *game, int server_socket)
{
    if(!get_ora_creazione_partita_dal_server(server_socket, &game->ora_creazione_partita))
        gestisci_errore_comunicazione(server_socket);
}

void update_info_game_client(Game_client *game)
{
    int server_socket = get_connessione_server(game->server_address);
    if(!invia_aggiorna_info_al_server(server_socket) || !invia_id_al_server(server_socket, game->id_giocatore))
        gestisci_errore_comunicazione(server_socket);
    Messaggio_server messaggio = get_messaggio_dal_server(server_socket);
    if(messaggio == ERRORE_SERVER)
        gestisci_errore_comunicazione(server_socket);
    update_info_giocatori_game_client(game, server_socket);
    update_info_oggetti_game_client(game, server_socket);
    update_info_locazioni_game_client(game, server_socket);
    update_info_ostacoli_game_client(game, server_socket);
    update_ostacoli_visibili_game_client(game, server_socket);
    update_punti_game_client(game, server_socket);
    update_ora_creazione_partita(game, server_socket);
    close(server_socket);
}

void update_lite_info_game_client(Game_client *game)
{
    int server_socket = get_connessione_server(game->server_address);
    if(!invia_update_lite_info_al_server(server_socket) || !invia_id_al_server(server_socket, game->id_giocatore))
        gestisci_errore_comunicazione(server_socket);
    Messaggio_server messaggio = get_messaggio_dal_server(server_socket);
    if(messaggio == ERRORE_SERVER)
        gestisci_errore_comunicazione(server_socket);
    update_info_giocatori_game_client(game, server_socket);
    update_info_oggetti_game_client(game, server_socket);
    update_ostacoli_visibili_game_client(game, server_socket);
    update_punti_game_client(game, server_socket);
    close(server_socket);
}

void stampa_account_giocatore_game_client(Giocatore *giocatore, int index)
{
    switch(index)
    {
        case 0:
            stampa_account_giocatore(giocatore, POSIZIONE_X_ACCOUNT_GIOCATORE_UNO, POSIZIONE_Y_ACCOUNT_GIOCATORE_UNO);
            break;
        case 1:
            stampa_account_giocatore(giocatore, POSIZIONE_X_ACCOUNT_GIOCATORE_DUE, POSIZIONE_Y_ACCOUNT_GIOCATORE_DUE);
            break;
        case 2:
            stampa_account_giocatore(giocatore, POSIZIONE_X_ACCOUNT_GIOCATORE_TRE, POSIZIONE_Y_ACCOUNT_GIOCATORE_TRE);
            break;
    }
}

void cancella_account_giocatore_game_client(Giocatore *giocatore, int index)
{
    switch(index)
    {
        case 0:
            cancella_account_giocatore(giocatore, POSIZIONE_X_ACCOUNT_GIOCATORE_UNO, POSIZIONE_Y_ACCOUNT_GIOCATORE_UNO);
            break;
        case 1:
            cancella_account_giocatore(giocatore, POSIZIONE_X_ACCOUNT_GIOCATORE_DUE, POSIZIONE_Y_ACCOUNT_GIOCATORE_DUE);
            break;
        case 2:
            cancella_account_giocatore(giocatore, POSIZIONE_X_ACCOUNT_GIOCATORE_TRE, POSIZIONE_Y_ACCOUNT_GIOCATORE_TRE);
            break;
    }
}

void stampa_giocatori_game_client(Game_client *game)
{
    int i;
    for(i = 0; i != MAX_CLIENTS; ++i)
    {
        if(get_in_gioco_giocatore(&game->giocatori[i]))
        {
            if(game->id_giocatore == i)
                set_colore_console(get_colore_giocatore(&game->giocatori[i]));
            else
                set_colore_console(ROSSO);
            stampa_giocatore(&game->giocatori[i], MAPPA_POSIZIONE_X, MAPPA_POSIZIONE_Y);
            stampa_account_giocatore_game_client(&game->giocatori[i], i);
        }
    }
}

void stampa_oggetti_game_client(Game_client *game)
{
    int i;
    for(i = 0; i != NUMERO_OGGETTI; ++i)
    {
        if(is_visibile_oggetto(&game->oggetti[i]))
        {
            set_colore_console(get_colore_oggetto(&game->oggetti[i]));
            stampa_oggetto(&game->oggetti[i], MAPPA_POSIZIONE_X, MAPPA_POSIZIONE_Y);
        }
    }
}

void stampa_locazioni_game_client(Game_client *game)
{
    int i;
    for(i = 0; i != NUMERO_LOCAZIONI; ++i)
    {
        set_colore_console(get_colore_locazione(&game->locazioni[i]));
        stampa_locazione(&game->locazioni[i], MAPPA_POSIZIONE_X, MAPPA_POSIZIONE_Y);
    }
}

void stampa_ostacoli_game_client(Game_client *game)
{
    set_colore_console(CIANO);
    int i;
    for(i = 0; i != NUMERO_OSTACOLI; ++i)
        if(game->ostacoli_visibili[i])
            stampa_ostacolo(&game->ostacoli[i], MAPPA_POSIZIONE_X, MAPPA_POSIZIONE_Y);
}

void stampa_elementi_game_client(Game_client *game)
{
    stampa_oggetti_game_client(game);
    stampa_locazioni_game_client(game);
    stampa_giocatori_game_client(game);
    stampa_ostacoli_game_client(game);
}

void cancella_giocatori_game_client(Game_client *game)
{
    int i;
    for(i = 0; i != MAX_CLIENTS; ++i)
        if(get_in_gioco_giocatore(&game->giocatori[i]))
        {
            cancella_giocatore(&game->giocatori[i], MAPPA_POSIZIONE_X, MAPPA_POSIZIONE_Y);
            cancella_account_giocatore_game_client(&game->giocatori[i], i);
        }
}

void cancella_oggetti_game_client(Game_client *game)
{
    int i;
    for(i = 0; i != NUMERO_OGGETTI; ++i)
        cancella_oggetto(&game->oggetti[i], MAPPA_POSIZIONE_X, MAPPA_POSIZIONE_Y);
}

void cancella_locazioni_game_client(Game_client *game)
{
    int i;
    for(i = 0; i != NUMERO_LOCAZIONI; ++i)
        cancella_locazione(&game->locazioni[i], MAPPA_POSIZIONE_X, MAPPA_POSIZIONE_Y);
}

void cancella_ostacoli_game_client(Game_client *game)
{
    int i;
    for(i = 0; i != NUMERO_OSTACOLI; ++i)
        cancella_ostacolo(&game->ostacoli[i], MAPPA_POSIZIONE_X, MAPPA_POSIZIONE_Y);
}

void cancella_elementi_game_client(Game_client *game)
{
    cancella_giocatori_game_client(game);
    cancella_oggetti_game_client(game);
    cancella_locazioni_game_client(game);
    cancella_ostacoli_game_client(game);
}

void evento_key_w_game_client(Game_client *game)
{
    int server_socket = get_connessione_server(game->server_address);
    if(!invia_muovi_su_al_server(server_socket) || !invia_id_al_server(server_socket, game->id_giocatore))
        gestisci_errore_comunicazione(server_socket);
    Messaggio_server messaggio = get_messaggio_dal_server(server_socket);
    if(messaggio == ERRORE_SERVER)
        gestisci_errore_comunicazione(server_socket);
    close(server_socket);
}

void evento_key_s_game_client(Game_client *game)
{
    int server_socket = get_connessione_server(game->server_address);
    if(!invia_muovi_giu_al_server(server_socket) || !invia_id_al_server(server_socket, game->id_giocatore))
        gestisci_errore_comunicazione(server_socket);
    Messaggio_server messaggio = get_messaggio_dal_server(server_socket);
    if(messaggio == ERRORE_SERVER)
        gestisci_errore_comunicazione(server_socket);
    close(server_socket);
}

void evento_key_a_game_client(Game_client *game)
{
    int server_socket = get_connessione_server(game->server_address);
    if(!invia_muovi_sinistra_al_server(server_socket) || !invia_id_al_server(server_socket, game->id_giocatore))
        gestisci_errore_comunicazione(server_socket);
    Messaggio_server messaggio = get_messaggio_dal_server(server_socket);
    if(messaggio == ERRORE_SERVER)
        gestisci_errore_comunicazione(server_socket);
    close(server_socket);
}

void evento_key_d_game_client(Game_client *game)
{
    int server_socket = get_connessione_server(game->server_address);
    if(!invia_muovi_destra_al_server(server_socket) || !invia_id_al_server(server_socket, game->id_giocatore))
        gestisci_errore_comunicazione(server_socket);
    Messaggio_server messaggio = get_messaggio_dal_server(server_socket);
    if(messaggio == ERRORE_SERVER)
        gestisci_errore_comunicazione(server_socket);
    close(server_socket);
}

void evento_key_esc_game_client(Game_client *game)
{
    int server_socket = get_connessione_server(game->server_address);
    if(!invia_esci_dalla_partita_al_server(server_socket) || !invia_id_al_server(server_socket, game->id_giocatore))
        gestisci_errore_comunicazione(server_socket);
    Messaggio_server messaggio = get_messaggio_dal_server(server_socket);
    if(messaggio == ERRORE_SERVER)
        gestisci_errore_comunicazione(server_socket);
    close(server_socket);
    game->run_game = false;
}

void evento_key_j_game_client(Game_client *game)
{
    int server_socket = get_connessione_server(game->server_address);
    if(!invia_prendi_oggetto_al_server(server_socket) || !invia_id_al_server(server_socket, game->id_giocatore))
        gestisci_errore_comunicazione(server_socket);
    Messaggio_server messaggio = get_messaggio_dal_server(server_socket);
    if(messaggio == ERRORE_SERVER)
        gestisci_errore_comunicazione(server_socket);
    close(server_socket);
}

void evento_key_k_game_client(Game_client *game)
{
    int server_socket = get_connessione_server(game->server_address);
    if(!invia_lascia_oggetto_al_server(server_socket) || !invia_id_al_server(server_socket, game->id_giocatore))
        gestisci_errore_comunicazione(server_socket);
    Messaggio_server messaggio = get_messaggio_dal_server(server_socket);
    if(messaggio == ERRORE_SERVER)
        gestisci_errore_comunicazione(server_socket);
    close(server_socket);
}

void gestisci_input(Game_client *game, int input)
{
    switch(input)
    {
        case KEY_W:
            evento_key_w_game_client(game);
            break;
        case KEY_S:
            evento_key_s_game_client(game);
            break;
        case KEY_A:
            evento_key_a_game_client(game);
            break;
        case KEY_D:
            evento_key_d_game_client(game);
            break;
        case KEY_ESC:
            evento_key_esc_game_client(game);
            break;
        case KEY_J:
            evento_key_j_game_client(game);
            break;
        case KEY_K:
            evento_key_k_game_client(game);
            break;
    }
}

bool are_objects_all_not_visible(Game_client *game)
{
    int i;
    for(i = 0; i != NUMERO_OGGETTI; ++i)
        if(game->oggetti[i].visibile)
            return false;
    return true;
}

bool is_time_over(Game_client *game)
{
    int differenza = (int)difftime(get_current_time(), game->ora_creazione_partita);
    if(differenza >= TEMPO_SESSIONE_PARTITA)
        return true;
    return false;
}

int get_punteggio_piu_alto(Game_client *game)
{
    int punti = 0;
    int i;
    for(i = 0; i != MAX_CLIENTS; ++i)
        if(game->giocatori[i].in_gioco && punti < game->punti[i])
            punti = game->punti[i];
    return punti;
}

void stampa_messaggio_finale(Game_client *game)
{
    pulisci_console();
    muovi_cursore(0, 0);
    puts("Ha//Hanno vinto:");
    int punteggio_max = get_punteggio_piu_alto(game);
    int i;
    for(i = 0; i != MAX_CLIENTS; ++i)
        if(game->giocatori[i].in_gioco && game->punti[i] == punteggio_max)
            printf("%s\n", get_account_giocatore(&game->giocatori[i]));
    printf("Con %d punti\n", punteggio_max);
    puts("Verra' creata una nuova partita");
    puts("Premere invio per continuare...");
    premi_invio();
}

void comunica_fine_partita(Game_client *game)
{
    int server_socket = get_connessione_server(game->server_address);
    if(!invia_fine_partita_al_server(server_socket) || !invia_id_al_server(server_socket, game->id_giocatore))
        gestisci_errore_comunicazione(server_socket);
    Messaggio_server messaggio = get_messaggio_dal_server(server_socket);
    if(messaggio == ERRORE_SERVER)  
        gestisci_errore_comunicazione(server_socket);
    close(server_socket);
}

void crea_nuova_partita(Game_client *game)
{
    int server_socket = get_connessione_server(game->server_address);
    if(!invia_entra_in_partita_al_server(server_socket) || !invia_id_al_server(server_socket, game->id_giocatore))
        gestisci_errore_comunicazione(server_socket);
    Messaggio_server messaggio = get_messaggio_dal_server(server_socket);
    if(messaggio == ERRORE_SERVER)  
        gestisci_errore_comunicazione(server_socket);
    close(server_socket);
}

void fine_partita(Game_client *game)
{
    comunica_fine_partita(game);
    stampa_messaggio_finale(game);
    crea_nuova_partita(game);
    pulisci_console();
    set_colore_console(BLU);
    stampa_mappa(&game->mappa, MAPPA_POSIZIONE_X, MAPPA_POSIZIONE_Y);
    update_info_game_client(game);
}

//FUNZIONI VISIBILI
void init_game_client(Game_client *game, struct sockaddr_in *server_address, int id_giocatore)
{
    game->run_game = true;
    game->server_address = server_address;
    game->id_giocatore = id_giocatore;
    init_mappa(&game->mappa, RIGHE_MAPPA, COLONNE_MAPPA);
    update_info_game_client(game);
}

void esegui_game_client(Game_client *game)
{
    pulisci_console();
    set_colore_console(BLU);
    stampa_mappa(&game->mappa, MAPPA_POSIZIONE_X, MAPPA_POSIZIONE_Y);
    stampa_elementi_game_client(game);
    while(game->run_game)
    {
        if(!kbhit())
        {
            cancella_giocatori_game_client(game);
            update_lite_info_game_client(game);
            stampa_elementi_game_client(game);
        }
        else
        {
            int input = getch();
            cancella_giocatori_game_client(game);
            gestisci_input(game, input);
            update_lite_info_game_client(game);
            stampa_elementi_game_client(game);
        }
        if(are_objects_all_not_visible(game) || is_time_over(game))
        {
            cancella_elementi_game_client(game);
            fine_partita(game);
        }
    }
    cancella_elementi_game_client(game);
}
