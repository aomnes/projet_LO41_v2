#ifndef HEADER_H
#define HEADER_H

#include <signal.h>//raise, kill, signal

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#include <errno.h>

#include <sys/sem.h>//semaphores
#include <pthread.h>
#include <sys/wait.h>

#include <time.h>

#include <semaphore.h>

#include <setjmp.h>

#include <fcntl.h>

#include <sys/shm.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

sigjmp_buf	contexte_sigalrm;

sem_t 		*sem_convoyeur;
sem_t 		*sem_machine;

int 		nb_machine;
int 		somme_piece_sup;
int 		*nb_piece_sup;
int			*nb_piece;

#define CONVOYER_VERIF 0 //nb pour les semaphores
#define RATIO_TEMPS 0.02

int		defaut; /* ==>
0. non
1. defaut robot entre
2. defaut robot sortie
3. defaut retire convoyeur pour table
4. defaut duree de travail machine
*/

/* Status Compte rendu */
#define OK 1
#define DEFAILLANCE 2

typedef struct	s_piece
{
	bool		def_in;
	bool		def_out;
	bool		def_retire_conv;
	bool		def_work_machine;
}				s_piece;

typedef struct	s_info_trs
{
	long		type;
	int			num_machine;
	int			num_piece;//piece restante pour la machine en comptant celle qui est envoyé
	s_piece		piece;
}				s_info_trs;

typedef struct	s_cmpt_rendu
{
	long		type;
	int			status;//1 piece fini --> 2 machine defaillance
	s_info_trs 	info_precedentes;
}				s_cmpt_rendu;

typedef struct	s_do_thr
{
	long		type;
	int			num_thread;
	int			nb_machine;
}				s_do_thr;

int msgid_in;
int msgid_rbt_inst_table;
int msgid_machine;
int msgid_cmpt_rendu_mach;
int msgid_fin_go;
int msgid_out;

void		error(char *msg);
void		gestionnaire_sigalrm(int inutilise);
void		creation_sem_msg(void);
void		fonction_sigint(int signum);
void		fonction_sigegv(int signum);
void 		fonction_sigegv(int signum);
void		fonction_spr_sem_msg(void);

int			lire_nombre_sp(void);
int			lire_nombre_p(void);
int			lire_nombre_defaut(void);
int			lire_numero_type_def(int nb_machine);
int			lire_numero_piece(int nb_piece);
int			trouver_max(int *tab, int nb_element);

void		superviseur(s_piece **piece);
void		creation_robot_in(void);
void		creation_robot_out(void);
void		creation_robot_install_table(void);
s_piece		**creation_piece(int nb_machine, s_piece **piece);
void		creation_machine(void);
void		creation_convoyeur(void);

#endif //HEADER_H
