//int sem_wait (sem_t * sem ) <== P(s) --
//int sem_post (sem_t * sem ) <== V(s) ++

#include "header.h"

void				*fonc_thread(void *k)
{
	s_do_thr		*info_thread;
	s_msg_env_sup	rep;
	int				valeur_out_msgrcv;

	info_thread = (s_do_thr*)k;
	printf("Machine %d allumee\n", info_thread->num_thread);

	do
	{
		if (msgrcv(msgid_machine, &rep, sizeof(s_msg_env_sup), 0, 0) == -1)
			error("msgrcv creation_machine rep #1");
	} while (info_thread->num_thread != rep.num_machine);
	//ne pas oublier eteindre la si la machine n a pas de pieces (!nb_piece_type)
	do
	{
		errno = 0;
		valeur_out_msgrcv = msgrcv(msgid_machine, &rep, sizeof(s_msg_env_sup), 0, IPC_NOWAIT);
		 if (errno != ENOMSG && valeur_out_msgrcv != 0)
			error("msgrcv creation_machine vide file message #1");
	} while (errno != ENOMSG);//vider file de message

	while (1)
	{
		if (!rep.nb_piece_type)//nb_recu par msgrcv(); pb ==> si pas de piece alors on allume pas la machine donc pas de message a envoyer utilisation varaible globale
			break;
		do
		{
			if (msgrcv(msgid_machine, &rep, sizeof(s_msg_env_sup), 0, 0) == -1)
				error("msgrcv creation_machine rep #2");
		} while (info_thread->num_thread != rep.num_machine);
		do
		{
			errno = 0;
			valeur_out_msgrcv = msgrcv(msgid_machine, &rep, sizeof(s_msg_env_sup), 0, IPC_NOWAIT);
			 if (errno != ENOMSG && valeur_out_msgrcv != 0)
				error("msgrcv creation_machine vide file message #2");
		} while (errno != ENOMSG);//vider file de message

		alarm(1);
		//msgsnd(...) compte rendu
		if (msgsnd(msgid_in, &rep.piece, sizeof(s_piece), 0) == -1)
			error("msgsnd msgid_out");
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
