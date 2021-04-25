#ifndef MENU_COMANDI_H
#define MENU_COMANDI_H
#define SIZE_MESSAGGI_MENU_COMANDI 8
#include "../messaggio/messaggio.h"

typedef struct Menu_comandi
{
    Messaggio messaggi[SIZE_MESSAGGI_MENU_COMANDI];
}
Menu_comandi;

void init_menu_comandi(Menu_comandi *menu);
void esegui_menu_comandi(const Menu_comandi *menu);

#endif