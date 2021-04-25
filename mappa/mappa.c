#include "mappa.h"
#include <stdlib.h>
#include <stdio.h>
#include "../console_utility/console_utility.h"
#define ERROR_GET_AT_MAPPA -300
#define BORDI_RIGHE 2
#define BORDI_COLONNE 2

//FUNZIONI NON VISIBILI
bool is_righe_minore_di_max_righe(int righe)
{
    if(righe > 0 && righe <= MAX_RIGHE_MAPPA)
        return true;
    return false;
}

bool is_colonne_minore_di_max_colonne(int colonne)
{
    if(colonne > 0 && colonne <= MAX_COLONNE_MAPPA)
        return true;
    return false;
}

char get_token(int riga, int colonna, int righe, int colonne)
{
    if((!riga && !colonna) || (!riga && colonna == (colonne - 1)) || 
       (riga == (righe - 1) && !colonna) || (riga == (righe - 1) && colonna == (colonne - 1)))
       return '+';
    else if(!riga || riga == (righe - 1))
        return '-';
    else if(!colonna || colonna == (colonne - 1))
        return '|';
    return ' ';
}

void set_bordi_mappa(Mappa *mappa)
{
    int riga, colonna;
    for(riga = 0; riga != mappa->righe; ++riga)
        for(colonna = 0; colonna != mappa->colonne; ++colonna)
        {
            char token = get_token(riga, colonna, mappa->righe, mappa->colonne);
            mappa->matrice[riga][colonna] = token;
        }
}

bool is_riga_corretta(const Mappa *mappa, int riga)
{
    if(riga >= mappa->righe || riga < 1)
        return false;
    return true;
}

bool is_colonna_corretta(const Mappa *mappa, int colonna)
{
    if(colonna >= mappa->colonne || colonna < 1)
        return false;
    return true;
}

//FUNZIONI VISIBILI
bool init_mappa(Mappa *mappa, int righe, int colonne)
{
    if(!is_righe_minore_di_max_righe(righe) || !is_colonne_minore_di_max_colonne(colonne))
        return false;
    mappa->righe = righe + BORDI_RIGHE;
    mappa->colonne = colonne + BORDI_COLONNE;
    set_bordi_mappa(mappa);
    return true;
}

int get_at_mappa(const Mappa *mappa, int riga, int colonna)
{
    if(is_riga_corretta(mappa, riga) && is_colonna_corretta(mappa, colonna))
        return (int)mappa->matrice[riga][colonna];
    return ERROR_GET_AT_MAPPA; 
}

bool set_at_mappa(Mappa *mappa, int riga, int colonna, char carattere)
{
    if(is_riga_corretta(mappa, riga) && is_colonna_corretta(mappa, colonna))
    {
        mappa->matrice[riga][colonna] = carattere;
        return true;
    }
    return false;
}

void stampa_mappa(const Mappa *mappa, int x, int y)
{
    int riga, colonna;
    for(riga = 0; riga != mappa->righe; ++riga)
        for(colonna = 0; colonna != mappa->colonne; ++colonna)
        {
            muovi_cursore(x + colonna, y + riga);
            putchar(mappa->matrice[riga][colonna]);
        }
}

int get_righe(const Mappa *mappa)
{
    return mappa->righe;
}

int get_colonne(const Mappa *mappa)
{
    return mappa->colonne;
}

void cancella_mappa(const Mappa *mappa, int x, int y)
{
    int riga, colonna;
    for(riga = 0; riga != mappa->righe; ++riga)
        for(colonna = 0; colonna != mappa->colonne; ++colonna)
        {
            muovi_cursore(x + colonna, y + riga);
            putchar(' ');
        }
}

void destroy_mappa(Mappa *mappa)
{
    mappa->righe = 0;
    mappa->colonne = 0;
}

void cancella_contenuto_mappa(const Mappa *mappa, int x, int y)
{
    int riga;
    for(riga = 1; riga != mappa->righe - 1; ++riga)
    {
        int colonna;
        for(colonna = 1; colonna != mappa->colonne - 1; ++colonna)
        {
            muovi_cursore(colonna + x, riga + y);
            putchar(' ');
        }
    }
}
