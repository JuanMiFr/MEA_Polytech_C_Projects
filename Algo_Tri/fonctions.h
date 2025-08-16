/*
 * fonctions.h
 *
 *  Created on: 7 janv. 2024
 *      Author: test
 */

#ifndef FONCTIONS_H_
#define FONCTIONS_H_


void swap(int *a, int *b);
void affiche_tab(int* t, int taille);
void tri_bulles(int* t,int taille);
void tri_selec(int* t,int taille);
void merge(int arr[], int l, int m, int r);
void mergeSort(int arr[], int l, int r);
int partition(int arr[], int low, int high);
void quickSort(int arr[], int low, int high);
#endif /* FONCTIONS_H_ */
