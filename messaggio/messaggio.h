#ifndef MESSAGGIO_H
#define MESSAGGIO_H

typedef struct Messaggio
{
    const char *messaggio;
    int x;
    int y;
}
Messaggio;

void init_messaggio(Messaggio *m, const char *messaggio, int x, int y);
void stampa_messaggio(const Messaggio *m);
void set_messaggio(Messaggio *m, const char *messaggio);
void set_x_messaggio(Messaggio *m, int x);
void set_y_messaggio(Messaggio *m, int y);
const char* get_messaggio(const Messaggio *m);
int get_x_messaggio(const Messaggio *m);
int get_y_messaggio(const Messaggio *m);

#endif