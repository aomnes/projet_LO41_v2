#include "header.h"

//sem_t *sem_open(const char *name, int oflag, ...);
//int sem_unlink(const char *name);
//int sem_post(sem_t *sem);
//int sem_wait(sem_t *sem);
//int sem_close(sem_t *sem);

//int sem_wait (sem_t * sem ) <== P(s) --
//int sem_post (sem_t * sem ) <== V(s) ++

void gestionnaire_sigalrm (int inutilise)
{
	(void) inutilise;

	siglongjmp(contexte_sigalrm, 1);//echec du saut
}

void superviseur(int nb_piece, s_piece **piece)
{
	struct sigaction action;

	action.sa_handler = gestionnaire_sigalrm;
	action.sa_flags = 0;
	sigfillset(& action.sa_mask);
	sigaction(SIGALRM, & action, NULL);

	if((ptr_mem_partagee = shmat(mem_ID,NULL, 0)) == (void*) -1)
		error("shmat");

	sem_convoyeur = sem_open("/sem_convoyeur", O_RDWR);
	if (sem_convoyeur == SEM_FAILED)
	{
		if (errno != ENOENT)
			error("sem_open/init/convoyeur");
		sem_convoyeur = sem_open("/sem_convoyeur" , O_CREAT, 0666, 0);//le 0 correction a l initialisation du 0 (qui change avec P et V)
		if (sem_convoyeur == SEM_FAILED)
			error("sem_open/init/convoyeur");
	}

	sem_machine = sem_open("/sem_machine", O_RDWR);
	if (sem_machine == SEM_FAILED)
	{
		if (errno != ENOENT)
			error("sem_open/init/machine");
		sem_machine = sem_open("/sem_machine" , O_CREAT, 0666, nb_machine - 1);//le 0 correction a l initialisation du 0 (qui change avec P et V)
		if (sem_machine == SEM_FAILED)
			error("sem_open/init/machine");
	}

	while (nb_piece)
	{
		if (sigsetjmp(contexte_sigalrm, 1) == 0)
		{
			/* premier passage, installation */
			alarm(20 * RATIO_TEMPS);//peut etre probleme car fonctionne avec sec...
//			usleep((1000000 * 20 - 10000) * RATIO_TEMPS * piece[][].defaut);
			alarm(0);
			fprintf(stdout, "Ok ! Piece sur le convoyeur\n");
		}
		else
		{
			/* On est arrive par SIGALRM */
			fprintf(stdout, "\n==== Systeme en état de défaillance! ====\n");
			exit(EXIT_FAILURE);
		}
		sem_wait(sem_convoyeur);//peut etre a placer avant le usleep();
		sem_wait(sem_machine);
		printf("la piece %d est sur le convoyeur\n", nb_piece);

	}
}