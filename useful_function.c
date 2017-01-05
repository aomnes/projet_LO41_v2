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

void creation_sem_msg(void)
{
	CLEF_1 = ftok("/msgid_in", 'A');
	CLEF_2 = ftok("/msgid_rbt_inst_table", 'A');
	CLEF_3 = ftok("/msgid_machine", 'A');
	CLEF_4 = ftok("/msgid_cmpt_rendu_mach", 'A');
	CLEF_5 = ftok("/msgid_fin_go", 'A');
	CLEF_6 = ftok("/msgid_out", 'A');
	if ((msgid_in = msgget(CLEF_1, IPC_CREAT | IPC_EXCL | 0600)) == -1)
		error("msgget Robot_in");
	if ((msgid_rbt_inst_table = msgget(CLEF_2, IPC_CREAT | IPC_EXCL | 0600)) == -1)
		error("msgget msgid_rbt_inst_table");
	if ((msgid_machine = msgget(CLEF_3, IPC_CREAT | IPC_EXCL | 0600)) == -1)
		error("msgget msgid_machine");
	if ((msgid_cmpt_rendu_mach = msgget(CLEF_4, IPC_CREAT | IPC_EXCL | 0600)) == -1)
		error("msgget msgid_cmpt_rendu_mach");
	if ((msgid_fin_go = msgget(CLEF_5, IPC_CREAT | IPC_EXCL | 0600)) == -1)
		error("msgget msgid_fin_go");
	if ((msgid_out = msgget(CLEF_6, IPC_CREAT | IPC_EXCL | 0600)) == -1)
		error("msgget robot_out");
	sem_convoyeur = sem_open("/sem_convoyeur", O_RDWR);
	if (sem_convoyeur == SEM_FAILED)
	{
		if (errno != ENOENT)
			error("sem_open/init/convoyeur");
		sem_convoyeur = sem_open("/sem_convoyeur" , O_CREAT, 0666, 0);
		//le 0 correction a l initialisation du 0 (qui change avec P et V)
		if (sem_convoyeur == SEM_FAILED)
			error("sem_open/init/convoyeur");
	}
	/*
		sem_machine = sem_open("/sem_machine", O_RDWR);
		if (sem_machine == SEM_FAILED)
		{
			if (errno != ENOENT)
				error("sem_open/init/machine");
			sem_machine = sem_open("/sem_machine" , O_CREAT, 0666, nb_machine - 1);
			//le 0 correction a l initialisation du 0 (qui change avec P et V)
			if (sem_machine == SEM_FAILED)
				error("sem_open/init/machine");
		}
	*/
}
