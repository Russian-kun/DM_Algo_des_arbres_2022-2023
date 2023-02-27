#ifndef ABR_H
#define ABR_H

#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct noeud {
    char* mot;
    struct noeud *fg, *fd;
} Noeud, *Arbre;

Noeud* alloue_noeud(char* mot);

void parcours_infixe(Arbre A);

Noeud* ajout(Arbre* A, char* mot);

Noeud* extrait_max(Arbre* A);

Noeud* recherche(Arbre A, char* mot);

Noeud* extrait_Noeudmin(Arbre* A);

Noeud* suppression(Arbre* A, char* mot);

void libere(Arbre* A);

void ecrireDebut(FILE* f);

void ecrireFin(FILE* f);

void ecrireArbre(FILE* f, Arbre a);

void dessine(char* nom, Arbre A);

int cree_arbre(char* nom, Arbre* A);

#endif
