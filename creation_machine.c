//int sem_wait (sem_t * sem ) <== P(s) --
//int sem_post (sem_t * sem ) <== V(s) ++

#include "header.h"

void			*fonc_thread(void *k)
{
	s_do_thr	*info_thread;
	int			nb_piece;

	info_thread = (s_do_thr*)k;
	printf("Machine %d allumee\n", info_thread->num_thread);

	//do
	// rep = msgrcv(...)
	//while(rep != num_mach)

	while (1)
	{
		if (!nb_piece)//nb_recu par msgrcv();
			break;
		//do
		// rep = msgrcv(...) ordre
		// num_mach = struct.num;
		//while(rep != num_mach)
		//alarm(10min);
		//msgsnd(...) compte rendu
		//msgrcv("env conv" robot_out);
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
