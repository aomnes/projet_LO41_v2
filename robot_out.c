#include "header.h"

void			*fonc_thread_out(void *k)
{
	(void)			k;
	s_info_trs		message;
	int				ratio_defaut;

	puts("Robot out allume\n");
	while (1)
	{
		//ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg);
		if (msgrcv(msgid_out, &message, sizeof(s_info_trs) - sizeof(long), 5, 0) == -1)
			error("msgrcv msgid_out");
		if (message.piece.def_out)
			ratio_defaut = 2;
		else
			ratio_defaut = 1;
		sem_post(sem_convoyeur);//capteur allume, piece n est plus sur le convoyeur
		if (sigsetjmp(contexte_sigalrm, 1) == 0)
		{
			/* premier passage, installation */
			alarm(20 * RATIO_TEMPS);//peut etre probleme car fonctionne avec sec...
			usleep((1000000 * 20 - 10000) * RATIO_TEMPS * ratio_defaut);
			alarm(0);
			puts("Ok ! Piece sur dans le depot\n");
		}
		else
		{
			/* On est arrive par SIGALRM */
			puts("\n==== Systeme en état de défaillance Robot_out! ====\n");
			sleep(10);
			fonction_spr_sem_msg();
			exit(EXIT_FAILURE);
		}
	}
	puts("Robot out eteint\n");
	return (NULL);
}


void			creation_robot_out(void)
{
	pthread_t	thread_id;
	long		i;

	i = 0;
	if (pthread_create(&thread_id, 0, fonc_thread_out, (void*)i) != 0)
	{
		error("Creation du robot out");
		usleep(3000);
	}
}
