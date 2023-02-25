#include "ABR.h"

// supprime de l’arbre *A tous les nœuds contenant un mot présent dans l’arbre *filtre et
// insère ce mot dans l’ABR *utilises
int filtre(Arbre* A, Arbre filtref, Arbre* utilises) {
    if (*A == NULL) {
        return 0;
    }
    int res = 0;
    if (recherche(filtref, (*A)->mot) != NULL) {
        ajout(utilises, (*A)->mot);
        res = 1;
    }
    res += filtre(&((*A)->fg), filtref, utilises);
    res += filtre(&((*A)->fd), filtref, utilises);
    if (res > 0) {
        Noeud* supprime_noeud = *A;
        *A = (*A)->fg;
        ajout(A, supprime_noeud->mot);
        free(supprime_noeud);
    }
    return res;
}

int main(int argv, char* argc[]) {
    if (argv != 3) {
        printf("Usage: %s <texte> <filtre>\n", argc[0]);
        // printf("Filtre le texte en supprimant les mots présents dans le filtre.\n");
        // printf("Affiche les mots présents dans le texte mais pas dans le filtre, puis les mots présents simultanément dans les deux fichiers.\n");
        // printf("\nOptions: \n");
        printf("  -h, --help  \tAffiche l'aide.\n");
        // printf("  -v, --visuel\tCree des fichiers pdf pour visualiser les arbres.\n");
        return 1;
    }
    char* texte = argc[1];
    char* filtref = argc[2];
    Arbre texte_arbre = NULL, filtre_arbre = NULL, utilises = NULL;
    cree_arbre(texte, &texte_arbre);
    cree_arbre(filtref, &filtre_arbre);

    filtre(&texte_arbre, filtre_arbre, &utilises);
    // affiche sur le terminal les mots présents dans le fichier
    // texte mais qui ne sont pas dans filtre, puis les mots
    // présents simultanément dans les deux fichiers.
    printf("Mots présents dans le texte mais pas dans le filtre: \n");
    parcours_infixe(texte_arbre);
    printf("Mots présents dans le texte et dans le filtre: \n");
    parcours_infixe(utilises);
    return 0;
}