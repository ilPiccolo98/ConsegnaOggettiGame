#ifndef MAPPA_H
#define MAPPA_H
#include <stdbool.h>
#define MAX_RIGHE_MAPPA 300
#define MAX_COLONNE_MAPPA 300

typedef struct Mappa
{
    char matrice[MAX_RIGHE_MAPPA][MAX_COLONNE_MAPPA];
    int righe;
    int colonne;
}
Mappa;

bool init_mappa(Mappa *mappa, int righe, int colonne);
int get_at_mappa(const Mappa *mappa, int riga, int colonna);
bool set_at_mappa(Mappa *mappa, int riga, int colonna, char carattere);
void stampa_mappa(const Mappa *mappa, int x, int y);
int get_righe(const Mappa *mappa);
int get_colonne(const Mappa *mappa);
void cancella_mappa(const Mappa *mappa, int x, int y);
void destroy_mappa(Mappa *mappa);
void cancella_contenuto_mappa(const Mappa *mappa, int x, int y);

#endif