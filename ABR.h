#ifndef ABR_H
#define ABR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/// @brief Structure de données pour stocker les arguments
typedef struct noeud {
    char* mot;
    struct noeud *fg, *fd;
} Noeud, *Arbre;

/**
 * @brief Alloue un noeud avec le mot passé en paramètre
 *
 * @param mot
 * @return Noeud*
 */
Noeud* alloue_noeud(char* mot);

/**
 * @brief Affiche l'arbre en infixe (gauche, racine, droite)
 *
 * @param A
 */
void parcours_infixe(Arbre A);

/**
 * @brief Ajoute un mot dans l'arbre
 *
 * @param A
 * @param mot
 * @return Noeud*
 */
Noeud* ajout(Arbre* A, char* mot);

/**
 * @brief Insère un noeud dans l'arbre
 *
 * @param A
 * @param n
 * @return int
 */
int insere(Arbre* A, Noeud* n);

/**
 * @brief Retourne le noeud avec la valeur maximale de l'arbre.
 * Retourne NULL si l'arbre est vide
 *
 * @param A
 * @return Noeud*
 */
Noeud* extrait_max(Arbre* A);

/**
 * @brief Retourne le noeud dont le mot est passé en paramètre.
 * Retourne NULL si le mot n'est pas présent dans l'arbre
 *
 * @param A
 * @param mot
 * @return Noeud*
 */
Noeud* recherche(Arbre A, char* mot);

/**
 * @brief Retourne le noeud avec la valeur minimale de l'arbre.
 * Retourne NULL si l'arbre est vide
 *
 * @param A
 * @return Noeud*
 */
Noeud* extrait_Noeudmin(Arbre* A);

/**
 * @brief Supprime le noeud dont le mot est passé en paramètre.
 *
 * @param A
 * @param mot
 * @return Noeud*
 */
Noeud* suppression(Arbre* A, char* mot);

/**
 * @brief Libère l'arbre
 *
 * @param A
 */
void libere(Arbre* A);

/**
 * @brief Ecrit le début du fichier dot
 *
 * @param f
 */
void ecrireDebut(FILE* f);

/**
 * @brief Ecrit la fin du fichier dot
 *
 * @param f
 */
void ecrireFin(FILE* f);

/**
 * @brief Ecrit l'arbre dans le fichier dot
 *
 * @param f
 * @param a
 */
void ecrireArbre(FILE* f, Arbre a);

/**
 * @brief Cree un fichier dot et le compile en pdf
 *
 * @param nom
 * @param A
 */
void dessine(char* nom, Arbre A);

/**
 * @brief Cree un arbre à partir d'un fichier
 *
 * @param nom
 * @param A
 * @return int
 */
int cree_arbre(char* nom, Arbre* A);

#endif
