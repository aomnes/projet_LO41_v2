#include "header.h"

void			fonction_spr_sem_msg(void)
{
	if (msgctl(msgid_in, IPC_RMID, NULL) == -1)
		error("msgctl msgid_in");
	if (msgctl(msgid_out, IPC_RMID, NULL) == -1)
		error("msgctl msgid_out");
	if (msgctl(msgid_machine, IPC_RMID, NULL) == -1)
		error("msgctl msgid_machine");
	if (msgctl(msgid_cmpt_rendu_mach, IPC_RMID, NULL) == -1)
		error("msgctl msgid_cmpt_rendu_mach");
	if (msgctl(msgid_fin_go, IPC_RMID, NULL) == -1)
		error("msgctl msgid_fin_go");
	if (msgctl(msgid_rbt_inst_table, IPC_RMID, NULL) == -1)
		error("msgctl msgid_rbt_inst_table");
	if (sem_unlink("/sem_convoyeur") == -1)
		error("unlink_sem_convoyeur");
}

void			error(char *msg)
{
	perror(msg);
	fonction_spr_sem_msg();
	exit(0);
}

int				lire_nombre_sp(void)
{
	int 		d;
	int 		c;

	do
	{
		scanf("%d", &d);
		while ((c = getchar ()) != '\n' && c != EOF);
	} while (d <= 0);
	return (d);
}

int				lire_nombre_p(void)
{
	int			d;
	int			c;

	do
	{
		scanf("%d", &d);
		while ((c = getchar ()) != '\n' && c != EOF);
	} while (d < 0);
	return (d);
}

int				lire_nombre_defaut(void)
{
	int			d;
	int			c;

	do
	{
		scanf("%d", &d);
		while ((c = getchar ()) != '\n' && c != EOF);
	} while (d < 0 || d > 4);
	return (d);
}

int				lire_numero_type_def(int nb_machine)
{
	int			d;
	int			c;

	do
	{
		scanf("%d", &d);
		while ((c = getchar ()) != '\n' && c != EOF);
	} while (d < 0 || d > nb_machine - 1);
	return (d);
}

int				lire_numero_piece(int nb_piece)
{
	int			d;
	int			c;

	do
	{
		scanf("%d", &d);
		while ((c = getchar ()) != '\n' && c != EOF);
	} while (d < 0 || d > nb_piece - 1);
	return (d);
}

int				trouver_max(int *tab, int nb_element)
{
	int			max;
	int			index;

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

void			creation_sem_msg(void)
{
	key_t		CLEF_1;
	key_t		CLEF_2;
	key_t		CLEF_3;
	key_t		CLEF_4;
	key_t		CLEF_5;
	key_t		CLEF_6;
	char		*chaine;
	int			len_PWD;
	int			len_fichier;

	len_PWD = strlen(getenv("PWD"));
	len_fichier = strlen("/robot_in.c");
	chaine = (char*)malloc(sizeof(char) * (len_PWD + len_fichier + 1));
	if (!chaine)
		error("malloc chaine 1 PWD");
	chaine[len_PWD + len_fichier] = '\0';
	sprintf(chaine , "%s/robot_in.c", getenv("PWD"));
	CLEF_1 = ftok(chaine, 'A');
	if (CLEF_1 == -1)
		error("ftok CLEF_1");
	free(chaine);

	len_fichier = strlen("/robot_install_table.c");
	chaine = (char*)malloc(sizeof(char) * (len_PWD + len_fichier + 1));
	if (!chaine)
		error("malloc chaine 2 PWD");
	chaine[len_PWD + len_fichier] = '\0';
	sprintf(chaine , "%s/robot_install_table.c", getenv("PWD"));
	CLEF_2 = ftok(chaine, 'B');
	if (CLEF_1 == -1)
		error("ftok CLEF_2");
	free(chaine);

	len_fichier = strlen("/creation_machine.c");
	chaine = (char*)malloc(sizeof(char) * (len_PWD + len_fichier + 1));
	if (!chaine)
		error("malloc chaine 3 PWD");
	chaine[len_PWD + len_fichier] = '\0';
	sprintf(chaine , "%s/creation_machine.c", getenv("PWD"));
	CLEF_3 = ftok(chaine, 'C');
	if (CLEF_1 == -1)
		error("ftok CLEF_3");
	free(chaine);

	len_fichier = strlen("/superviseur.c");
	chaine = (char*)malloc(sizeof(char) * (len_PWD + len_fichier + 1));
	if (!chaine)
		error("malloc chaine 4 PWD");
	chaine[len_PWD + len_fichier] = '\0';
	sprintf(chaine , "%s/superviseur.c", getenv("PWD"));
	CLEF_4 = ftok(chaine, 'D');
	if (CLEF_1 == -1)
		error("ftok CLEF_4");
	free (chaine);

	len_fichier = strlen("/useful_function.c");
	chaine = (char*)malloc(sizeof(char) * (len_PWD + len_fichier + 1));
	if (!chaine)
		error("malloc chaine 5 PWD");
	chaine[len_PWD + len_fichier] = '\0';
	sprintf(chaine , "%s/useful_function.c", getenv("PWD"));
	CLEF_5 = ftok(chaine, 'E');
	if (CLEF_1 == -1)
		error("ftok CLEF_5");
	free (chaine);

	len_fichier = strlen("/robot_out.c");
	chaine = (char*)malloc(sizeof(char) * (len_PWD + len_fichier + 1));
	if (!chaine)
		error("malloc chaine 6 PWD");
	chaine[len_PWD + len_fichier] = '\0';
	sprintf(chaine , "%s/robot_out.c", getenv("PWD"));
	CLEF_6 = ftok(chaine, 'F');
	if (CLEF_1 == -1)
		error("ftok CLEF_6");
	free (chaine);

	msgid_in = msgget(CLEF_1, IPC_CREAT | IPC_EXCL | 0660);
	if (msgid_in == -1)
		error("msgget Robot_in");
	msgid_rbt_inst_table = msgget(CLEF_2, IPC_CREAT | IPC_EXCL | 0660);
	if (msgid_rbt_inst_table == -1)
		error("msgget msgid_rbt_inst_table");
	if ((msgid_machine = msgget(CLEF_3, IPC_CREAT | IPC_EXCL | 0660)) == -1)
		error("msgget msgid_machine");
	if ((msgid_cmpt_rendu_mach = msgget(CLEF_4, IPC_CREAT | IPC_EXCL | 0660)) == -1)
		error("msgget msgid_cmpt_rendu_mach");
	if ((msgid_fin_go = msgget(CLEF_5, IPC_CREAT | IPC_EXCL | 0660)) == -1)
		error("msgget msgid_fin_go");
	if ((msgid_out = msgget(CLEF_6, IPC_CREAT | IPC_EXCL | 0660)) == -1)
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
