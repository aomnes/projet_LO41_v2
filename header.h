#ifndef HEADER_H
#define HEADER_H

#include <signal.h>//raise, kill, signal

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

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

void* ptr_mem_partagee;
int mem_ID;

#define CONVOYER_VERIF 0 //nb pour les semaphores
#define MACHINE_VERIF 1
#define RATIO_TEMPS 0.02

int     lire_nombre_sp(void);
int     lire_nombre_p(void);
int     lire_nombre_defaut(void);

typedef struct	s_piece
{
	int			id;
	int			usinage;
	int			def_in;
	int			def_ou;
	int			def_retire_tapis;
	int			def_work_machine;
}				s_piece;

typedef struct	s_do_thr
{
	int			num_thread;
	int			nb_machine;
}				s_do_thr;

void		error(char *msg);

void		superviseur(int nb_piece, s_piece piece);
s_piece		*creation_piece(int nb_machine);
void		creation_machine(void);
void		creation_convoyeur(void);

#endif //HEADER_H
