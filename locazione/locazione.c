#include "locazione.h"
#include <string.h>
#include <stdio.h>
#include "../console_utility/console_utility.h"

//FUNZIONI VISIBILI
void init_locazione(Locazione *locazione, int x, int y, char skin, const char *colore)
{
    set_x_locazione(locazione, x);
    set_y_locazione(locazione, y);
    set_colore_locazione(locazione, colore);
    set_skin_locazione(locazione, skin);
}

int get_x_locazione(const Locazione *locazione)
{
    return locazione->x;
}

void set_x_locazione(Locazione *locazione, int x)
{
    locazione->x = x;
}

int get_y_locazione(const Locazione *locazione)
{
    return locazione->y;
}

void set_y_locazione(Locazione *locazione, int y)
{
    locazione->y = y;
}

const char* get_colore_locazione(const Locazione *locazione)
{
    return locazione->colore;
}

void set_colore_locazione(Locazione *locazione, const char *colore)
{
    memcpy(locazione->colore, colore, SIZE_COLORE);
}

char get_skin_locazione(const Locazione *locazione)
{
    return locazione->skin;
}

void set_skin_locazione(Locazione *locazione, char skin)
{
    locazione->skin = skin;
}

void stampa_locazione(const Locazione *locazione, int x, int y)
{
    set_colore_console(locazione->colore);
    muovi_cursore(locazione->x + x, locazione->y + y);
    putchar(locazione->skin);
}

void cancella_locazione(const Locazione *locazione, int x, int y)
{
    muovi_cursore(locazione->x + x, locazione->y + y);
    putchar(' ');
}
