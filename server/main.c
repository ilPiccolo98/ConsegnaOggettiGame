#include <stdio.h>
#include <stdlib.h>
#include "server.h"
#include <time.h>
#include "../costanti/costanti.h"

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        puts("Errore numero parametri");
        exit(1);
    }
    Server server;
    int porta = atoi(argv[1]);
    srand(time(NULL));
    if(!init_server(&server, porta, MAX_CLIENTS))
    {
        puts("Errore inizializzazione server");
        exit(1);
    }
    esegui_server(&server);
    return 0;
}