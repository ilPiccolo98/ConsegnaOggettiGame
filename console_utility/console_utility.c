#include "console_utility.h"
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <stdlib.h>

void muovi_cursore(int x, int y)
{
	printf("\033[%d;%dH", y, x);
}

void set_colore_console(const char *colore)
{
    printf("%s", colore);
}

int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

int kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    if(ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}

void mostra_cursore(void)
{
    system("setterm -cursor on");
}

void nascondi_cursore(void)
{
    system("setterm -cursor off");
}

void pulisci_console(void)
{
    system("clear");
}
 
void clear_buffer_console(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

void turn_on_echo(void)
{
    system("stty echo");
}

void turn_off_echo(void)
{
    system("stty -echo");
}