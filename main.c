#include "header.h"

void 		fonction_sigint(int signum)
{
	(void)	signum;
	signal(SIGINT, SIG_DFL);
	fonction_spr_sem_msg();
	raise(SIGINT);
}

void 		fonction_sigbus(int signum)
{
	(void)	signum;
	signal(SIGBUS, SIG_DFL);
	fonction_spr_sem_msg();
	raise(SIGBUS);
}

void 		fonction_sigegv(int signum)
{
	(void)	signum;
	signal(SIGSEGV, SIG_DFL);
	fonction_spr_sem_msg();
	raise(SIGSEGV);
}

void 		fonction_sigkill(int signum)
{
	(void)	signum;
	fonction_spr_sem_msg();
	signal(SIGKILL, SIG_DFL);
	raise(SIGKILL);
}

void 		fonction_sigill(int signum)
{
	(void)	signum;
	signal(SIGILL, SIG_DFL);
	fonction_spr_sem_msg();
	raise(SIGILL);
}

int			main(void)
{
	s_piece **piece;

	piece = NULL;
	puts("Bienvenue");
	//modification des signaux
	signal(SIGSEGV, fonction_sigegv);
	signal(SIGINT, fonction_sigint);
	signal(SIGBUS, fonction_sigbus);
	signal(SIGKILL, fonction_sigkill);
	signal(SIGILL, fonction_sigill);
	creation_sem_msg();
	puts("Combien voulez-vous de machines? (entrer autre chose que 0)");
	nb_machine = lire_nombre_sp();
	piece = creation_piece(nb_machine, piece);//création des pièces
	creation_machine();//création des machines (threads)
	sleep(3);//attente de la creation des machines

	creation_robot_install_table();
	creation_robot_in();
	creation_robot_out();
	superviseur(piece);//lancement du superviseur
	free(piece);
	free(nb_piece_sup);
	free(nb_piece);
	fonction_spr_sem_msg();//suprimer le/les sem files de message
	printf("Extinction totale...\n");
	return (0);
}
