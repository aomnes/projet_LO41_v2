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

int     lire_numero_type_def(int nb_machine)
{
    int d;
    int c;

    do
    {
        scanf("%d", &d);
        while ((c = getchar ()) != '\n' && c != EOF);
    } while(d < 0 || d > nb_machine - 1);
    return (d);
}

int     lire_numero_piece(int nb_piece)
{
    int d;
    int c;

    do
    {
        scanf("%d", &d);
        while ((c = getchar ()) != '\n' && c != EOF);
    } while(d < 0 || d > nb_piece - 1);
    return (d);
}

int trouver_max(int *tab, int nb_element)
{
	int max;
	int index;

	max = tab[0];
	index = 1;
	while (index < nb_element)
	{
		if (max >= tab[index])
			max = tab[index];
		index++;
	}
	return (max);
}
