#include "ostacolo.h"
#include "../console_utility/console_utility.h"
#include <stdio.h>

//FUNZIONI VISIBILI
void init_ostacolo(Ostacolo *ostacolo, int x, int y, char skin)
{
    set_x_ostacolo(ostacolo, x);
    set_y_ostacolo(ostacolo, y);
    set_skin_ostacolo(ostacolo, skin);
}

int get_x_ostacolo(const Ostacolo *ostacolo)
{
    return ostacolo->x;
}

void set_x_ostacolo(Ostacolo *ostacolo, int x)
{
    ostacolo->x = x;
}

int get_y_ostacolo(const Ostacolo *ostacolo)
{
    return ostacolo->y;
}

void set_y_ostacolo(Ostacolo *ostacolo, int y)
{
    ostacolo->y = y;
}

char get_skin_ostacolo(const Ostacolo *ostacolo)
{
    return ostacolo->skin;
}

void set_skin_ostacolo(Ostacolo *ostacolo, char skin)
{
    ostacolo->skin = skin;
}

void stampa_ostacolo(const Ostacolo *ostacolo, int x, int y)
{
    muovi_cursore(ostacolo->x + x, ostacolo->y + y);
    putchar(ostacolo->skin);
}

void cancella_ostacolo(const Ostacolo *ostacolo, int x, int y)
{
    muovi_cursore(ostacolo->x + x, ostacolo->y + y);
    putchar(' ');
}

