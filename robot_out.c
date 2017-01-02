#include "header.h"

void			*fonc_thread_out(void *k)
{
	(void)		*k;
    struct sigaction action;

    action.sa_handler = gestionnaire_sigalrm;
    action.sa_flags = 0;
    sigfillset(& action.sa_mask);
    sigaction(SIGALRM, & action, NULL);

	puts("Robot out allume\n");
	while (1)
	{
        //msgrcv(...)
        if (sigsetjmp(contexte_sigalrm, 1) == 0)
        {
            /* premier passage, installation */
            alarm(20 * RATIO_TEMPS);//peut etre probleme car fonctionne avec sec...
            usleep((1000000 * 20 - 10000) * RATIO_TEMPS * piece.def_in);
            alarm(0);
            puts()"Ok ! Piece sur le convoyeur\n");
        }
        else
        {
            /* On est arrive par SIGALRM */
            puts("\n==== Systeme en état de défaillance! ====\n");
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
