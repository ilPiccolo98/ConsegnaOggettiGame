#include "utility_gestione_accounts.h"
#include <stdio.h>
#include <string.h>
#include "../costanti/costanti.h"
#include "../utility/utility.h"
#include <pthread.h>

pthread_mutex_t mutex_aggiungi_account = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_registra_operazione_account = PTHREAD_MUTEX_INITIALIZER;


//FUNZIONI VISIBILI
bool is_account_esistente(const char *account)
{
    FILE *file_lettura = fopen(ACCOUNTS_FILE, "r");
    if(!file_lettura)
        return false;
    char account_file[SIZE_ACCOUNT] = "\0";
    char password[SIZE_PASSWORD] = "\0";
    while(!feof(file_lettura))
    {
        fscanf(file_lettura, "%s", account_file);
        fscanf(file_lettura, "%s", password);
        if(strcmp(account, account_file) == 0)
        {
            fclose(file_lettura);
            return true;
        }
    }
    fclose(file_lettura);
    return false;
}

bool aggiungi_account(const char *account, const char *password)
{
    FILE *file_scrittura = fopen(ACCOUNTS_FILE, "a");
    if(file_scrittura)
    {
        pthread_mutex_lock(&mutex_aggiungi_account);
        fprintf(file_scrittura, "%s\n", account);
        fprintf(file_scrittura, "%s\n", password);
        pthread_mutex_unlock(&mutex_aggiungi_account);
        fclose(file_scrittura);
        return true;
    }
    return false;
}

bool matching_account(const char *account, const char *password)
{
    FILE *file_lettura = fopen(ACCOUNTS_FILE, "r");
    if(!file_lettura)
        return false;
    else
    {
        char account_file[SIZE_ACCOUNT] = "\0";
        char password_file[SIZE_PASSWORD] = "\0";
        while(!feof(file_lettura))
        {
            fscanf(file_lettura, "%s", account_file);
            fscanf(file_lettura, "%s", password_file);
            if(strcmp(account_file, account) == 0 && strcmp(password_file, password) == 0)
            {
                fclose(file_lettura);
                return true;
            }
        }
    }
    fclose(file_lettura);
    return false;
}

bool registra_operazione_account(const char *account, const char *hostname, const char *ip_address, const char *operazione)
{
    FILE *file_scrittura = fopen(OPERATIONS_FILE, "a");
    if(file_scrittura)
    {
        pthread_mutex_lock(&mutex_registra_operazione_account);
        time_t time = get_current_time();
        struct tm *time_info = localtime(&time);
        fprintf(file_scrittura, "%s\n", operazione);
        fprintf(file_scrittura, "%s\n", account);
        fprintf(file_scrittura, "%s\n", hostname);
        fprintf(file_scrittura, "%s\n", ip_address);
        fprintf(file_scrittura, "%s\n\n", asctime(time_info));
        pthread_mutex_unlock(&mutex_registra_operazione_account);
        fclose(file_scrittura);
        return true;
    }
    return false;
}
