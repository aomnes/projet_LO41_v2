#include "header.h"

//sem_t *sem_open(const char *name, int oflag, ...);
//int sem_unlink(const char *name);
//int sem_post(sem_t *sem);
//int sem_wait(sem_t *sem);
//int sem_close(sem_t *sem);

//int sem_wait (sem_t * sem ) <== P(s) --
//int sem_post (sem_t * sem ) <== V(s) ++

void 				*superviseur(s_piece **piece)
{
	int 			i;
	int 			j;
	int 			somme;
	s_info_trs		envoi;
	s_cmpt_rendu	compte_rendu;
	s_extinction	quitter;

	i = 0;
	j = 0;
	somme = 0;

	while (i < nb_machine)
	{
		if (nb_piece[i] != 0)
		{
			sem_wait(sem_convoyeur);//attente du convoyeur libre
			envoi.num_machine = i;
			envoi.num_piece = j;
			envoi.piece = piece[i][j];
			envoi.type = 50;
			if (msgsnd(msgid_in, &envoi, sizeof(s_info_trs) - sizeof(long), 0) == -1)
				error("msgsnd msgid_in sup.c #1");
			sleep(4);
		}
		//else nothing
		somme++;
		i++;
	}//toutes les machines son remplies de pieces en premier
	while (somme <= somme_piece_sup + nb_machine - 1)
	{
		if (msgrcv(msgid_cmpt_rendu_mach, &compte_rendu, sizeof(s_cmpt_rendu) - sizeof(long), 3, 0) == -1)//recoit rapport
			error("msgrcv msgid_cmpt_rendu_mach sup.c");
		if (compte_rendu.status == DEFAILLANCE)
		{
			printf("Defaillance machine numero: %d\n", compte_rendu.info_precedentes.num_machine);
			if (nb_piece[compte_rendu.info_precedentes.num_machine] < compte_rendu.info_precedentes.num_piece)
			{
				printf("==== Systeme en état de défaillance du a la machine: %d! ====", compte_rendu.info_precedentes.num_machine);
				return (NULL);
			}
		}
		else
		{
			compte_rendu.info_precedentes.type = 4;
			if (msgsnd(msgid_fin_go, &compte_rendu.info_precedentes, sizeof(s_info_trs) - sizeof(long), 0) == -1)//ok va y
				error("msgsnd msgid_fin_go sup.c");
			compte_rendu.info_precedentes.type = 5;
			if (msgsnd(msgid_out, &compte_rendu.info_precedentes, sizeof(s_info_trs) - sizeof(long), 0) == -1)//ok va y
				error("msgsnd msgid_out sup.c");
			sem_wait(sem_convoyeur);//attente du convoyeur libre puis la prend
			envoi.num_machine = compte_rendu.info_precedentes.num_machine;
			envoi.num_piece = compte_rendu.info_precedentes.num_piece + 1;
			envoi.piece = piece[compte_rendu.info_precedentes.num_machine][compte_rendu.info_precedentes.num_piece + 1];
			envoi.type = 50;
			if (somme == somme_piece_sup)
				envoi.extinction = true;
			if (msgsnd(msgid_in, &envoi, sizeof(s_info_trs) - sizeof(long), 0) == -1)
				error("msgsnd msgid_in sup.c #2");
			somme++;
			//lui envoi une piece
		}
	}
	puts("Superviseur attend l arrêt du Robot_out\n");
	if (msgrcv(msgid_out_fin, &quitter, sizeof(s_info_trs) - sizeof(long), 100, 0) == -1)
		error("msgsnd msgid_out_fin robot_out.c");
	return (NULL);
}
