//int sem_wait (sem_t * sem ) <== P(s) --
//int sem_post (sem_t * sem ) <== V(s) ++

#include "header.h"

void			*fonc_thread_conv(void *k)
{
	(void)		*k;

	puts("Convoyeur allume\n");
	while (1)
	{
		sem_wait(sem_convoyeur);

		sem_post(sem_convoyeur);
	}
	puts("Convoyeur eteint\n");
    return (NULL);
}


void			creation_convoyeur(void)
{
	pthread_t	thread_id;
	long		i;

	i = 0;
	if(pthread_create(&thread_id, 0, fonc_thread_conv, (void*)i) != 0)
	{
		error("Creation du convoyeur");
		usleep(3000);
	}
}
