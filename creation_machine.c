//int sem_wait (sem_t * sem ) <== P(s) --
//int sem_post (sem_t * sem ) <== V(s) ++

#include "header.h"

void				*fonc_thread(void *k)		//fonction exécutée par chaque machine
{
	s_do_thr		*info_thread;
	s_info_trs		rep;
	s_cmpt_rendu	rep_cmpt_rendu;
	int 			ratio_defaut;

	info_thread = (s_do_thr*)k;
	printf("Machine %d allumee\n", info_thread->num_thread);
	if (!nb_piece[info_thread->num_thread])
	{
		printf("Machine %d eteinte car pas de piece\n", info_thread->num_thread);
		return (NULL);//pas exit sinon extinction de toutes les machines et du processus entier
	}
	while (1)
	{
		if (msgrcv(msgid_machine, &rep, sizeof(s_info_trs) - sizeof(long), info_thread->num_thread + 10, 0) == -1)
			error("msgrcv creation_machine rep #1");
		if (rep.piece.def_work_machine)			//
			ratio_defaut = 2;
		else
			ratio_defaut = 1;
		if (sigsetjmp(contexte_sigalrm, 1) == 0)	//pas de defaillance
		{
			/* premier passage, installation */
			printf("Usinage en cours, machine[%d]\n", info_thread->num_thread);
			alarm(10000 * RATIO_TEMPS);//peut etre probleme car fonctionne avec sec...
			usleep((1000000 * 4000) * RATIO_TEMPS * ratio_defaut);
			alarm(0);
			rep_cmpt_rendu.status = OK;		//on defini les reponses a envoyer
			rep_cmpt_rendu.info_precedentes = rep;
			rep_cmpt_rendu.type = 3;
			printf("Piece [%d][%d] a fini d usiner... envoi du rapport\n", rep.num_machine, rep.num_piece);
			if (msgsnd(msgid_cmpt_rendu_mach, &rep_cmpt_rendu, sizeof(s_cmpt_rendu) - sizeof(long), 0) == -1)
				error("msgsnd msgid_cmpt_rendu_mach creation_machine.c");
			if (msgrcv(msgid_fin_go, &rep, sizeof(s_info_trs) - sizeof(long), 4, 0) == -1)
				error("msgrcv creation_machine rep msgid_fin_go");
			printf("Piece [%d][%d] va direction depot, elle est sur le convoyeur", rep.num_machine, rep.num_piece);

			if (!(rep.num_piece - 1))//nb_recu par msgrcv(); ==> plus de pieces apres celle-ci donc FIN
				break;
		}
		else					//piece defaillante
		{
			/* On est arrive par SIGALRM */
			printf("\n==== Machine %d en defaillance! ====\n", rep.num_machine);
			rep_cmpt_rendu.status = DEFAILLANCE;
			rep_cmpt_rendu.info_precedentes = rep;
			rep_cmpt_rendu.type = 3;
			if (msgsnd(msgid_cmpt_rendu_mach, &rep_cmpt_rendu, sizeof(s_cmpt_rendu) - sizeof(long), 0) == -1)
				error("msgsnd msgid_cmpt_rendu_mach creation_machine.c");
		}
	}
	printf("Machine %d eteinte\n", info_thread->num_thread);
	return (NULL);
}

void			creation_machine(void)
{
	int			rc;
	pthread_t	*thread_id;
	int			i;
	s_do_thr	*info_thread;

	thread_id = (pthread_t*)malloc(sizeof(pthread_t) * nb_machine);//ne pas oublier de free(2) à la  et signal
	if (!thread_id)
		error("malloc thread_id creat_machine");
	//msgrcv();
	for(i = 0; i < nb_machine; i++)		
	{
		info_thread = (s_do_thr*)malloc(sizeof(s_do_thr));//allouer une struct pour chaque thread et donc utilisation de pointeur car ils se suivent
		if (!info_thread)
			error("malloc info_thread creat_machine");
		info_thread->nb_machine = nb_machine;
		info_thread->num_thread = i;
		if((rc = pthread_create(&thread_id[i], 0, (void *(*)(void *))fonc_thread, (void *) info_thread)) != 0)	//creation de toutes les machines (threads)
		{
			error("Creation de machine");
			usleep(3000);
		}
	}
	free(thread_id);
	free(info_thread);
}
