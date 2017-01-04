#include "header.h"

void                    *fonc_thread_rbt_install(void *k)
{
	(void)              *k;
    struct sigaction    action;
    s_msg_env_sup       message;
    int                 ratio_defaut;

    action.sa_handler = gestionnaire_sigalrm;
    action.sa_flags = 0;
    sigfillset(& action.sa_mask);
    sigaction(SIGALRM, & action, NULL);
    if ((msgid_rbt_inst_table = msgget(CLEF, IPC_CREAT | IPC_EXCL | 0600)) == -1)
		error("msgget msgid_rbt_inst_table");
    if ((msgid_rbt_vers_table = msgget(CLEF, IPC_CREAT | IPC_EXCL | 0600)) == -1)
		error("msgget msgid_rbt_vers_table");
    if (message.def_retire_conv)
        ratio_defaut = 2;
    else
        ratio_defaut = 1;
	puts("Robot installe table allume\n");
	while (1)
	{
        //ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg);
        if (msgrcv(msgid_rbt_inst_table, &message, sizeof(s_msg_env_sup), 0, 0) == -1)
            error("msgrcv msgid_rbt_inst_table");
        if (sigsetjmp(contexte_sigalrm, 1) == 0)
        {
            /* premier passage, installation */
            alarm(50 * RATIO_TEMPS);//peut etre probleme car fonctionne avec sec...
            usleep((1000000 * 50 - 10000) * RATIO_TEMPS * ratio_defaut);
            alarm(0);
            //envoyer a tous les tread x nb_machine
            for (int count = 0; 0 < nb_machine; i++)
            {
                if (msgsnd(msgid_machine, &message, sizeof(s_msg_env_sup), 0) == -1)
                    error("msgsnd msgid_machine");
            }
            sem_post(sem_convoyeur);//piece n est plus sur le convoyeur
            puts("Ok ! Piece sur la table\n");
        }
        else
        {
            /* On est arrive par SIGALRM */
            puts("\n==== Systeme en état de défaillance Robot_intall_table! ====\n");
            exit(EXIT_FAILURE);
        }
	}
	puts("Robot installe table eteint\n");
    return (NULL);
}


void			creation_robot_install_table(void)
{
	pthread_t	thread_id;
	long		i;

	i = 0;
	if (pthread_create(&thread_id, 0, fonc_thread_rbt_install, (void*)i) != 0)
	{
		error("Creation Robot installe table");
		usleep(3000);
	}
}
