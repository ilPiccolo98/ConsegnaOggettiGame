#ifndef SERVER_H
#define SERVER_H
#include <netinet/in.h>
#include <stdbool.h>
#include "../gestione_gioco_server/gestione_gioco_server.h"

typedef struct Server
{
    int socket_descriptor;
    struct sockaddr_in my_address;
    Gestione_gioco_server gestione_gioco;
}
Server;

bool init_server(Server *server, int porta, int quantita_client);
void esegui_server(Server *server);

#endif 