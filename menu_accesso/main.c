#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include "../utility/utility.h"
#include "../console_utility/console_utility.h"
#include "menu_accesso.h"

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        puts("Errore paramentri");
        exit(1);
    }
    int porta = atoi(argv[2]);
    struct sockaddr_in server_address;
    init_address_host(&server_address, argv[1], porta);    
    nascondi_cursore();
    turn_off_echo();
    Menu_accesso menu;
    init_menu_accesso(&menu, &server_address);
    esegui_menu_accesso(&menu);
    turn_on_echo();
    mostra_cursore();
    return 0;
}