#ifndef LOCAZIONE_H
#define LOCAZIONE_H
#include "../costanti/costanti.h"

typedef struct Locazione
{
    char colore[SIZE_COLORE];
    int x;
    int y;
    char skin;
}
Locazione;

void init_locazione(Locazione *locazione, int x, int y, char skin, const char *colore);
int get_x_locazione(const Locazione *locazione);
void set_x_locazione(Locazione *locazione, int x);
int get_y_locazione(const Locazione *locazione);
void set_y_locazione(Locazione *locazione, int y);
const char* get_colore_locazione(const Locazione *locazione);
void set_colore_locazione(Locazione *locazione, const char *colore);
char get_skin_locazione(const Locazione *locazione);
void set_skin_locazione(Locazione *locazione, char skin);
void stampa_locazione(const Locazione *locazione, int x, int y);
void cancella_locazione(const Locazione *locazione, int x, int y);

#endif