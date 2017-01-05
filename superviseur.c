#include "header.h"

//sem_t *sem_open(const char *name, int oflag, ...);
//int sem_unlink(const char *name);
//int sem_post(sem_t *sem);
//int sem_wait(sem_t *sem);
//int sem_close(sem_t *sem);

//int sem_wait (sem_t * sem ) <== P(s) --
//int sem_post (sem_t * sem ) <== V(s) ++

void 				superviseur(s_piece **piece)
{
	int 			i;
	int 			j;
	int 			somme;
	s_info_trs		envoi;
	s_cmpt_rendu	compte_rendu;

	i = 0;
	j = 0;
	somme = 0;
	nb_piece_sup = (int*)malloc(sizeof(int) * nb_machine);
	if (!nb_piece_sup)
		error("malloc nb_piece_sup superviseur");

	//remplissage nb_piece_sup
	for (int count = 0; count < nb_machine; i++)
			nb_piece_sup[count] = sizeof(piece[count])/sizeof(s_piece);

	while (i < nb_machine)
	{
		if (nb_piece_sup[i] != 0)
		{
			sem_post(sem_convoyeur);//attente du convoyeur libre
			envoi.num_machine = i;
			envoi.num_piece = j;
			envoi.piece = piece[i][j];
			if (msgsnd(msgid_in, &envoi, sizeof(s_info_trs), 0) == -1)
				error("msgsnd msgid_in sup.c");
			sleep(1);
		}
		//else nothing
		somme++;
		i++;
	}//toutes les machines son remplies de pieces en premier

	while (somme != somme_piece_sup)
	{
		if (msgrcv(msgid_cmpt_rendu_mach, &compte_rendu, sizeof(s_cmpt_rendu), 0, 0) == -1)//recoit rapport
			error("msgrcv msgid_cmpt_rendu_mach sup.c");
		if (compte_rendu.status == DEFAILLANCE)
		{
			printf("Defaillance machine numero: %d\n", compte_rendu.info_precedentes.num_machine);
		}
		else
		{
			if (msgsnd(msgid_fin_go, &compte_rendu.info_precedentes, sizeof(s_info_trs), 0) == -1)//ok va y
				error("msgsnd msgid_fin_go sup.c");
			if (msgsnd(msgid_out, &compte_rendu.info_precedentes, sizeof(s_info_trs), 0) == -1)//ok va y
				error("msgsnd msgid_out sup.c");
		sem_post(sem_convoyeur);//attente du convoyeur libre
		envoi.num_machine = compte_rendu.info_precedentes.num_machine;
		envoi.num_piece = compte_rendu.info_precedentes.num_piece + 1;
		envoi.piece = piece[compte_rendu.info_precedentes.num_machine][compte_rendu.info_precedentes.num_piece + 1];
		if (msgsnd(msgid_in, &envoi, sizeof(s_info_trs), 0) == -1)
			error("msgsnd msgid_in sup.c");
		somme++;
		//lui envoi une piece
		}
	}
}
