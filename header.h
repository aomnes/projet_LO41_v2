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

#include <sys/types.h>

#include <time.h>

#include <semaphore.h>

#include <setjmp.h>

#include <fcntl.h>

#include <sys/shm.h>

key_t		CLEF;

sigjmp_buf	contexte_sigalrm;

sem_t *sem_convoyeur;
sem_t *sem_machine;

int nb_machine;

#define CONVOYER_VERIF 0 //nb pour les semaphores
#define MACHINE_VERIF 1
#define RATIO_TEMPS 0.02

int		defaut; /* ==>
0. non
1. defaut robot entre
2. defaut robot sortie
3. defaut retire convoyeur pour table
4. defaut duree de travail machine
*/

int     lire_nombre_sp(void);
int     lire_nombre_p(void);
int     lire_nombre_defaut(void);
int     lire_numero_type_def(int nb_machine);
int     lire_numero_piece(int nb_piece);

typedef struct	s_piece
{
	bool		def_in;
	bool		def_out;
	bool		def_retire_conv;
	bool		def_work_machine;
}				s_piece;

typedef struct	s_msg_env_sup
{
	int			num_machine;
	int			nb_piece_type;	//piece du type de la machine en comptant celle qui est envoyé
	s_piece		piece;
}				s_msg_env_sup;

typedef struct	s_msg_rcv_sup
{
	int		status;//1 piece fini --> 2 machine defaillance
	int		num_machine;

}				s_msg_rcv_sup;

typedef struct	s_do_thr
{
	int			num_thread;
	int			nb_machine;
}				s_do_thr;

void		error(char *msg);

void		superviseur(int nb_piece, s_piece **piece);
s_piece		**creation_piece(int nb_machine, s_piece **piece);
void		creation_machine(void);
void		creation_convoyeur(void);

#endif //HEADER_H
