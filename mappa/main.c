#include <stdio.h>
#include "mappa.h"
#include "../console_utility/console_utility.h"
#include <unistd.h>

int main(void)
{   
    Mappa mappa;
    if(init_mappa(&mappa, 10, 10))
        puts("Mappa inizializzata");
    else
        puts("Errore");
    pulisci_console();
    set_at_mappa(&mappa, 1, 0, 'x');
    pulisci_console();
    stampa_mappa(&mappa, 5, 5);
    sleep(1);
    cancella_contenuto_mappa(&mappa, 5, 5);
    return 0;
}