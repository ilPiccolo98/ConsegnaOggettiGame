#include "menu_accesso.h"
#include "../colori/colori.h"
#include "../console_utility/console_utility.h"
#include "../keys/keys.h"
#include "../messaggio_client/messaggio_client.h"
#include <fcntl.h>
#include <unistd.h>
#include "../utility/utility.h"
#include "../costanti/costanti.h"
#include "../messaggio_server/messaggio_server.h"
#include "../utility_comunicazione_client/utility_comunicazione_client.h"
#include <stdlib.h>
#include "../menu_principale/menu_principale.h"
#define INIZIO_MENU_ACCESSO_X 4
#define INIZIO_MENU_ACCESSO_Y 6

//FUNZIONI NON VISIBILI
void init_voci_menu_accesso(Menu_accesso *menu)
{
    init_messaggio(&menu->messaggi[LOGIN_MENU_ACCESSO], "Login", INIZIO_MENU_ACCESSO_X, INIZIO_MENU_ACCESSO_Y);
    init_messaggio(&menu->messaggi[CREA_ACCOUNT_MENU_ACCESSO], "Crea Account", INIZIO_MENU_ACCESSO_X, INIZIO_MENU_ACCESSO_Y + 2);
    init_messaggio(&menu->messaggi[ESCI_MENU_ACCESSO], "Esci", INIZIO_MENU_ACCESSO_X, INIZIO_MENU_ACCESSO_Y + 4);
}

void stampa_voci_menu_accesso(const Menu_accesso *menu)
{
    int i;
    for(i = 0; i != VOCI_MENU_ACCESSO; ++i)
    {
        if(menu->voce_selezionata == i)
            set_colore_console(ROSSO);
        else
            set_colore_console(VERDE);
        stampa_messaggio(&menu->messaggi[i]);
    }
}

void evento_key_w_menu_accesso(Menu_accesso *menu)
{
    if(menu->voce_selezionata == LOGIN_MENU_ACCESSO)
        menu->voce_selezionata = ESCI_MENU_ACCESSO;
    else
        --(menu->voce_selezionata);
}

void evento_key_s_menu_accesso(Menu_accesso *menu)
{
    if(menu->voce_selezionata == ESCI_MENU_ACCESSO)
        menu->voce_selezionata = LOGIN_MENU_ACCESSO;
    else
        ++(menu->voce_selezionata);
}

void premuto_esci_menu_accesso(Menu_accesso *menu)
{
    menu->run_menu = false;
}

void get_account_menu_accesso(char *buffer)
{
    pulisci_console();
    get_string("Inserire account:\n", buffer, SIZE_ACCOUNT, INIZIO_MENU_ACCESSO_X, INIZIO_MENU_ACCESSO_Y);
}

void get_password_menu_accesso(char *buffer)
{
    pulisci_console();
    get_string("Inserire password:\n", buffer, SIZE_PASSWORD, INIZIO_MENU_ACCESSO_X, INIZIO_MENU_ACCESSO_Y);
}

void premuto_crea_accout_menu_accesso(struct sockaddr_in *server_address)
{
    char account[SIZE_ACCOUNT] = "\0";
    char password[SIZE_PASSWORD] = "\0";
    get_account_menu_accesso(account);
    get_password_menu_accesso(password);
    int server_socket = get_connessione_server(server_address);
    if(!invia_crea_account_al_server(server_socket) || 
       !invia_stringa_al_server(server_socket, account, SIZE_ACCOUNT) || 
       !invia_stringa_al_server(server_socket, password, SIZE_PASSWORD))
    {
        gestisci_errore_comunicazione(server_socket);
    }
    Messaggio_server messaggio_server = get_messaggio_dal_server(server_socket);
    close(server_socket);
    if(messaggio_server == SUCCESSO_SERVER)
    {
        pulisci_console();
        stampa_aspetta("Account creato con successo");
    }
    else
    {
        pulisci_console();
        stampa_aspetta("Errore creazione account");    
    }
}

void esegui_menu_principale_menu_accesso(const char *account, int id, struct sockaddr_in *server_address)
{
    if(id == -1)
    {
        pulisci_console();
        stampa_aspetta("Errore server");
    }
    else
    {
        pulisci_console();
        stampa_aspetta("Login effettuato con successo");
        Menu_principale menu_principale;
        init_menu_principale(&menu_principale, server_address, account, id);
        esegui_menu_principale(&menu_principale);
    }
}

void premuto_login_menu_accesso(struct sockaddr_in *server_address)
{
    char account[SIZE_ACCOUNT] = "\0";
    char password[SIZE_PASSWORD] = "\0";
    get_account_menu_accesso(account);
    get_password_menu_accesso(password);
    int server_socket = get_connessione_server(server_address);
    if(!invia_login_al_server(server_socket) || 
       !invia_stringa_al_server(server_socket, account, SIZE_ACCOUNT) || 
       !invia_stringa_al_server(server_socket, password, SIZE_PASSWORD))
    {
        gestisci_errore_comunicazione(server_socket);
    }
    Messaggio_server messaggio_server = get_messaggio_dal_server(server_socket);
    if(messaggio_server == SUCCESSO_SERVER)
    {
        int id = get_id_dal_server(server_socket);
        close(server_socket);
        esegui_menu_principale_menu_accesso(account, id, server_address);
    }
    else
    {
        close(server_socket);
        pulisci_console();
        stampa_aspetta("Errore login");    
    }
}

void evento_key_enter_menu_accesso(Menu_accesso *menu)
{
    switch(menu->voce_selezionata)
    {
        case LOGIN_MENU_ACCESSO:
            premuto_login_menu_accesso(menu->server_address);
            break;
        case CREA_ACCOUNT_MENU_ACCESSO:
            premuto_crea_accout_menu_accesso(menu->server_address);
            break;
        case ESCI_MENU_ACCESSO:
            premuto_esci_menu_accesso(menu);
            break;
    }
}

void gestisci_input_menu_accesso(Menu_accesso *menu, int input)
{
    switch(input)
    {
        case KEY_ENTER:
            evento_key_enter_menu_accesso(menu);
            break;
        case KEY_W:
            evento_key_w_menu_accesso(menu);
            break;
        case KEY_S:
            evento_key_s_menu_accesso(menu);
            break;
    }
}

//FUNZIONI VISIBILI
void init_menu_accesso(Menu_accesso *menu, struct sockaddr_in *server_address)
{
    menu->server_address = server_address;
    menu->run_menu = true;
    menu->voce_selezionata = LOGIN_MENU_ACCESSO;
    init_voci_menu_accesso(menu);
}

void esegui_menu_accesso(Menu_accesso *menu)
{
    while(menu->run_menu)
    {
        pulisci_console();
        stampa_voci_menu_accesso(menu);
        int input = getch();
        gestisci_input_menu_accesso(menu, input);
    }
}

void set_true_run_menu_accesso(Menu_accesso *menu)
{
    menu->run_menu = true;
}

void set_false_run_menu_accesso(Menu_accesso *menu)
{
    menu->run_menu = false;
}

bool get_run_menu_accesso(const Menu_accesso *menu)
{
    return menu->run_menu;
}
