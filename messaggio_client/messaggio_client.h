#ifndef MESSAGGI_CLIENT_H
#define MESSAGGI_CLIENT_H

typedef enum Messaggio_client
{
    LOGIN_CLIENT, CREA_ACCOUNT_CLIENT, ERRORE_CLIENT, LOGOUT_CLIENT, ENTRA_IN_PARTITA_CLIENT,
    ESCI_DALLA_PARTITA_CLIENT, MUOVI_SU_CLIENT, MUOVI_GIU_CLIENT, MUOVI_SINISTRA_CLIENT, MUOVI_DESTRA_CLIENT,
    AGGIORNA_INFO_CLIENT, PRENDI_OGGETTO_CLIENT, LASCIA_OGGETTO_CLIENT, INIZIA_NUOVA_SESSIONE, UPDATE_LITE_INFO_CLIENT,
    FINE_PARTITA
}
Messaggio_client;

#endif