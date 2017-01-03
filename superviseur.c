#include "header.h"

//sem_t *sem_open(const char *name, int oflag, ...);
//int sem_unlink(const char *name);
//int sem_post(sem_t *sem);
//int sem_wait(sem_t *sem);
//int sem_close(sem_t *sem);

//int sem_wait (sem_t * sem ) <== P(s) --
//int sem_post (sem_t * sem ) <== V(s) ++

void superviseur(s_piece **piece)
{
	int max_piece_type;
	int i;
	int j;
	s_msg_env_sup envoi;
	s_msg_rcv_sup rep;

	i = 0;
	j = 0;
	if ((msgid_machine = msgget(CLEF, IPC_CREAT | IPC_EXCL | 0600)) == -1)
		error("msgget msgid_machine");
	nb_piece_sup = (int*)malloc(sizeof(int) * nb_machine);
	if (!nb_piece_sup)
		error("malloc nb_piece_sup superviseur");

	//remplissage nb_piece_sup
	for (int count = 0; count < nb_machine; i++)
			nb_piece_sup[count] = sizeof(piece[count])/sizeof(s_piece);
	max_piece_type = trouver_max(nb_piece_sup, nb_machine);
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
	while (j <= max_piece_type)
	{
		while (i < nb_machine)
		{
			if (j < nb_piece_sup[i])
			{
				sem_post(sem_convoyeur);//attente du convoyeur libre
				if (msgsnd(msgid_in, &piece[i][j], sizeof(s_piece), 0) == -1)
					error("msgsnd msgid_in sup.c");
				sleep(1);
				//msgsnd("machine retire");
				sem_wait(sem_convoyeur);
				puts("la piece est sur le convoyeur\n");
			}
			//else nothing
			i++;
		}
		j++;
	}
}
