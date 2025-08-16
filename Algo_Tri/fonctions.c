/*
 * fonctions.c
 *
 *  Created on: 7 janv. 2024
 *      Author: test
 */
#include "fonctions.h"
#include <stdio.h>
#include <stdlib.h>


// Fonction utilitaire pour échanger deux éléments dans un tableau
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


void affiche_tab(int* t, int taille)
{
	for (int i=0;i<taille;i++)
	{
		printf("%d;",t[i]);
	}
	printf("\n");
}


void tri_bulles(int* t,int taille)
{
	int l=0;
	int permu=0;
	while (l<taille)
	{
		for (int i=1;i<taille-l;i++)
		{
			if (t[i-1]>t[i])
			{
				permu=t[i];
				t[i]=t[i-1];
				t[i-1]=permu;
			}
		}

		l++;

	}
}

void tri_selec(int* t,int taille)
{
	int max=t[0];
	int l=0;
	int ind=0;
	while (l<taille-1)
	{
		for (int i=l+1;i<taille;i++)
			{
				if (max<t[i])
					{
						max=t[i];
						ind=i;
					}
			}
		int  jaja=0;
		jaja=t[taille-1-l];
		t[taille-1-l]=max;
		t[ind]=jaja;
		l++;
		max=0;

	}
}


// Fusionne deux sous-tableaux de arr[]
// Le premier sous-tableau est arr[l..m]
// Le deuxième sous-tableau est arr[m+1..r]
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Crée des tableaux temporaires
    int L[n1], R[n2];

    // Copie des données dans les tableaux temporaires L[] et R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Fusionne les tableaux temporaires L[] et R[] dans arr[l..r]
    i = 0; // Index initial du premier sous-tableau
    j = 0; // Index initial du deuxième sous-tableau
    k = l; // Index initial du tableau fusionné

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copie les éléments restants de L[], s'il y en a
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copie les éléments restants de R[], s'il y en a
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Fonction principale qui trie arr[l..r] en utilisant la méthode merge()
void mergeSort(int arr[], int l, int r)
{
    if (l < r) {
        // Trouver le point médian
        int m = l + (r - l) / 2;

        // Trier la première et la deuxième moitié
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        // Fusionner les moitiés triées
        merge(arr, l, m, r);
    }
}





// Fonction utilitaire pour choisir le bon pivot et partitionner le tableau
int partition(int arr[], int low, int high) {
    int pivot = arr[high];  // Choix du pivot (dans cet exemple, le dernier élément)
    int i = low - 1;  // Index du plus petit élément

    for (int j = low; j <= high - 1; j++) {
        // Si l'élément courant est plus petit ou égal au pivot
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);  // Échange arr[i] et arr[j]
        }
    }

    swap(&arr[i + 1], &arr[high]);  // Échange arr[i+1] et le pivot
    return i + 1;
}

// Fonction principale de tri rapide
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        // Partitionne le tableau et obtient l'index du pivot
        int pi = partition(arr, low, high);

        // Trie les éléments avant et après le pivot
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

