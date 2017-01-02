#include "header.h"

void			*fonc_thread_out(void *k)
{
	(void)		*k;

	puts("Robot out allume\n");
	while (1)
	{

	}
	puts("Robot out eteint\n");
    return (NULL);
}


void			creation_robot_out(void)
{
	pthread_t	thread_id;
	long		i;

	i = 0;
	if(pthread_create(&thread_id, 0, fonc_thread_out, (void*)i) != 0)
	{
		error("Creation du robot out");
		usleep(3000);
	}
}
