#include "giocatore.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../console_utility/console_utility.h"
#include "../utility/utility.h"
#include "../colori/colori.h"

//DA COMPILARE
//FUNZIONI NON VISIBILI
bool is_x_corretta_giocatore(int x)
{
    if(x < 0)
        return false;
    return true;
}

bool is_y_corretta_giocatore(int y)
{
    if(y < 0)
        return false;
    return true;
}

bool associa_giocatore_oggetto(Giocatore *giocatore, Oggetto *oggetto)
{
    if(giocatore->oggetto || !oggetto)
        return false;
    giocatore->oggetto = oggetto;
    return true;
}

bool dissocia_giocatore_oggetto(Giocatore *giocatore)
{
    if(!giocatore->oggetto)
        return false;
    giocatore->oggetto = NULL;
    return true;
}

//FUNZIONI VISIBILI
void init_giocatore(Giocatore *giocatore, int x, int y, char skin, bool connesso, bool in_gioco, int id, const char *account)
{
    giocatore->x = x;
    giocatore->y = y;
    giocatore->skin = skin;
    giocatore->oggetto = NULL;
    giocatore->connesso = connesso;
    giocatore->id = id;
    set_account_giocatore(giocatore, account);
    giocatore->in_gioco = in_gioco;
    set_colore_giocatore(giocatore, VERDE);
}

void stampa_giocatore(const Giocatore *giocatore, int x, int y)
{
    muovi_cursore(giocatore->x + x, giocatore->y + y);
    putchar(giocatore->skin);
}

void cancella_giocatore(const Giocatore *giocatore, int x, int y)
{
    muovi_cursore(giocatore->x + x, giocatore->y + y);
    putchar(' ');
}

int get_x_giocatore(const Giocatore *giocatore)
{
    return giocatore->x;
}

int get_y_giocatore(const Giocatore *giocatore)
{
    return giocatore->y;
}

char get_skin_giocatore(const Giocatore *giocatore)
{
    return giocatore->skin;
}

bool set_x_giocatore(Giocatore *giocatore, int x)
{
    if(!is_x_corretta_giocatore(x))
        return false;
    giocatore->x = x;
    if(ha_oggetto_giocatore(giocatore))
        set_x_oggetto(giocatore->oggetto, x);
    return true;
}

bool set_y_giocatore(Giocatore *giocatore, int y)
{
    if(!is_y_corretta_giocatore(y))
        return false;
    giocatore->y = y;
    if(ha_oggetto_giocatore(giocatore))
        set_y_oggetto(giocatore->oggetto, y);
    return true;
}

void set_skin_giocatore(Giocatore *giocatore, char skin)
{
    giocatore->skin = skin;
}

void set_connesso_giocatore(Giocatore *giocatore, bool connesso)
{
    giocatore->connesso = connesso;
}

bool get_connesso_giocatore(const Giocatore *giocatore)
{
    return giocatore->connesso;
}

void set_in_gioco_giocatore(Giocatore *giocatore, bool in_gioco)
{
    giocatore->in_gioco = in_gioco;
}

bool get_in_gioco_giocatore(const Giocatore *giocatore)
{
    return giocatore->in_gioco;
}

void set_id_giocatore(Giocatore *giocatore, int id)
{
    giocatore->id = id;
}

int get_id_giocatore(const Giocatore *giocatore)
{
    return giocatore->id;
}

void set_account_giocatore(Giocatore *giocatore, const char *account)
{
    memcpy(giocatore->account, account, SIZE_ACCOUNT);
}

const char* get_account_giocatore(const Giocatore *giocatore)
{
    return giocatore->account;
}

void set_oggetto_giocatore(Giocatore *giocatore, Oggetto *oggetto)
{
    giocatore->oggetto = oggetto;
}

bool ha_oggetto_giocatore(const Giocatore *giocatore)
{
    if(giocatore->oggetto)
        return true;
    return false;
}

void scollega_oggetto_giocatore(Giocatore *giocatore)
{
    giocatore->oggetto = NULL;
}

Oggetto* get_oggetto_giocatore(const Giocatore *giocatore)
{
    return giocatore->oggetto;
}

void set_colore_giocatore(Giocatore *giocatore, const char *colore)
{
    memcpy(giocatore->colore, colore, SIZE_COLORE);
}

const char* get_colore_giocatore(const Giocatore *giocatore)
{
    return giocatore->colore;
}

void stampa_account_giocatore(const Giocatore *giocatore, int x, int y)
{
    muovi_cursore(x, y);
    printf("%s\n", giocatore->account);
}

void cancella_account_giocatore(const Giocatore *giocatore, int x, int y)
{
    muovi_cursore(x, y);
    int len = strlen(giocatore->account);
    int i;
    for(i = 0; i != len; ++i)
        putchar(' ');
}