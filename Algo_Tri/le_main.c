/*
 * le_main.c
 *
 *  Created on: 7 janv. 2024
 *      Author: test
 */
#include "fonctions.h"
#include <stdio.h>
int main ()
{
	int t[10]={8,12,18,25,2,0,9,15,15,17};
	int arr[10]={8,12,18,25,2,0,9,15,15,17};
	int taille=10;
	affiche_tab(t,taille);
	tri_bulles(t,taille);
	affiche_tab(t,taille);
	affiche_tab(arr,taille);
	tri_selec(arr,taille);
	affiche_tab(arr,taille);
	quickSort(arr,0,taille);


	return 0;
}

