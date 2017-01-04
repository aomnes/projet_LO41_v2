//int sem_wait (sem_t * sem ) <== P(s) --
//int sem_post (sem_t * sem ) <== V(s) ++

#include "header.h"

void				*fonc_thread(void *k)
{
	s_do_thr		*info_thread;
	s_info_trs  	rep;
	s_cmpt_rendu	rep_cmpt_rendu;
	int 			ratio_defaut;
	int				valeur_out_msgrcv;

	info_thread = (s_do_thr*)k;
	printf("Machine %d allumee\n", info_thread->num_thread);
	//attendre la creation des pieces;
	if (!nb_piece_sup[info_thread->num_thread])
	{
		puts("Machine %d eteinte car pas de piece");
		return (NULL);//pas exit sinon extinction de toutes les machines et du processus entier
	}
	while (1)
	{
		do
		{
			if (msgrcv(msgid_machine, &rep, sizeof(s_info_trs), 0, 0) == -1)
				error("msgrcv creation_machine rep #1");
		} while (info_thread->num_thread != rep.num_machine);//si machine bonne (car plusieurs thread)
		do
		{
			errno = 0;
			valeur_out_msgrcv = msgrcv(msgid_machine, &rep, sizeof(s_info_trs), 0, IPC_NOWAIT);
			 if (errno != ENOMSG && valeur_out_msgrcv != 0)
				error("msgrcv creation_machine vide file message #2");
		} while (errno != ENOMSG);//vider file de message
		if (rep.piece.def_work_machine)
            ratio_defaut = 2;
        else
            ratio_defaut = 1;
		if (sigsetjmp(contexte_sigalrm, 1) == 0)
		{
			/* premier passage, installation */
			alarm(50 * RATIO_TEMPS);//peut etre probleme car fonctionne avec sec...
			usleep((1000000 * 50 - 10000) * RATIO_TEMPS * ratio_defaut);
			alarm(0);
			rep_cmpt_rendu.status = OK;
			rep_cmpt_rendu.info_precedentes = rep;
			if (msgsnd(msgid_cmpt_rendu_mach, &rep_cmpt_rendu, sizeof(s_cmpt_rendu), 0) == -1)
				error("msgsnd msgid_cmpt_rendu_mach creation_machine.c");
			if (msgrcv(msgid_fin_go, &rep, sizeof(s_info_trs), 0, 0) == -1)
				error("msgrcv creation_machine rep msgid_fin_go");
			puts("Piece fini d usiner est sur le convoyeur");
			if (!(rep.num_piece - 1))//nb_recu par msgrcv(); ==> plus de pieces apres celle-ci donc FIN
				break;
		}
		else
		{
			/* On est arrive par SIGALRM */
			printf("\n==== Machine %d en defaillance! ====\n", rep.num_machine);
			rep_cmpt_rendu.status = DEFAILLANCE;
			rep_cmpt_rendu.info_precedentes = rep;
			if (msgsnd(msgid_cmpt_rendu_mach, &rep_cmpt_rendu, sizeof(s_cmpt_rendu), 0) == -1)
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

	puts("Combien voulez-vous de machines? (entrer autre chose que 0)");

	nb_machine = lire_nombre_sp();

	thread_id = (pthread_t*)malloc(sizeof(pthread_t) * nb_machine);//ne pas oublier de free(2) à la  et signal
	if (!thread_id)
		error("malloc thread_id creat_machine");

	for(i = 0; i < nb_machine; i++)
	{
		info_thread = (s_do_thr*)malloc(sizeof(s_do_thr));//allouer une struct pour chaque thread et donc utilisation de pointeur car ils se suivent
		if (!info_thread)
			error("malloc info_thread creat_machine");
		info_thread->nb_machine = nb_machine;
		info_thread->num_thread = i;
		if((rc = pthread_create(&thread_id[i], 0, fonc_thread, (void *) info_thread)) != 0)
		{
			error("Creation de machine");
			usleep(3000);
		}
	}
	free(info_thread);
}
