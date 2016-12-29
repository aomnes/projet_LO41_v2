//int sem_wait (sem_t * sem ) <== P(s) --
//int sem_post (sem_t * sem ) <== V(s) ++

#include "header.h"

void			*fonc_thread(void *k)
{
	s_do_thr	*info_thread;

	if((ptr_mem_partagee = shmat(mem_ID,NULL, 0)) == (void *) -1)
		error("shmat");

	info_thread = (s_do_thr*)k;
	printf("Machine %d allumee\n", info_thread->num_thread);
	while (1)
	{
		sem_wait(sem_machine);

		sem_post(sem_machine);
		sem_post(sem_convoyeur);
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

	CLEF = ftok("/cle_shm", 'A');

	puts("Combien voulez-vous de machines? (entrer autre chose que 0)");

	nb_machine = lire_nombre_sp();

	thread_id = (pthread_t*)malloc(sizeof(pthread_t) * nb_machine);//ne pas oublier de free(2) à la  et signal
	if (!thread_id)
		error("malloc thread_id creat_machine");

	mem_ID = shmget(CLEF, sizeof(int) * nb_machine, 0666 | IPC_CREAT);
	if(mem_ID < 0)
		error("shmget");

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
