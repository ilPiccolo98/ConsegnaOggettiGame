#include "gestione_gioco_server.h"
#include <stdlib.h>
#include <string.h>
#include "../utility/utility.h"
#include <stdio.h>
#include "../costanti/costanti.h"
#include "../colori/colori.h"
#include "../utility_gestione_accounts/utility_gestione_accounts.h"
#include <pthread.h>
#define TEMPO_ULTIMA_RICHIESTA 120
#define RIGA_OSTACOLO 6
#define COLONNA_OSTACOLO 2

pthread_mutex_t mutex_set_giocatore_connesso = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_kick_off_account_disconnessi = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_aggiungi_giocatore_in_partita = PTHREAD_MUTEX_INITIALIZER;

//FUNZIONI NON VISIBILI
void set_carattere_in_mappa(Gestione_gioco_server *gioco, int x, int y, char skin)
{
    set_at_mappa(&gioco->mappa, y, x, skin);
}

bool is_there_something_at_position(Gestione_gioco_server *gioco, int x, int y)
{
    char c = get_at_mappa(&gioco->mappa, y, x);
    if(c == ' ')
        return false;
    return true;
}

void init_giocatori_gestione_gioco_server(Gestione_gioco_server *gioco)
{
    int i;
    for(i = 0; i != MAX_CLIENTS; ++i)
        init_giocatore(&gioco->giocatori[i], 0, 0, SKIN_GIOCATORE, false, false, i, "");
}

void init_oggetti_gestione_gioco_server(Gestione_gioco_server *gioco)
{
    int i;
    for(i = 0; i != NUMERO_OGGETTI; ++i)
    {
        int number = random_range(0, 2);
        int x = random_range(1, COLONNE_MAPPA - 2);
        int y = random_range(1, RIGHE_MAPPA - 2);
        while(is_there_something_at_position(gioco, x, y))
        {
            int number = random_range(0, 2);
            x = random_range(1, COLONNE_MAPPA - 2);
            y = random_range(1, RIGHE_MAPPA - 2);
        }
        switch(number)
        {
            case 0:
                init_oggetto(&gioco->oggetti[i], x, y, SKIN_OGGETTO, GIALLO, true);
                break;
            case 1:
                init_oggetto(&gioco->oggetti[i], x, y, SKIN_OGGETTO, BLU, true);
                break;
            case 2:
                init_oggetto(&gioco->oggetti[i], x, y, SKIN_OGGETTO, MAGENTA, true);
                break;
        }
        set_carattere_in_mappa(gioco, x, y, SKIN_OGGETTO);
    }
}

void init_locazioni_gestione_gioco_server(Gestione_gioco_server *gioco)
{
    int i;
    for(i = 0; i != NUMERO_LOCAZIONI; ++i)
    {
        int x = random_range(1, COLONNE_MAPPA - 2);
        int y = random_range(1, RIGHE_MAPPA - 2);
        while(is_there_something_at_position(gioco, x, y))
        {
            x = random_range(1, COLONNE_MAPPA - 2);
            y = random_range(1, RIGHE_MAPPA - 2);
        }
        switch(i)
        {
            case 0:
                init_locazione(&gioco->locazioni[i], x, y, SKIN_LOCAZIONE, GIALLO);
                break;
            case 1:
                init_locazione(&gioco->locazioni[i], x, y, SKIN_LOCAZIONE, BLU);
                break;
            case 2:
                init_locazione(&gioco->locazioni[i], x, y, SKIN_LOCAZIONE, MAGENTA);
                break;
        }
        set_carattere_in_mappa(gioco, x, y, SKIN_LOCAZIONE);
    }
}

bool ci_sono_ostacoli_intorno(Gestione_gioco_server *gioco, int x, int y)
{
    char su = get_at_mappa(&gioco->mappa, y - 1, x);
    char giu = get_at_mappa(&gioco->mappa, y + 1, x);
    char sinistra = get_at_mappa(&gioco->mappa, y, x - 1);
    char destra = get_at_mappa(&gioco->mappa, y, x + 1);
    if(su == SKIN_OSTACOLO && giu == SKIN_OSTACOLO && sinistra == SKIN_OSTACOLO && destra == SKIN_OSTACOLO)
        return true;
    return false;
}

void init_ostacoli_gestione_gioco_server(Gestione_gioco_server *gioco)
{
    int i;
    for(i = 0; i != NUMERO_OSTACOLI; ++i)
    {
        int x = random_range(1, COLONNE_MAPPA - 2);
        int y = random_range(1, RIGHE_MAPPA - 2);
        while(is_there_something_at_position(gioco, x, y) || ci_sono_ostacoli_intorno(gioco, x, y))
        {
            x = random_range(1, COLONNE_MAPPA - 2);
            y = random_range(1, RIGHE_MAPPA - 2);
        }
        init_ostacolo(&gioco->ostacoli[i], x, y, SKIN_OSTACOLO);
        set_carattere_in_mappa(gioco, x, y, SKIN_OSTACOLO);
    }
}

void crea_partita(Gestione_gioco_server *gioco)
{
    init_mappa(&gioco->mappa, RIGHE_MAPPA, COLONNE_MAPPA);
    init_oggetti_gestione_gioco_server(gioco);
    init_locazioni_gestione_gioco_server(gioco);
    init_ostacoli_gestione_gioco_server(gioco);
    gioco->ora_creazione_partita = get_current_time();
}

bool is_una_partita_creata(Gestione_gioco_server *gioco)
{
    int i;
    for(i = 0; i != MAX_CLIENTS; ++i)
        if(get_in_gioco_giocatore(&gioco->giocatori[i]))
            return true;
    return false;
}

void set_array_bool_false(bool array[], int size)
{
    int i;
    for(i = 0; i != size; ++i)
        array[i] = false;
}

void init_ostacoli_visibili(Gestione_gioco_server *gioco, int id)
{
    int i;
    switch(id)
    {
        case 0:
            set_array_bool_false(gioco->ostacoli_visibili_giocatore_uno, NUMERO_OSTACOLI);
            break;
        case 1:
            set_array_bool_false(gioco->ostacoli_visibili_giocatore_due, NUMERO_OSTACOLI);
            break;
        case 2:
            set_array_bool_false(gioco->ostacoli_visibili_giocatore_tre, NUMERO_OSTACOLI);
            break;
    }
}

void join_giocatore_alla_partita(Gestione_gioco_server *gioco, int id)
{
    Giocatore *g = &gioco->giocatori[id];
    int x = random_range(1, COLONNE_MAPPA - 2);
    int y = random_range(1, RIGHE_MAPPA - 2);
    while(is_there_something_at_position(gioco, x, y))
    {
        x = random_range(1, COLONNE_MAPPA - 2);
        y = random_range(1, RIGHE_MAPPA - 2);    
    }
    set_x_giocatore(g, x);
    set_y_giocatore(g, y);
    set_skin_giocatore(g, SKIN_GIOCATORE);
    set_in_gioco_giocatore(g, true);
    set_carattere_in_mappa(gioco, x, y, SKIN_GIOCATORE);
    init_ostacoli_visibili(gioco, id);
    gioco->punti[id] = 0;
} 

bool check_id(int id)
{
    if(id >= 0 && id < MAX_CLIENTS)
        return true;
    return false;
}

bool is_there_a_collision(Gestione_gioco_server *gioco, int x, int y)
{
    char c = get_at_mappa(&gioco->mappa, y, x);
    if(c == ' ')
        return false;
    return true;
}

bool is_there_an_object(Gestione_gioco_server *gioco, int x, int y)
{
    char c = get_at_mappa(&gioco->mappa, y, x);
    if(c == SKIN_OGGETTO)
        return true;
    return false;
}

bool is_there_a_location(Gestione_gioco_server *gioco, int x, int y)
{
    char c = get_at_mappa(&gioco->mappa, y, x);
    if(c == SKIN_LOCAZIONE)
        return true;
    return false;
}

bool is_giocatore_su_un_oggetto(Gestione_gioco_server *gioco, int x, int y)
{
    char c = get_at_mappa(&gioco->mappa, y, x);
    if(c == SKIN_GIOCATORE_SU_OGGETTO || c == SKIN_GIOCATORE_CON_OGGETTO_SU_OGGETTO)
        return true;
    return false;
}

bool is_giocatore_su_una_locazione(Gestione_gioco_server *gioco, int x, int y)
{
    char c = get_at_mappa(&gioco->mappa, y, x);
    if(c == SKIN_GIOCATORE_CON_OGGETTO_SU_LOCAZIONE || c == SKIN_GIOCATORE_SU_LOCAZIONE)
        return true;
    return false;
}

void cambia_posizione_giocatore_gioco_server(Gestione_gioco_server *gioco, Giocatore *giocatore, int nuova_x, int nuova_y, char nuova_skin)
{
    set_x_giocatore(giocatore, nuova_x);
    set_y_giocatore(giocatore, nuova_y);
    set_skin_giocatore(giocatore, nuova_skin);
    set_carattere_in_mappa(gioco, nuova_x, nuova_y, nuova_skin);
}

void cancella_vecchia_posizione_giocatore_gioco_server(Gestione_gioco_server *gioco, int x, int y)
{
    if(is_giocatore_su_una_locazione(gioco, x, y))
        set_carattere_in_mappa(gioco, x, y, SKIN_LOCAZIONE);
    else if(is_giocatore_su_un_oggetto(gioco, x, y))
        set_carattere_in_mappa(gioco, x, y, SKIN_OGGETTO);
    else
        set_carattere_in_mappa(gioco, x, y, ' ');
}

Oggetto* get_oggetto_nella_posizione_gioco_server(Gestione_gioco_server *gioco, int x, int y)
{
    int i;
    for(i = 0; i != NUMERO_OGGETTI; ++i)
    {
        int x_oggetto = get_x_oggetto(&gioco->oggetti[i]);
        int y_oggetto = get_y_oggetto(&gioco->oggetti[i]);
        if(x_oggetto == x && y_oggetto == y)
            return &gioco->oggetti[i];
    }
    return NULL;
}

Locazione* get_locazione_nella_posizione_gioco_server(Gestione_gioco_server *gioco, int x, int y)
{
    int i;
    for(i = 0; i != NUMERO_LOCAZIONI; ++i)
    {
        int x_locazione = get_x_locazione(&gioco->locazioni[i]);
        int y_locazione = get_y_locazione(&gioco->locazioni[i]);
        if(x_locazione == x && y_locazione == y)
            return &gioco->locazioni[i];
    }
    return NULL;
}

bool is_there_an_obstacle(Gestione_gioco_server *gioco, int x, int y)
{
    char c = get_at_mappa(&gioco->mappa, y, x);
    if(c == SKIN_OSTACOLO)
        return true;
    return false;
}

int get_index_ostacolo_nella_posizione(Gestione_gioco_server *gioco, int x, int y)
{
    int i;
    for(i = 0; i != NUMERO_OSTACOLI; ++i)
    {
        Ostacolo *ostacolo = &gioco->ostacoli[i];
        if(x == get_x_ostacolo(ostacolo) && y == get_y_ostacolo(ostacolo))
            return i;
    }
    return -1;
}

void set_ostacolo_visibile_true(Gestione_gioco_server *gioco, int id_giocatore, int index_ostacolo)
{
    switch(id_giocatore)
    {
        case 0:
            gioco->ostacoli_visibili_giocatore_uno[index_ostacolo] = true;
            break;
        case 1:
            gioco->ostacoli_visibili_giocatore_due[index_ostacolo] = true;
            break;
        case 2:
            gioco->ostacoli_visibili_giocatore_tre[index_ostacolo] = true;
            break;
    }
}

//FUNZIONI VISIBILI
void init_gestione_gioco_server(Gestione_gioco_server *gioco)
{
    init_mappa(&gioco->mappa, RIGHE_MAPPA, COLONNE_MAPPA);
    init_giocatori_gestione_gioco_server(gioco);
}

int set_giocatore_connesso(Gestione_gioco_server *gioco, const char *account)
{
    pthread_mutex_lock(&mutex_set_giocatore_connesso);
    int i;
    for(i = 0; i != MAX_CLIENTS; ++i)
        if(!get_connesso_giocatore(&gioco->giocatori[i]))
        {
            set_connesso_giocatore(&gioco->giocatori[i], true);
            set_account_giocatore(&gioco->giocatori[i], account);
            pthread_mutex_unlock(&mutex_set_giocatore_connesso);
            return i;
        }
    pthread_mutex_unlock(&mutex_set_giocatore_connesso);
    return -1;
}

void set_giocatore_disconnesso(Gestione_gioco_server *gioco, int id)
{
    set_connesso_giocatore(&gioco->giocatori[id], false);
}

bool is_giocatore_connesso_by_account(Gestione_gioco_server *gioco, const char *account)
{
    int i;
    for(i = 0; i != MAX_CLIENTS; ++i)
        if(get_connesso_giocatore(&gioco->giocatori[i]) && strcmp(account, get_account_giocatore(&gioco->giocatori[i])) == 0)
            return true;
    return false;
}

bool is_giocatore_in_gioco_by_account(Gestione_gioco_server *gioco, const char *account)
{
    int i;
    for(i = 0; i != MAX_CLIENTS; ++i)
        if(get_in_gioco_giocatore(&gioco->giocatori[i]) && strcmp(account, get_account_giocatore(&gioco->giocatori[i])) == 0)
            return true;
    return false;
}

bool is_giocatore_connesso_by_id(Gestione_gioco_server *gioco, int id)
{
    return get_connesso_giocatore(&gioco->giocatori[id]);
}

bool is_giocatore_in_gioco_by_id(Gestione_gioco_server *gioco, int id)
{
    return get_in_gioco_giocatore(&gioco->giocatori[id]);
}

const char *get_account_by_id(Gestione_gioco_server *gioco, int id)
{
    if(id >= 0 && id < MAX_CLIENTS)
        return get_account_giocatore(&gioco->giocatori[id]);
    return NULL;
}

void set_ultima_richiesta_al_tempo_corrente(Gestione_gioco_server *gioco, int id)
{
    if(check_id(id))
        gioco->ultima_richiesta[id] = get_current_time();
}

time_t get_ultima_richiesta(Gestione_gioco_server *gioco, int id)
{
    if(check_id(id))
        return gioco->ultima_richiesta[id];
    return 0;
}

void kick_off_account_disconnessi(Gestione_gioco_server *gioco)
{
    pthread_mutex_lock(&mutex_kick_off_account_disconnessi);
    time_t current_time = get_current_time();
    int i;
    for(i = 0; i != MAX_CLIENTS; ++i)
        if(get_connesso_giocatore(&gioco->giocatori[i]) && (int)difftime(current_time, gioco->ultima_richiesta[i]) >= TEMPO_ULTIMA_RICHIESTA)
        {    
            set_connesso_giocatore(&gioco->giocatori[i], false);
            set_in_gioco_giocatore(&gioco->giocatori[i], false);
        }
    pthread_mutex_unlock(&mutex_kick_off_account_disconnessi);
}

void aggiungi_giocatore_in_partita(Gestione_gioco_server *gioco, int id)
{
    if(check_id(id))
    {
        pthread_mutex_lock(&mutex_aggiungi_giocatore_in_partita);
        if(!is_una_partita_creata(gioco))
            crea_partita(gioco);
        join_giocatore_alla_partita(gioco, id);
        pthread_mutex_unlock(&mutex_aggiungi_giocatore_in_partita);
    }
}

void rimuovi_giocatore_dalla_partita(Gestione_gioco_server *gioco, int id)
{
    if(check_id(id))
    {
        set_in_gioco_giocatore(&gioco->giocatori[id], false);
        scollega_oggetto_giocatore(&gioco->giocatori[id]);
        set_colore_giocatore(&gioco->giocatori[id], VERDE);
    }
}

void muovi_giocatore_su(Gestione_gioco_server *gioco, int id)
{
    if(check_id(id))
    {
        Giocatore *g = &gioco->giocatori[id];
        int y = get_y_giocatore(g);
        int x = get_x_giocatore(g);
        int skin = get_skin_giocatore(g);
        if(is_there_a_location(gioco, x, y - 1))
        {
            if(!ha_oggetto_giocatore(g))
                cambia_posizione_giocatore_gioco_server(gioco, g, x, y - 1, SKIN_GIOCATORE_SU_LOCAZIONE);
            else  
                cambia_posizione_giocatore_gioco_server(gioco, g, x, y - 1, SKIN_GIOCATORE_CON_OGGETTO_SU_LOCAZIONE);
            cancella_vecchia_posizione_giocatore_gioco_server(gioco, x, y);
        }
        else if(is_there_an_object(gioco, x, y - 1))
        {
            if(!ha_oggetto_giocatore(g))
                cambia_posizione_giocatore_gioco_server(gioco, g, x, y - 1, SKIN_GIOCATORE_SU_OGGETTO);
            else
                cambia_posizione_giocatore_gioco_server(gioco, g, x, y - 1, SKIN_GIOCATORE_CON_OGGETTO_SU_OGGETTO);
            cancella_vecchia_posizione_giocatore_gioco_server(gioco, x, y);
        }
        else if(!is_there_a_collision(gioco, x, y - 1))
        {   
            if(ha_oggetto_giocatore(g))
                skin = SKIN_GIOCATORE_CON_OGGETTO;
            else
                skin = SKIN_GIOCATORE;
            cambia_posizione_giocatore_gioco_server(gioco, g, x, y - 1, skin);
            cancella_vecchia_posizione_giocatore_gioco_server(gioco, x, y);
        }
        else if(is_there_an_obstacle(gioco, x, y - 1))
        {
            int index_ostacolo = get_index_ostacolo_nella_posizione(gioco, x, y - 1);
            set_ostacolo_visibile_true(gioco, id, index_ostacolo);
        }
    }
}

void muovi_giocatore_giu(Gestione_gioco_server *gioco, int id)
{
    if(check_id(id))
    {
        Giocatore *g = &gioco->giocatori[id];
        int y = get_y_giocatore(g);
        int x = get_x_giocatore(g);
        int skin = get_skin_giocatore(g);
        if(is_there_a_location(gioco, x, y + 1))
        {
            if(!ha_oggetto_giocatore(g))
                cambia_posizione_giocatore_gioco_server(gioco, g, x, y + 1, SKIN_GIOCATORE_SU_LOCAZIONE);
            else
                cambia_posizione_giocatore_gioco_server(gioco, g, x, y + 1, SKIN_GIOCATORE_CON_OGGETTO_SU_LOCAZIONE);
            cancella_vecchia_posizione_giocatore_gioco_server(gioco, x, y);
        }
        else if(is_there_an_object(gioco, x, y + 1))
        {    
            if(!ha_oggetto_giocatore(g))
                cambia_posizione_giocatore_gioco_server(gioco, g, x, y + 1, SKIN_GIOCATORE_SU_OGGETTO);
            else
                cambia_posizione_giocatore_gioco_server(gioco, g, x, y + 1, SKIN_GIOCATORE_CON_OGGETTO_SU_OGGETTO);
            cancella_vecchia_posizione_giocatore_gioco_server(gioco, x, y);
        }
        else if(!is_there_a_collision(gioco, x, y + 1))
        {    
            if(ha_oggetto_giocatore(g))
                skin = SKIN_GIOCATORE_CON_OGGETTO;
            else
                skin = SKIN_GIOCATORE;
            cambia_posizione_giocatore_gioco_server(gioco, g, x, y + 1, skin);
            cancella_vecchia_posizione_giocatore_gioco_server(gioco, x, y);
        }
        else if(is_there_an_obstacle(gioco, x, y + 1))
        {
            int index_ostacolo = get_index_ostacolo_nella_posizione(gioco, x, y + 1);
            set_ostacolo_visibile_true(gioco, id, index_ostacolo);
        }
    }
}

void muovi_giocatore_sinistra(Gestione_gioco_server *gioco, int id)
{
    if(check_id(id))
    {
        Giocatore *g = &gioco->giocatori[id];
        int y = get_y_giocatore(g);
        int x = get_x_giocatore(g);
        int skin = get_skin_giocatore(g);
        if(is_there_a_location(gioco, x - 1, y))
        {
            if(!ha_oggetto_giocatore(g))
                cambia_posizione_giocatore_gioco_server(gioco, g, x - 1, y, SKIN_GIOCATORE_SU_LOCAZIONE);
            else
                cambia_posizione_giocatore_gioco_server(gioco, g, x - 1, y, SKIN_GIOCATORE_CON_OGGETTO_SU_LOCAZIONE);
            cancella_vecchia_posizione_giocatore_gioco_server(gioco, x, y);
        }
        else if(is_there_an_object(gioco, x - 1, y))
        {
            if(!ha_oggetto_giocatore(g))
                cambia_posizione_giocatore_gioco_server(gioco, g, x - 1, y, SKIN_GIOCATORE_SU_OGGETTO);
            else 
                cambia_posizione_giocatore_gioco_server(gioco, g, x - 1, y, SKIN_GIOCATORE_CON_OGGETTO_SU_OGGETTO);
            cancella_vecchia_posizione_giocatore_gioco_server(gioco, x, y);
        }
        else if(!is_there_a_collision(gioco, x - 1, y))
        {
            if(ha_oggetto_giocatore(g))
                skin = SKIN_GIOCATORE_CON_OGGETTO;
            else
                skin = SKIN_GIOCATORE; 
            cambia_posizione_giocatore_gioco_server(gioco, g, x - 1, y, skin);
            cancella_vecchia_posizione_giocatore_gioco_server(gioco, x, y);
        }
        else if(is_there_an_obstacle(gioco, x - 1, y))
        {
            int index_ostacolo = get_index_ostacolo_nella_posizione(gioco, x - 1, y);
            set_ostacolo_visibile_true(gioco, id, index_ostacolo);
        }
    }
}

void muovi_giocatore_destra(Gestione_gioco_server *gioco, int id)
{
    if(check_id(id))
    {
        Giocatore *g = &gioco->giocatori[id];
        int y = get_y_giocatore(g);
        int x = get_x_giocatore(g);
        int skin = get_skin_giocatore(g);
        if(is_there_a_location(gioco, x + 1, y))
        {
            if(!ha_oggetto_giocatore(g))
                cambia_posizione_giocatore_gioco_server(gioco, g, x + 1, y, SKIN_GIOCATORE_SU_LOCAZIONE);
            else
                cambia_posizione_giocatore_gioco_server(gioco, g, x + 1, y, SKIN_GIOCATORE_CON_OGGETTO_SU_LOCAZIONE);
            cancella_vecchia_posizione_giocatore_gioco_server(gioco, x, y);
        }
        else if(is_there_an_object(gioco, x + 1, y))
        {   
            if(!ha_oggetto_giocatore(g))
                cambia_posizione_giocatore_gioco_server(gioco, g, x + 1, y, SKIN_GIOCATORE_SU_OGGETTO);
            else
                cambia_posizione_giocatore_gioco_server(gioco, g, x + 1, y, SKIN_GIOCATORE_CON_OGGETTO_SU_OGGETTO);
            cancella_vecchia_posizione_giocatore_gioco_server(gioco, x, y);
        }
        else if(!is_there_a_collision(gioco, x + 1, y))
        {
            if(ha_oggetto_giocatore(g))
                skin = SKIN_GIOCATORE_CON_OGGETTO;
            else
                skin = SKIN_GIOCATORE; 
            cambia_posizione_giocatore_gioco_server(gioco, g, x + 1, y, skin);
            cancella_vecchia_posizione_giocatore_gioco_server(gioco, x, y);
        }
        else if(is_there_an_obstacle(gioco, x + 1, y))
        {
            int index_ostacolo = get_index_ostacolo_nella_posizione(gioco, x + 1, y);
            set_ostacolo_visibile_true(gioco, id, index_ostacolo);
        }  
    }
}

void prendi_oggetto_gestione_gioco_server(Gestione_gioco_server *gioco, int id)
{
    Giocatore *g = &gioco->giocatori[id];
    int x = get_x_giocatore(g);
    int y = get_y_giocatore(g);
    if(is_giocatore_su_un_oggetto(gioco, x, y) && !ha_oggetto_giocatore(g))
    {
        Oggetto *oggetto = get_oggetto_nella_posizione_gioco_server(gioco, x, y);
        if(oggetto)
        {
            set_oggetto_giocatore(g, oggetto);
            set_colore_giocatore(g, get_colore_oggetto(oggetto));
            set_skin_giocatore(g, SKIN_GIOCATORE_CON_OGGETTO);
            set_carattere_in_mappa(gioco, x, y, SKIN_GIOCATORE_CON_OGGETTO);
        }
    }
}

void lascia_oggetto_gestione_gioco_server(Gestione_gioco_server *gioco, int id, const char *ip_address, const char *hostname)
{
    Giocatore *g = &gioco->giocatori[id];
    int x = get_x_giocatore(g);
    int y = get_y_giocatore(g);
    char skin = get_skin_giocatore(g);
    if(ha_oggetto_giocatore(g) && skin != SKIN_GIOCATORE_CON_OGGETTO_SU_OGGETTO)
    {   
        if(skin == SKIN_GIOCATORE_CON_OGGETTO_SU_LOCAZIONE)
        {
            Oggetto *o = get_oggetto_giocatore(g);
            Locazione *l = get_locazione_nella_posizione_gioco_server(gioco, x, y);
            if(strcmp(get_colore_locazione(l), get_colore_oggetto(o)) == 0)
            {
                scollega_oggetto_giocatore(g);
                set_colore_giocatore(g, VERDE);
                set_skin_giocatore(g, SKIN_GIOCATORE_SU_LOCAZIONE);
                set_carattere_in_mappa(gioco, x, y, SKIN_GIOCATORE_SU_LOCAZIONE);
                set_visibile_oggetto(o, false);
                ++gioco->punti[id];
                const char *account = get_account_by_id(gioco, id);
                registra_operazione_account(account, hostname, ip_address, "Il giocatore ha fatto punto");
            }
        }
        else
        {
            scollega_oggetto_giocatore(g);
            set_colore_giocatore(g, VERDE);
            set_skin_giocatore(g, SKIN_GIOCATORE_SU_OGGETTO);
            set_carattere_in_mappa(gioco, x, y, SKIN_GIOCATORE_SU_OGGETTO);
        }
    }
}

void set_giocatori_tutti_non_in_gioco(Gestione_gioco_server *gioco)
{
    int i;
    for(i = 0; i != MAX_CLIENTS; ++i)
    {
        gioco->giocatori[i].in_gioco = false;
        scollega_oggetto_giocatore(&gioco->giocatori[i]);
        set_colore_giocatore(&gioco->giocatori[i], VERDE);
    }
}
