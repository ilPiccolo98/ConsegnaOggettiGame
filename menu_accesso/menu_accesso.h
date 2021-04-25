#ifndef MENU_ACCESSO_H
#define MENU_ACCESSO_H
#include <netinet/in.h>
#include <stdbool.h>
#include "../messaggio/messaggio.h"
#define VOCI_MENU_ACCESSO 3

typedef enum Voci_menu_accesso
{
    LOGIN_MENU_ACCESSO, CREA_ACCOUNT_MENU_ACCESSO, ESCI_MENU_ACCESSO
}
Voci_menu_accesso;

typedef struct Menu_accesso
{
    struct sockaddr_in *server_address;
    bool run_menu;
    Messaggio messaggi[VOCI_MENU_ACCESSO];
    Voci_menu_accesso voce_selezionata;
}
Menu_accesso;

void init_menu_accesso(Menu_accesso *menu, struct sockaddr_in *server_address);
void esegui_menu_accesso(Menu_accesso *menu);
void set_true_run_menu_accesso(Menu_accesso *menu);
void set_false_run_menu_accesso(Menu_accesso *menu);
bool get_run_menu_accesso(const Menu_accesso *menu);

#endif 