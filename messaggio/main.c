#include <stdio.h>
#include <stdlib.h>
#include "messaggio.h"

int main(void)
{
    Messaggio inizio_gioco;
    Messaggio esci;
    system("clear");
    init_messaggio(&inizio_gioco, "Inizia gioco", 4, 5);
    init_messaggio(&esci, "Esci", 4, 6);
    stampa_messaggio(&inizio_gioco);
    stampa_messaggio(&esci);
    return 0;
}