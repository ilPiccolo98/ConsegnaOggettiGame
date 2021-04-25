#include "menu_principale.h"
#include "../colori/colori.h"
#include "../console_utility/console_utility.h"
#include "../keys/keys.h"
#include "../menu_comandi/menu_comandi.h"
#include "../utility_comunicazione_client/utility_comunicazione_client.h"
#include <unistd.h>
#include "../game_client/game_client.h"
#define INIZIO_MENU_PRINCIPALE_X 4
#define INIZIO_MENU_PRINCIPALE_Y 6

//FUNZIONI NON VISIBILI
void init_voci_menu_principale(Menu_principale *menu)
{
    init_messaggio(&menu->messaggi[GIOCA_MENU_PRINCIPALE], "Gioca", INIZIO_MENU_PRINCIPALE_X, INIZIO_MENU_PRINCIPALE_Y);
    init_messaggio(&menu->messaggi[COMANDI_MENU_PRINCIPALE], "Comandi", INIZIO_MENU_PRINCIPALE_X, INIZIO_MENU_PRINCIPALE_Y + 2);
    init_messaggio(&menu->messaggi[LOGOUT_MENU_PRINCIPALE], "Logout", INIZIO_MENU_PRINCIPALE_X, INIZIO_MENU_PRINCIPALE_Y + 4);
}

void stampa_voci_menu_principale(const Menu_principale *menu)
{
    int i;
    for(i = 0; i != VOCI_MENU_PRINCIPALE; ++i)
    {
        if(i == menu->voce_selezionata)
            set_colore_console(ROSSO);
        else
            set_colore_console(VERDE);
        stampa_messaggio(&menu->messaggi[i]);
    }
}

void evento_key_w_menu_principale(Menu_principale *menu)
{
    if(menu->voce_selezionata == GIOCA_MENU_PRINCIPALE)
        menu->voce_selezionata = LOGOUT_MENU_PRINCIPALE;
    else
        --menu->voce_selezionata;
}

void evento_key_s_menu_principale(Menu_principale *menu)
{
    if(menu->voce_selezionata == LOGOUT_MENU_PRINCIPALE)
        menu->voce_selezionata = GIOCA_MENU_PRINCIPALE;
    else
        ++menu->voce_selezionata;
}

void premuto_comandi_menu_principale(void)
{
    Menu_comandi menu;
    init_menu_comandi(&menu);
    esegui_menu_comandi(&menu);
}

void premuto_logout_menu_principale(Menu_principale *menu)
{
    int server_socket = get_connessione_server(menu->server_address);
    if(!invia_logout_al_server(server_socket) || !invia_id_al_server(server_socket, menu->id_giocatore))
        gestisci_errore_comunicazione(server_socket);
    Messaggio_server messaggio = get_messaggio_dal_server(server_socket);
    if(messaggio == ERRORE_SERVER)
        gestisci_errore_comunicazione(server_socket);
    close(server_socket);
    menu->run_menu = false;
}

void premuto_gioca_menu_principale(Menu_principale *menu)
{
    int server_socket = get_connessione_server(menu->server_address);
    if(!invia_entra_in_partita_al_server(server_socket) || !invia_id_al_server(server_socket, menu->id_giocatore))
        gestisci_errore_comunicazione(server_socket);
    Messaggio_server messaggio = get_messaggio_dal_server(server_socket);
    close(server_socket);
    if(messaggio == ERRORE_SERVER)
        gestisci_errore_comunicazione(server_socket);
    close(server_socket);
    Game_client game;
    init_game_client(&game, menu->server_address, menu->id_giocatore);
    esegui_game_client(&game);
}

void evento_enter_menu_principale(Menu_principale *menu)
{
    switch(menu->voce_selezionata)
    {
        case GIOCA_MENU_PRINCIPALE:
            premuto_gioca_menu_principale(menu);
            break;
        case COMANDI_MENU_PRINCIPALE:
            premuto_comandi_menu_principale();
            break;
        case LOGOUT_MENU_PRINCIPALE:
            premuto_logout_menu_principale(menu);
            break;
    }
}

void gestisci_input_menu_principale(Menu_principale *menu, int input)
{
    switch(input)
    {
        case KEY_W:
            evento_key_w_menu_principale(menu);
            break;
        case KEY_S:
            evento_key_s_menu_principale(menu);
            break;
        case KEY_ENTER:
            evento_enter_menu_principale(menu);
            break;
    }
}

//FUNZIONI VISIBILI
void init_menu_principale(Menu_principale *menu, struct sockaddr_in *server_address, const char *account_giocatore, int id_giocatore)
{
    menu->server_address = server_address;
    menu->run_menu = true;
    menu->account_giocatore = account_giocatore;
    menu->id_giocatore = id_giocatore;
    init_voci_menu_principale(menu);
    menu->voce_selezionata = GIOCA_MENU_PRINCIPALE;
}

void esegui_menu_principale(Menu_principale *menu)
{
    while(menu->run_menu)
    {
        pulisci_console();
        stampa_voci_menu_principale(menu);
        int input = getch();
        gestisci_input_menu_principale(menu, input);
    }
}

void set_true_run_menu_principale(Menu_principale *menu)
{
    menu->run_menu = true;
}

void set_false_run_menu_principale(Menu_principale *menu)
{
    menu->run_menu = false;
}

bool get_run_menu_principale(const Menu_principale *menu)
{
    return menu->run_menu;
}

