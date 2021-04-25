#include <stdio.h>
#include "giocatore.h"

int main(void)
{
    Giocatore giocatore;
    init_giocatore(&giocatore, 0, 0, 'x', false, false, 0, "");
    printf("Account: %s\n", get_account_giocatore(&giocatore));
    const char *account = "giuseppe";
    set_account_giocatore(&giocatore, account);
    printf("Account: %s\n", get_account_giocatore(&giocatore));
    return 0;
}