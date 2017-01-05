#include "header.h"

void gestionnaire_sigalrm(int inutilise)
{
	(void) inutilise;

	siglongjmp(contexte_sigalrm, 1);//echec du saut
}

void			*fonc_thread_in(void *k)
{
	(void)		k;
    s_info_trs	message;
    int			ratio_defaut;

	puts("Robot in allume");
	while (1)
	{
		//ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg);
		if (msgrcv(msgid_in, &message, sizeof(s_info_trs) - sizeof(long), 50, 0) == -1)
			error("msgrcv msgid_in");
		if (message.piece.def_in)
			ratio_defaut = 2;
		else
			ratio_defaut = 1;
		if (sigsetjmp(contexte_sigalrm, 1) == 0)
		{
			/* premier passage, installation */
			alarm(20 * RATIO_TEMPS);//peut etre probleme car fonctionne avec sec...
			usleep((1000000 * 20 - 10000) * RATIO_TEMPS * ratio_defaut);
			alarm(0);
			puts("Ok ! Piece sur le convoyeur (Robot_in)\n");
			sleep(1);
			message.type = 1;
			if (msgsnd(msgid_rbt_inst_table, &message, sizeof(s_info_trs) - sizeof(long), 0) == -1)
				error("msgsnd msgid_in -> msgid_rbt_inst_table");
			sem_wait(sem_convoyeur);//piece est sur le convoyeur
		}
		else
		{
			/* On est arrive par SIGALRM */
			puts("\n==== Systeme en état de défaillance Robot_in! ====\n");
			exit(EXIT_FAILURE);
		}
	}
	puts("Robot in eteint\n");
	return (NULL);
}


void			creation_robot_in(void)
{
	pthread_t	thread_id;
	long		i;

	i = 0;
	if (pthread_create(&thread_id, 0, fonc_thread_in, (void*)i) != 0)
	{
		error("Creation du robot in");
		usleep(3000);
	}
}
