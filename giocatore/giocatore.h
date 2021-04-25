#ifndef GIOCATORE_H
#define GIOCATORE_H
#include <stdbool.h>
#include "../oggetto/oggetto.h"
#include "../costanti/costanti.h"

typedef struct Giocatore
{
    int x;
    int y;
    char skin;
    int id;
    bool connesso;
    bool in_gioco;
    Oggetto *oggetto;
    char account[SIZE_ACCOUNT];
    char colore[SIZE_COLORE]; 
}
Giocatore;

void init_giocatore(Giocatore *giocatore, int x, int y, char skin, bool connesso, bool in_gioco, int id, const char *account);
void stampa_giocatore(const Giocatore *giocatore, int x, int y);
void cancella_giocatore(const Giocatore *giocatore, int x, int y);
int get_x_giocatore(const Giocatore *giocatore);
int get_y_giocatore(const Giocatore *giocatore);
char get_skin_giocatore(const Giocatore *giocatore);
bool set_x_giocatore(Giocatore *giocatore, int x);
bool set_y_giocatore(Giocatore *giocatore, int y);
void set_skin_giocatore(Giocatore *giocatore, char skin);
void set_connesso_giocatore(Giocatore *giocatore, bool connesso);
bool get_connesso_giocatore(const Giocatore *giocatore);
void set_in_gioco_giocatore(Giocatore *giocatore, bool in_gioco);
bool get_in_gioco_giocatore(const Giocatore *giocatore);
void set_id_giocatore(Giocatore *giocatore, int id);
int get_id_giocatore(const Giocatore *giocatore);
void set_account_giocatore(Giocatore *giocatore, const char *account);
const char* get_account_giocatore(const Giocatore *giocatore);
void set_oggetto_giocatore(Giocatore *giocatore, Oggetto *oggetto);
bool ha_oggetto_giocatore(const Giocatore *giocatore);
void scollega_oggetto_giocatore(Giocatore *giocatore);
Oggetto* get_oggetto_giocatore(const Giocatore *giocatore);
void set_colore_giocatore(Giocatore *giocatore, const char *colore);
const char* get_colore_giocatore(const Giocatore *giocatore);
void stampa_account_giocatore(const Giocatore *giocatore, int x, int y);
void cancella_account_giocatore(const Giocatore *giocatore, int x, int y);

#endif