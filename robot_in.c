#include "header.h"

void			*fonc_thread_in(void *k)
{
	(void)		*k;

	puts("Robot in allume\n");
	while (1)
	{

	}
	puts("Robot in eteint\n");
    return (NULL);
}


void			creation_robot_in(void)
{
	pthread_t	thread_id;
	long		i;

	i = 0;
	if(pthread_create(&thread_id, 0, fonc_thread_in, (void*)i) != 0)
	{
		error("Creation du robot in");
		usleep(3000);
	}
}
