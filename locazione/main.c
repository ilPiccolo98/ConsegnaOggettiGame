#include <stdio.h>
#include "locazione.h"
#include "../colori/colori.h"
#include "../console_utility/console_utility.h"

int main(void)
{
    Locazione locazione;
    init_locazione(&locazione, 3, 6, SKIN_LOCAZIONE, BLU);
    pulisci_console();
    stampa_locazione(&locazione, 0, 0);
    cancella_locazione(&locazione, 0, 0);
    return 0;
}