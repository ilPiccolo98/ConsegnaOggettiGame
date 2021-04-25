#ifndef OSTACOLO_H
#define OSTACOLO_H

typedef struct Ostacolo
{
    int x;
    int y;
    char skin;
}
Ostacolo;

void init_ostacolo(Ostacolo *ostacolo, int x, int y, char skin);
int get_x_ostacolo(const Ostacolo *ostacolo);
void set_x_ostacolo(Ostacolo *ostacolo, int x);
int get_y_ostacolo(const Ostacolo *ostacolo);
void set_y_ostacolo(Ostacolo *ostacolo, int y);
char get_skin_ostacolo(const Ostacolo *ostacolo);
void set_skin_ostacolo(Ostacolo *ostacolo, char skin);
void stampa_ostacolo(const Ostacolo *ostacolo, int x, int y);
void cancella_ostacolo(const Ostacolo *ostacolo, int x, int y);

#endif 