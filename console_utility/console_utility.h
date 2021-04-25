#ifndef CONSOLE_UTILITY_H
#define CONSOLE_UTILITY_H

void muovi_cursore(int x, int y);
void set_colore_console(const char *colore);
int getch(void);
int getche(void);
int kbhit(void);
void mostra_cursore(void);
void nascondi_cursore(void);
void pulisci_console(void);
void clear_buffer_console(void);
void turn_on_echo(void);
void turn_off_echo(void);

#endif