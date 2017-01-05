#include "header.h"

void 		fonction_sigint(int signum)
{
	(void)	signum;
	signal(SIGINT, SIG_DFL);
	if (msgctl(msgid_in, IPC_RMID, NULL) == -1)
		error("msgctl msgid_in");
	if (msgctl(msgid_out, IPC_RMID, NULL) == -1)
		error("msgctl msgid_out");
	if (msgctl(msgid_machine, IPC_RMID, NULL) == -1)
		error("msgctl msgid_machine");
	if (msgctl(msgid_cmpt_rendu_mach, IPC_RMID, NULL) == -1)
		error("msgctl msgid_cmpt_rendu_mach");
	if (msgctl(msgid_fin_go, IPC_RMID, NULL) == -1)
		error("msgctl msgid_fin_go");
	if (msgctl(msgid_rbt_inst_table, IPC_RMID, NULL) == -1)
		error("msgctl msgid_rbt_inst_table");
	if (sem_unlink("/sem_convoyeur") == -1)
		error("unlink_sem_convoyeur");
	raise(SIGINT);
}

void 		fonction_sigbus(int signum)
{
	(void)	signum;
	signal(SIGBUS, SIG_DFL);
	if (msgctl(msgid_in, IPC_RMID, NULL) == -1)
		error("msgctl msgid_in");
	if (msgctl(msgid_out, IPC_RMID, NULL) == -1)
		error("msgctl msgid_out");
	if (msgctl(msgid_machine, IPC_RMID, NULL) == -1)
		error("msgctl msgid_machine");
	if (msgctl(msgid_cmpt_rendu_mach, IPC_RMID, NULL) == -1)
		error("msgctl msgid_cmpt_rendu_mach");
	if (msgctl(msgid_fin_go, IPC_RMID, NULL) == -1)
		error("msgctl msgid_fin_go");
	if (msgctl(msgid_rbt_inst_table, IPC_RMID, NULL) == -1)
		error("msgctl msgid_rbt_inst_table");
	if (sem_unlink("/sem_convoyeur") == -1)
		error("unlink_sem_convoyeur");
	raise(SIGBUS);
}

void 		fonction_sigegv(int signum)
{
	(void)	signum;
	signal(SIGSEGV, SIG_DFL);
	if (msgctl(msgid_in, IPC_RMID, NULL) == -1)
		error("msgctl msgid_in");
	if (msgctl(msgid_out, IPC_RMID, NULL) == -1)
		error("msgctl msgid_out");
	if (msgctl(msgid_machine, IPC_RMID, NULL) == -1)
		error("msgctl msgid_machine");
	if (msgctl(msgid_cmpt_rendu_mach, IPC_RMID, NULL) == -1)
		error("msgctl msgid_cmpt_rendu_mach");
	if (msgctl(msgid_fin_go, IPC_RMID, NULL) == -1)
		error("msgctl msgid_fin_go");
	if (msgctl(msgid_rbt_inst_table, IPC_RMID, NULL) == -1)
		error("msgctl msgid_rbt_inst_table");
	if (sem_unlink("/sem_convoyeur") == -1)
		error("unlink_sem_convoyeur");
	raise(SIGSEGV);
}

int			main(void)
{
	pid_t	pid;
	s_piece **piece;

	piece = NULL;
	puts("Bienvenue");
	sleep(1);
	//modification des signaux
	signal(SIGSEGV, fonction_sigegv);
	signal(SIGINT, fonction_sigint);
	signal(SIGBUS, fonction_sigbus);
	creation_sem_msg();
	puts("Combien voulez-vous de machines? (entrer autre chose que 0)");
	nb_machine = lire_nombre_sp();
	piece = creation_piece(nb_machine, piece);//création des pièces
	creation_machine();//création des machines (threads)
	sleep(3);//attente de la creation des machines

	creation_robot_install_table();
	creation_robot_in();
	creation_robot_out();

	//ne pas oublier d ajouter le signal() dans pour suprimer les ipcs
	pid = fork();//création du processus superviseur
	switch(pid)
	{
		case -1:
			error("fork");
			break;
		case 0:
			printf("Je suis le superviseur\n");
			superviseur(piece);
			exit(0);
			break;
		default:
			printf("J'ai lancé le superviseur\n");
			wait(NULL);
			free(piece);
			free(nb_piece_sup);
			free(nb_piece);
			fonction_spr_sem_msg();
			break;
	}
	return (0);
	//free;
}
