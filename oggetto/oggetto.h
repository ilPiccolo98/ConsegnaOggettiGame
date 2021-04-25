#ifndef OGGETTO_H
#define OGGETTO_H
#include <stdbool.h>
#include "../costanti/costanti.h"

typedef struct Oggetto
{
    int x;
    int y;
    char skin;
    char colore[SIZE_COLORE];
    bool visibile;
}
Oggetto;

void init_oggetto(Oggetto *oggetto, int x, int y, char skin, const char *colore, bool visibile);
void stampa_oggetto(const Oggetto *oggetto, int x, int y);
void cancella_oggetto(const Oggetto *oggetto, int x, int y);
int get_x_oggetto(const Oggetto *oggetto);
int get_y_oggetto(const Oggetto *oggetto);
char get_skin_oggetto(const Oggetto *oggetto);
bool set_x_oggetto(Oggetto *oggetto, int x);
bool set_y_oggetto(Oggetto *oggetto, int y);
void set_skin_oggetto(Oggetto *oggetto, char skin);
const char *get_colore_oggetto(const Oggetto *oggetto);
void set_colore_oggetto(Oggetto *oggetto, const char *colore);
bool is_visibile_oggetto(const Oggetto *oggetto);
void set_visibile_oggetto(Oggetto *oggetto, bool visibile);

#endif