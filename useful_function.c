#include "header.h"

void		error(char *msg)
{
	perror(msg);
	exit(0);
}

int     lire_nombre_sp(void)
{
    int d;
    int c;

    do
    {
        scanf("%d", &d);
        while ((c = getchar ()) != '\n' && c != EOF);
    } while(d <= 0);
    return (d);
}

int     lire_nombre_p(void)
{
    int d;
    int c;

    do
    {
        scanf("%d", &d);
        while ((c = getchar ()) != '\n' && c != EOF);
    } while(d < 0);
    return (d);
}

int     lire_nombre_defaut(void)
{
    int d;
    int c;

    do
    {
        scanf("%d", &d);
        while ((c = getchar ()) != '\n' && c != EOF);
    } while(d < 0 || d > 4);
    return (d);
}
