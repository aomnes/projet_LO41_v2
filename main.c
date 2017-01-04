#include "header.h"

int			main(void)
{
	pid_t	pid;
	s_piece **piece;

	piece = NULL;
	CLEF = ftok("/cle_shm", 'A');
	puts("Bienvenue");
	sleep(1);
	//modification des signaux
	puts("Combien voulez-vous de machines? (entrer autre chose que 0)");
	nb_machine = lire_nombre_sp();
	piece = creation_piece(nb_machine, piece);//création des pièces
	creation_machine();//création des machines (threads)
	sleep(3);//attente de la creation des machines

	creation_robot_install_table();
	creation_robot_in();
	creation_robot_out();

	creation_convoyeur();//création du creation_convoyeur()
	//ne pas oublier d ajouter le signal() dans pour suprimer les ipcs
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
