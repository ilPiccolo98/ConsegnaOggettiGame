#ifndef UTILITY_GESTIONE_ACCOUNTS_H
#define UTILITY_GESTIONE_ACCOUNTS_H
#include <stdbool.h>

bool is_account_esistente(const char *account);
bool aggiungi_account(const char *account, const char *password);
bool matching_account(const char *account, const char *password);
bool registra_operazione_account(const char *account, const char *hostname, const char *ip_address, const char *operazione);

#endif