#include "menu_comandi.h"
#include "../console_utility/console_utility.h"
#include "../colori/colori.h"
#include <stdbool.h>
#define INIZIO_MENU_COMANDI_X 4
#define INIZIO_MENU_COMANDI_Y 6

//FUNZIONI NON VISIBILI
typedef enum Voce_messaggio_menu_comandi
{
    INIZIALE, MUOVI_SU, MUOVI_GIU, MUOVI_SINISTRA,
    MUOVI_DESTRA, RACCOGLI_OGGETTO, LASCIA_OGGETTO,
    ESCI
}
Voce_messaggio_menu_comandi;

void stampa_messaggi_menu_comandi(const Menu_comandi *menu)
{
    int i;
    for(i = 0; i != SIZE_MESSAGGI_MENU_COMANDI; ++i)
    {
        set_colore_console(VERDE);
        stampa_messaggio(&menu->messaggi[i]);
    }
}

//FUNZIONI VISIBILI
void init_menu_comandi(Menu_comandi *menu)
{
    init_messaggio(&menu->messaggi[INIZIALE], "ELENCO COMANDI DI GIOCO:", INIZIO_MENU_COMANDI_X, INIZIO_MENU_COMANDI_X);
    init_messaggio(&menu->messaggi[MUOVI_SU], "Pulsante muovi su: W", INIZIO_MENU_COMANDI_X, INIZIO_MENU_COMANDI_X + 2);
    init_messaggio(&menu->messaggi[MUOVI_GIU], "Pulsante muovi giu': S", INIZIO_MENU_COMANDI_X, INIZIO_MENU_COMANDI_X + 4);
    init_messaggio(&menu->messaggi[MUOVI_SINISTRA], "Pulsante muovi sinistra: A", INIZIO_MENU_COMANDI_X, INIZIO_MENU_COMANDI_X + 6);
    init_messaggio(&menu->messaggi[MUOVI_DESTRA], "Pulsante muovi destra: D", INIZIO_MENU_COMANDI_X, INIZIO_MENU_COMANDI_X + 8);
    init_messaggio(&menu->messaggi[RACCOGLI_OGGETTO], "Pulsante raccogli oggetto: J", INIZIO_MENU_COMANDI_X, INIZIO_MENU_COMANDI_X + 10);
    init_messaggio(&menu->messaggi[LASCIA_OGGETTO], "Pulsante lascia oggetto: K", INIZIO_MENU_COMANDI_X, INIZIO_MENU_COMANDI_X + 12);
    init_messaggio(&menu->messaggi[ESCI], "Premere un pulsante per tornare al menu principale", INIZIO_MENU_COMANDI_X, INIZIO_MENU_COMANDI_X + 14);
}

void esegui_menu_comandi(const Menu_comandi *menu)
{
    pulisci_console();
    stampa_messaggi_menu_comandi(menu);
    int c = getch();
}

