#ifndef UTILITY_H
#define UTILITY_H
#include <stdio.h>
#include <stdbool.h>
#include <netinet/in.h>
#include <time.h>

int get_line(FILE *file, char *buffer, int size_buffer);
void stampa_aspetta(const char *messaggio);
int milliseconds_sleep(int milliseconds);
const char* get_ip_address_host(struct sockaddr_in *host_address);
const char* get_hostname(struct sockaddr_in *host_address);
void init_address_host(struct sockaddr_in *host_address, char *ip_address, int porta);
void get_string(const char *message, char *buffer, int size_buffer, int x, int y);
time_t get_current_time(void);
int random_range(int min, int max);
const char* from_in_to_color(int number);
void premi_invio(void);

#endif 