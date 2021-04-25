#include "oggetto.h"
#include <stdio.h>
#include "../console_utility/console_utility.h"
#include "../utility/utility.h"
#include <string.h>

//FUNZIONI NON VISIBILI
bool is_x_corretta_oggetto(int x)
{
    if(x < 0)
        return false;
    return true;
}

bool is_y_corretta_oggetto(int y)
{
    if(y < 0)
        return false;
    return true;
}

//FUNZIONI VISIBILI
void init_oggetto(Oggetto *oggetto, int x, int y, char skin, const char *colore, bool visibile)
{
    set_x_oggetto(oggetto, x);
    set_y_oggetto(oggetto, y);
    set_skin_oggetto(oggetto, skin);
    set_colore_oggetto(oggetto, colore);
    set_visibile_oggetto(oggetto, visibile);
}

void stampa_oggetto(const Oggetto *oggetto, int x, int y)
{
    muovi_cursore(oggetto->x + x, oggetto->y + y);
    putchar(oggetto->skin);
}

void cancella_oggetto(const Oggetto *oggetto, int x, int y)
{
    muovi_cursore(oggetto->x + x, oggetto->y + y);
    putchar(' ');
}

int get_x_oggetto(const Oggetto *oggetto)
{
    return oggetto->x;
}

int get_y_oggetto(const Oggetto *oggetto)
{
    return oggetto->y;
}

char get_skin_oggetto(const Oggetto *oggetto)
{
    return oggetto->skin;
}

bool set_x_oggetto(Oggetto *oggetto, int x)
{
    if(!is_x_corretta_oggetto(x))
        return false;
    oggetto->x = x;
    return true;
}

bool set_y_oggetto(Oggetto *oggetto, int y)
{
    if(!is_y_corretta_oggetto(y))
        return false;
    oggetto->y = y;
    return true;
}

void set_skin_oggetto(Oggetto *oggetto, char skin)
{
    oggetto->skin = skin;
}

const char *get_colore_oggetto(const Oggetto *oggetto)
{
    return oggetto->colore;
}

void set_colore_oggetto(Oggetto *oggetto, const char *colore)
{
    memcpy(oggetto->colore, colore, SIZE_COLORE * sizeof(char));
}

bool is_visibile_oggetto(const Oggetto *oggetto)
{
    return oggetto->visibile;
}

void set_visibile_oggetto(Oggetto *oggetto, bool visibile)
{
    oggetto->visibile = visibile;
}