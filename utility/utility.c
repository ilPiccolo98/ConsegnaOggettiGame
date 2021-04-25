#include "utility.h"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include "../console_utility/console_utility.h"
#include "../keys/keys.h"

//FUNZIONI VISIBILI
int get_line(FILE *file, char *buffer, int size_buffer)
{
    int indice = 0;
    char carattere = (char)getc(file);
    while(carattere != '\n' && carattere != EOF && indice < size_buffer)
    {
        buffer[indice] = carattere;
        ++indice;
        carattere = (char)getc(file);
    }
    return indice;
}

void stampa_aspetta(const char *messaggio)
{
    printf("%s\n", messaggio);
    puts("Premere un pulsante per continuare...");
    getch();
}

int milliseconds_sleep(int milliseconds)
{
    return usleep(milliseconds * 1000);
}

const char* get_ip_address_host(struct sockaddr_in *host_address)
{
    socklen_t len_host = sizeof(*host_address);
    return inet_ntoa(host_address->sin_addr); 
}

const char* get_hostname(struct sockaddr_in *host_address)
{
    socklen_t len_host = sizeof(*host_address);
    struct hostent *host = gethostbyaddr((struct sockaddr*)host_address, len_host, AF_INET);
    return host->h_name;
}

void init_address_host(struct sockaddr_in *host_address, char *ip_address, int porta)  
{
    host_address->sin_family = AF_INET;
    host_address->sin_port = htons(porta);
    if(strlen(ip_address) == 1 && strcmp(ip_address, "0") == 0)
        host_address->sin_addr.s_addr = INADDR_ANY;
    else
        host_address->sin_addr.s_addr = inet_addr(ip_address);
    memset(&host_address->sin_zero, '\0', sizeof(host_address->sin_zero));
}

void get_string(const char *message, char *buffer, int size_buffer, int x, int y)
{
    turn_on_echo();
    muovi_cursore(x, y);
    printf("%s", message);
    muovi_cursore(x, y + 1);
    get_line(stdin, buffer, size_buffer);
    turn_off_echo();
}

time_t get_current_time(void)
{
    time_t current_time;
    time(&current_time);
    return current_time;
}

int random_range(int min, int max)
{
    int x = min + rand() % (max + 1 - min);
    return x;
}

void premi_invio(void)
{
    bool continua = true;
    while(continua)
    {
        int key = getch();
        if(key == KEY_ENTER)
            continua = false; 
    }
}
