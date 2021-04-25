#include "messaggio.h"
#include <stdio.h>
#include "../console_utility/console_utility.h"

void init_messaggio(Messaggio *m, const char *messaggio, int x, int y)
{
    m->messaggio = messaggio;
    m->x = x;
    m->y = y;
}

void stampa_messaggio(const Messaggio *m)
{
    muovi_cursore(m->x, m->y);
    printf("%s\n", m->messaggio);
}

void set_messaggio(Messaggio *m, const char *messaggio)
{
    m->messaggio = messaggio;
}

void set_x_messaggio(Messaggio *m, int x)
{
    m->x = x;
}

void set_y_messaggio(Messaggio *m, int y)
{
    m->y = y;
}

const char* get_messaggio(const Messaggio *m)
{
    return m->messaggio;
}

int get_x_messaggio(const Messaggio *m)
{
    return m->x;
}

int get_y_messaggio(const Messaggio *m)
{
    return m->y;
}


