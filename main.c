/*
 * main.c
 *
 *  Created on: 5 janv. 2024
 *      Author: test
 */

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct col col_t;

struct col
{
	int nc;  //column number
	int val;  //value
	col_t *pc; //pointer to the next column
};

typedef col_t *pc_t; //pc_t is a pointer to col_t type

typedef struct line line_t;
struct line
{
	line_t *pl; //Pointer to next line
	int nl;  // line number
	col_t *pc; //pointer to first column element
};

typedef line_t *pl_t;    //pl_t is a pointer to line_t type


pl_t get_line (pl_t M, int nl)
{
	while (M != NULL)
	{
		if (M->nl==nl)
		{
			if (M->pc!=NULL)
			{
				return M;
			}
		}
		M=M->pl;
	}
	return M;
}

pc_t get_item(pl_t M, int nl,int nc)
{
pl_t line = get_line(M, nl);

  if (line != NULL) {
      col_t *current_col = line->pc;
      while (current_col != NULL) {
          if (current_col->nc == nc) {
              return current_col;
          }
          current_col = current_col->pc;
      }
  }

  return NULL;
}

pl_t insert_line(pl_t *M, int nl)
{
	//vérification que lq ligne n'existe pas
	pl_t existing_line;
	existing_line=get_line (*M,nl);
	if (existing_line!=NULL)
		{
			return existing_line; //on la retourne si elle y est deja
		}

	//nouvelle ligne
	pl_t new_line=(pl_t)malloc(sizeof(line_t));
	if (new_line == NULL)
		{
		    printf("Erreur d'allocation mémoire pour la nouvelle ligne.\n");
		    exit(EXIT_FAILURE);
		}
	//initiation de la ligne
	new_line->pl = NULL;
	new_line->nl = nl;
    new_line->pc = NULL;
    // Insérer la nouvelle ligne à sa place
       if (*M == NULL || nl < (*M)->nl) {
           new_line->pl = *M;
           *M = new_line;
       } else {
           pl_t current_line = *M;

           while (current_line->pl != NULL && current_line->pl->nl < nl) {
               current_line = current_line->pl;
           }

           new_line->pl = current_line->pl;
           current_line->pl = new_line;
       }

       return new_line; // Retourner l'adresse de la nouvelle ligne
}


pc_t insert_val(pl_t *M, int nl, int nc, int val) {
    // Insérer ou récupérer la ligne
    pl_t line = insert_line(M, nl);

    // Parcourir les colonnes de la ligne
    col_t *current_col = line->pc;
    col_t *prev_col = NULL;

    while (current_col != NULL && current_col->nc < nc) {
        prev_col = current_col;
        current_col = current_col->pc;
    }

    // Vérifier si la colonne existe déjà
    if (current_col != NULL && current_col->nc == nc) {
        // Modifier la valeur existante
        current_col->val = val;
        return current_col;
    } else {
        // Créer une nouvelle colonne
        col_t *new_col = (col_t *)malloc(sizeof(col_t));
        if (new_col == NULL) {
            fprintf(stderr, "Erreur d'allocation mémoire pour la nouvelle colonne.\n");
            exit(EXIT_FAILURE);
        }

        // Initialiser la nouvelle colonne
        new_col->nc = nc;
        new_col->val = val;
        new_col->pc = current_col;

        // Insérer la nouvelle colonne à sa place
        if (prev_col == NULL) {
            line->pc = new_col;
        } else {
            prev_col->pc = new_col;
        }

        return new_col; // Retourner l'adresse de la nouvelle colonne
    }
}

void list_from_array (pl_t *M, int *t, int nl, int nc)
{
	int nb_lignes_occupees=0;
	int somme=0;

	//parcours du tableau pour chercher les lignes non vides
	for (int i=0; i<nl; i++)
	{
		for (int j=0; j<nc; j++)
		{
			somme=somme+(*(t+(i*nc)+j));
		}
		if (somme==0)
		{
			nb_lignes_occupees++;
		}
		somme=0;
	}
	//creation de lignes non vides dans M
	while (nb_lignes_occupees!=1)
	{
		insert_line(M,nb_lignes_occupees);
		nb_lignes_occupees--;
	}

	//recherche et creation des colonnes non vides
	int val=0;
	for (int p=0; p<nl; p++)
	{
		for (int l=0; l<nc; l++)
		{
			val=(*(t+(p*nc)+l));
			if (val!=0)
			{
				insert_val(M, p + 1, l + 1, val);
			}
		}
		val=0;

	}

}

void list_display(pl_t M)
{
	while (M!=NULL)
	{
		printf("[%d] ->",M->nl);
		pc_t col=(M->pc);
		while (col!=NULL)
		{
			printf("[%d] ",col->nc);
			printf("%d ",col->val);
			if(col->pc==NULL)
			{
				printf("*");
			}
			col=col->pc;
		}
		printf("\n");
		M=M->pl;
	}
}

void mat_display(pl_t M, int nl, int nc)
{
	for (int i=1;i<=nl;i++)
	{
		for (int j=1;j<=nc;j++)
		{
			pc_t col=get_item(M,i,j);

			if (col!=NULL)
			{
				printf("%d",col->val);
			}else{printf("O");}
		}
		printf("\n");
	}
	printf("\n");
}

void list_destroy(pl_t *M)
{
	    while (*M != NULL) {
	        pl_t temp_line = *M;
	        *M = (*M)->pl;

	        col_t *current_col = temp_line->pc;
	        while (current_col != NULL) {
	            col_t *temp_col = current_col;
	            current_col = current_col->pc;
	            free(temp_col);
	        }

	        free(temp_line);
	    }
}
//marche pas car il crée des lignes entre les lignes de MC qui ont des colonnes qui pointent vers rien.
void list_acc(pl_t *MD, pl_t M)
{
	int nl=(M->nl);
    while (M != NULL)
    {
        pl_t line = get_line(*MD,nl);

        if (line == NULL)
        {
            line = insert_line(MD, M->nl);
        }

        col_t *current_col = M->pc;
        while (current_col != NULL)
        {
            insert_val(&line, M->nl, current_col->nc, current_col->val);
            current_col = current_col->pc;
        }
        M = M->pl;
        if(M!=NULL)
        {
            nl=(M->nl);
        }

    }
}

//il est bon mais ne marche pas car celui d'avant est faux
pl_t list_sum(pl_t M1, pl_t M2) {
    pl_t result = NULL;

    // Copy M1 to result
    list_acc(&result, M1);

    // Add M2 to result
    list_acc(&result, M2);

    return result;
}

int main (void)
{
	pl_t M= NULL;
	int TA[5][4]= {{0,2,0,0},{0,0,4,0},{0,0,3,1},{0,0,0,0},{0,1,0,8}};
	int TB[5][4]= {{0,4,0,0},{1,0,2,0},{0,0,5,0},{0,0,0,0},{0,6,0,0}};
	pl_t MA= NULL;
	pl_t MB= NULL;
	pl_t MC= NULL;
	int nl=3;
	M=get_line (MA,nl);
	// Insérer une nouvelle ligne avec le numéro 2
	    pl_t line1 = insert_line(&M, 2);

	    // Insérer une nouvelle ligne avec le numéro 1
	    pl_t line2 = insert_line(&M, 1);

	    // Insérer une nouvelle ligne avec le numéro 3
	    pl_t line3 = insert_line(&M, 3);

	    // Afficher les adresses des lignes
	    printf("Adresse de la ligne 1 : %p\n", (void *)line1);
	    printf("Adresse de la ligne 2 : %p\n", (void *)line2);
	    printf("Adresse de la ligne 3 : %p\n", (void *)line3);


	//build MA list from TA array
	list_from_array(&MA,(int*)TA,5,4);

	printf("List A is: \n");

	list_display(MA);
	printf("Matrix A is :\n");
	mat_display(MA,5,4);
	printf("\n");


	//build MB list from TB array
	list_from_array(&MB,(int*)TB,5,4);

	printf("List B is: \n");
	list_display(MB);
	printf("Matrix B is :\n");
	mat_display(MB,5,4);
	printf("\n");


	//compute sum MC=MA+MB
	MC= list_sum(MA,MB);

	printf("List C=(A+B) is: \n");
	list_display(MC);
	printf("Matrix C is :\n");
	mat_display(MC,5,4);
	printf("\n");
	/*
	//free memory
	printf("Now cleaning memory... \n");
	list_destroy(&MA);
	list_display(MA);
	list_destroy(&MB);
	list_display(MB);
	list_destroy(&MC);
	list_display(MC);
	*/
	return 0;
}
