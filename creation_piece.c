#include "header.h"

s_piece		**creation_piece(int nb_machine, s_piece **piece)
{
	int		i;
	int		i_bis;
	int		index;
	int		nb_type_piece;
	int		nb_type_piece2;
	int		somme_piece;
	int		num_def_piece;
	int 	defaut_machine;

	nb_type_piece = nb_machine;
	nb_type_piece2 = nb_machine;
	somme_piece = 0;
	i = 0;
	i_bis = 0;
	index = 0;

	nb_piece = (int*)malloc(sizeof(int) * nb_machine);
	if (!nb_piece)
		error("malloc nb_piece");
	piece = (s_piece**)malloc(sizeof(piece) * nb_machine);		//ajouter le free(2) dans le signal
	if (!piece)
		error("malloc creation tableau piece");
    while (nb_type_piece)		//on cree un certain nombre de piece d'un certain type pour une machine
    {
        printf("Ici, nous allons créer les pièces à usiner.\nPour la machine %d Combien en voulez-vous ?\n", nb_type_piece - 1);
        nb_piece[nb_type_piece - 1] = lire_nombre_p();
        nb_type_piece--;
    }
    while (nb_type_piece2)
    {
        somme_piece += nb_piece[nb_type_piece2 - 1];
        printf("nb piece machine %d: %d\n", nb_type_piece2 - 1, nb_piece[nb_type_piece2 - 1]);
        nb_type_piece2--;
    }
    printf("\nVoici la somme des pieces: %d\n\n", somme_piece);
	somme_piece_sup = somme_piece;
	if (!somme_piece)
	{
		puts("Vous n'avez cree aucune piece");
		printf("%s\n", "Exit...");
		fonction_spr_sem_msg();
		exit(0);
	}

	while (index < nb_machine)
	{
		piece[index] = (s_piece*)malloc(sizeof(piece) * nb_piece[index]);
		if (!piece[index])
			error("malloc creation tableau piece[index]");
		index++;
	}
	puts("Dans ce test y aura-t-il des erreurs?\n\		
			0. non\n\				//on demande si il y aura des erreurs et si oui, quel type
			1. defaut robot entre\n\ 
			2. defaut robot sortie\n\
			3. defaut retire convoyeur pour table\n\
			4. defaut duree de travail machine");
	defaut = lire_nombre_defaut();
	while (i < nb_machine)//init defaut 0		on initialise les pieces comme n'ayant aucun défaut
	{
		while (i_bis < nb_piece[i])
		{
			piece[i][i_bis].def_in = false;
			piece[i][i_bis].def_out = false;
			piece[i][i_bis].def_retire_conv = false;
			piece[i][i_bis].def_work_machine = false;
			i_bis++;
		}
		i++;
	}
	/* ==> test affichage des pieces
	i = 0;
	printf("nb_machine: %d\n\n", nb_machine);
	while (i < nb_machine)
	{
		i_bis = 0;
		while (i_bis < nb_piece[i])
		{
			printf("nb_pieces: %d\n", nb_piece[i]);
			printf("piece type %d: %d\n", i, i_bis);
			i_bis++;
		}
		printf("\n");
		i++;
	}
	*/
	printf("Voilà, nous avons créé les pieces!");
	if (defaut)		//si il y a des defauts, on les mets en place
	{
		puts("\nInstallation du defaut:");
		puts("Rentrer un numero de type de piece:");
		do {
			defaut_machine = lire_numero_type_def(nb_machine);
		} while(nb_piece[defaut_machine] == 0);
		printf("Defaut sur piece type: %d\n", defaut_machine);
		puts("Rentrer un numero de la piece:");
		num_def_piece = lire_numero_piece(nb_piece[defaut_machine]);
		switch (defaut) {
			case 1:
			piece[defaut_machine][num_def_piece].def_in = true;
			break;
			case 2:
			piece[defaut_machine][num_def_piece].def_out = true;
			break;
			case 3:
			piece[defaut_machine][num_def_piece].def_retire_conv = true;
			break;
			case 4:
			piece[defaut_machine][num_def_piece].def_work_machine = true;
			break;
		}
	printf("========== Defaut sur la piece de type %d, numero %d ==========\n", defaut_machine, num_def_piece);
	}
	printf("\n\n=============== FIN DE LA CREATION DES PIECES ===============\n\n");
	return (piece);
}
