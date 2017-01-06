#include "header.h"

void				*fonc_thread_rbt_install(void *k)
{
	(void)				k;
	struct sigaction	action;
	s_info_trs			message;
	int					ratio_defaut;

	action.sa_handler = gestionnaire_sigalrm;
	action.sa_flags = 0;
	sigfillset(& action.sa_mask);
	sigaction(SIGALRM, & action, NULL);
	puts("\nRobot installe table allume");
	while (1)
	{
		//ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg);
		if (msgrcv(msgid_rbt_inst_table, &message, sizeof(s_info_trs) - sizeof(long), 1, 0) == -1)
			error("msgrcv msgid_rbt_inst_table");
		if (message.piece.def_retire_conv)		//si la piece est defectueuse, les temps de manipulation seront multipliés par deux
			ratio_defaut = 100;
		else
			ratio_defaut = 1;
		if (sigsetjmp(contexte_sigalrm, 1) == 0)
		{
			/* premier passage, installation */
			alarm(10 * RATIO_TEMPS);//peut etre probleme car fonctionne avec sec...
			usleep(1000000 * 8 * RATIO_TEMPS * ratio_defaut);
			alarm(0);
			/* Pas de changement des donnees dans le message sauf le type */
			message.type = message.num_machine + 10;
			if (msgsnd(msgid_machine, &message, sizeof(s_info_trs) - sizeof(long), 0) == -1)
				error("msgsnd msgid_machine");
			printf("Ok ! Piece machine:[%d] piece:[%d]sur la table\n", message.num_machine, message.num_piece);
			sem_post(sem_convoyeur);//++
		}
		else
		{
			/* On est arrive par SIGALRM */
			puts("\n==== Systeme en état de défaillance Robot_intall_table! ====\n");
			puts("...");	//la piece est defectueuse
			sleep(3);
			fonction_spr_sem_msg();
			exit(EXIT_FAILURE);
		}
	}
	puts("Robot installe table eteint\n");
	return (NULL);
}


void			creation_robot_install_table(void)
{
	pthread_t	thread_id;
	long		i;

	i = 0;
	if (pthread_create(&thread_id, 0, fonc_thread_rbt_install, (void*)i) != 0)	//creation du thread du robot
	{
		error("Creation Robot installe table");
		usleep(3000);
	}
}
