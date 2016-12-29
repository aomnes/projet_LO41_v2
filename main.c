#include "header.h"

int			main(void)
{
	pid_t	pid;
	s_piece **piece;

	puts("Bienvenue");
	sleep(1);
	//modification des signaux
	creation_machine();//création des machines (threads)
	piece = (s_piece**)malloc(sizeof(piece) * nb_machine);		//ajouter le free(2) dans le signal
	if (!piece)
		error("malloc creation tableau piece");
	piece = creation_piece(nb_machine, piece);//création des pièces
	creation_convoyeur();//création du creation_convoyeur()

	pid = fork();//création du processus superviseur
	switch(pid)
	{
		case -1:
			error("fork");
			break;
		case 0:
			printf("Je suis le superviseur\n");
			exit(0);
			break;
		default:
			printf("J'ai lancé le superviseur\n");
			wait(NULL);
			if (shmctl(mem_ID, IPC_RMID, 0) == -1)
				error("shmctl /cle_shm");
			/*if (sem_unlink("/sem_convoyeur") == -1)
				error("unlink_sem_convoyeur");//
			if (sem_unlink("/sem_machine") == -1)
				error("unlink_sem_machine");

			* intile pour le moment car superviseur(); non installe dans le case 0...
			*/
			break;
	}
	return (0);
	//free;
}
