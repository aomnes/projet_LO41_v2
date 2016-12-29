#include "header.h"

s_piece		*creation_piece(int nb_machine)
{
	int		*nb_piece;
	int		i;
	int		i_bis;
	int		j;
	int		defaut;
	//int		nb_aleatoire;
    int     nb_type_piece;
    int     nb_type_piece2;
    int     somme_piece;
	s_piece	*piece;

	srand(time(NULL));
    nb_type_piece = nb_machine;
    nb_type_piece2 = nb_machine;
    somme_piece = 0;
    i = 0;
	j = 0;
	i_bis = 0;

    nb_piece = (int*)malloc(sizeof(int) * nb_machine);
    if (!nb_piece)
        error("malloc nb_piece");
    while (nb_type_piece)
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
	if (!somme_piece)
	{
		puts("Vous n'avez cree aucune piece");
        printf("%s\n", "Exit...");
		exit(0);
	}
	piece = (s_piece*)malloc(sizeof(piece) * somme_piece);		//ajouter le free(2) dans le signal
	if (!piece)
		error("malloc creation tableau pieces");
	puts("Dans ce test y aura-t-il des erreurs?\n\
            0. non\n\
            1. defaut robot entre\n\
            2. defaut robot sortie\n\
            3. defaut retire convoyeur pour table\n\
            4. defaut duree de travail machine");
	defaut = lire_nombre_defaut();
    while (i < somme_piece)
    {
        piece[i].id = i;
        piece[i].def_in = 0;
        piece[i].def_ou = 0;
        piece[i].def_retire_tapis = 0;
        piece[i].def_work_machine = 0;
        if (i_bis < nb_piece[j])
        	piece[i].usinage = j;
		else
		{
			j++;
			piece[i].usinage = j;
			i_bis = 0;
		}
		printf("type d usinage piece %d: %d\n", i, piece[i].usinage);
		i_bis++;
		i++;
    }
    /*
    for (i = 0; i < nb_piece; i++)
	{
		piece->id = i;
		nb_aleatoire = rand()%101;
		if (nb_aleatoire >=  && defaut != 0)////(rand()%(MAX - MIN + 1)) + MIN
			piece->defaut = 2;
		else
			piece->defaut = 1;
	}*/
	printf("Voilà, nous avons créé les pieces!");
	printf("\n\n=============== FIN DE LA CREATION DES PIECES ===============\n\n");
	return (piece);
}

int main(void)
{
    creation_piece(3);
    return (0);
}
