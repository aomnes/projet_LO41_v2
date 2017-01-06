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

	i = 0;
	j = 0;
	somme = 0;
	nb_piece_sup = (int*)malloc(sizeof(int) * nb_machine);
	if (!nb_piece_sup)
		error("malloc nb_piece_sup superviseur");
	//remplissage nb_piece_sup
	for (int count = 0; count < nb_machine; count++)
			nb_piece_sup[count] = sizeof(piece[count])/sizeof(s_piece);
	while (i < nb_machine)
	{
		if (nb_piece_sup[i] != 0)
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
	while (somme != somme_piece_sup)
	{
		printf("...\n");
		if (msgrcv(msgid_cmpt_rendu_mach, &compte_rendu, sizeof(s_cmpt_rendu) - sizeof(long), 3, 0) == -1)//recoit rapport
			error("msgrcv msgid_cmpt_rendu_mach sup.c");
		printf("...OK\n");
		if (compte_rendu.status == DEFAILLANCE)
		{
			printf("Defaillance machine numero: %d\n", compte_rendu.info_precedentes.num_machine);
			if (nb_piece_sup[compte_rendu.info_precedentes.num_machine] < compte_rendu.info_precedentes.num_piece)
			{
				printf("==== Systeme en état de défaillance du a la machine: %d! ====", compte_rendu.info_precedentes.num_machine);
				puts("10s...");
				sleep(10);
				fonction_spr_sem_msg();
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			printf("msgid_fin_go send #1\n");
			compte_rendu.info_precedentes.type = 4;
			if (msgsnd(msgid_fin_go, &compte_rendu.info_precedentes, sizeof(s_info_trs) - sizeof(long), 0) == -1)//ok va y
				error("msgsnd msgid_fin_go sup.c");
			printf("msgid_fin_go send #2\n");
			compte_rendu.info_precedentes.type = 5;
			if (msgsnd(msgid_out, &compte_rendu.info_precedentes, sizeof(s_info_trs) - sizeof(long), 0) == -1)//ok va y
				error("msgsnd msgid_out sup.c");
			//printf("msgid_out send #\n");
			sem_wait(sem_convoyeur);//attente du convoyeur libre puis la prend
			envoi.num_machine = compte_rendu.info_precedentes.num_machine;
			envoi.num_piece = compte_rendu.info_precedentes.num_piece + 1;
			envoi.piece = piece[compte_rendu.info_precedentes.num_machine][compte_rendu.info_precedentes.num_piece + 1];
			envoi.type = 50;
			if (msgsnd(msgid_in, &envoi, sizeof(s_info_trs) - sizeof(long), 0) == -1)
				error("msgsnd msgid_in sup.c #2");
			//printf("msgid_in send ########\n");
			somme++;
			//lui envoi une piece
		}
	}
	return (NULL);
}
