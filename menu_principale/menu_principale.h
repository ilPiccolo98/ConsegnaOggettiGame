#ifndef MENU_PRINCIPALE_H
#define MENU_PRINCIPALE_H
#define VOCI_MENU_PRINCIPALE 3
#include "../messaggio/messaggio.h"
#include <netinet/in.h>
#include <stdbool.h>

typedef enum Voci_menu_principale
{
    GIOCA_MENU_PRINCIPALE, COMANDI_MENU_PRINCIPALE, LOGOUT_MENU_PRINCIPALE
}
Voci_menu_principale;

typedef struct Menu_principale
{
    struct sockaddr_in *server_address;
    bool run_menu;
    Messaggio messaggi[VOCI_MENU_PRINCIPALE];
    Voci_menu_principale voce_selezionata;
    const char *account_giocatore;
    int id_giocatore;
}
Menu_principale;

void init_menu_principale(Menu_principale *menu, struct sockaddr_in *server_address, const char *account_giocatore, int id_giocatore);
void esegui_menu_principale(Menu_principale *menu);
void set_true_run_menu_principale(Menu_principale *menu);
void set_false_run_menu_principale(Menu_principale *menu);
bool get_run_menu_principale(const Menu_principale *menu);

#endif