#include "ABR.h"
#define NB_ARGS 5

/// @brief Structure de données pour stocker les arguments
typedef struct entry_dict_s {
    char* mot;
    int val;
} entry_t;

/// @brief Structure de données pour stocker les arguments
typedef struct dict_s {
    int size;
    struct entry_dict_s entry_t[NB_ARGS];
} dict_t;

/*supprime de l’arbre *A tous les nœuds contenant un mot présent dans l’arbre *filtre et insère ce mot dans l’ABR *utilises*/
int filtre(Arbre* A, Arbre filtref, Arbre* utilises) {
    if (*A == NULL) {
        return 0;
    }
    int res = 0;
    filtre(&((*A)->fg), filtref, utilises);
    filtre(&((*A)->fd), filtref, utilises);
    if (recherche(filtref, (*A)->mot) != NULL) {
        Noeud* suppr = suppression(A, (*A)->mot);
        insere(utilises, suppr);
        res = 1;
    }
    return res;
}

/*Recupere les parametres de la ligne de commande*/
dict_t get_params(int argc, char* argv[]) {
    dict_t dict;
    dict.size = 0;
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            printf("Usage: ./filtre <texte> <filtre>\n");
            printf("Filtre le texte en supprimant les mots présents dans le filtre.\n");
            printf("Affiche les mots présents dans le texte mais pas dans le filtre, puis les mots présents simultanément dans les deux fichiers.\n");
            printf("Les fichiers texte et filtre doivent être dans cette ordre\n");
            printf("\nOptions: \n");
            printf("  -h, --help  \tAffiche l'aide.\n");
            printf("  -v, --visuel\tCree des fichiers pdf pour visualiser les arbres.\n");
            exit(0);
        } else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--visuel") == 0) {
            dict.entry_t[i].mot = "visuel";
            dict.entry_t[i].val = 1;
        } else {
            dict.entry_t[i].mot = argv[i];
            dict.entry_t[i].val = 0;
        }
        dict.size++;
    }
    return dict;
}

/*recupere les fichiers texte et filtre. Retourne NULL si il n'y a pas 2 fichiers*/
char** get_files(dict_t dict) {
    char** files = malloc(sizeof(char*) * 2);
    int j = 0;
    for (int i = 1; i < dict.size && j < 2; i++) {
        if (dict.entry_t[i].val == 1) {
            continue;
        }
        files[j] = dict.entry_t[i].mot;
        j++;
    }
    return j == 2 ? files : NULL;
}

/*verifie si l'option visuel est presente dans les arguments*/
int is_visuel(dict_t dict) {
    for (int i = 0; i < dict.size; i++) {
        if (strcmp(dict.entry_t[i].mot, "visuel") == 0) {
            return dict.entry_t[i].val;
        }
    }
    return 0;
}

int main() {
    char* texte = "./test/texte1.txt";
    char* filtref = "./test/filtre1.txt";

    Arbre texte_filtre = NULL, texte_original = NULL, filtre_arbre = NULL, utilises = NULL;
    cree_arbre(texte, &texte_filtre);
    cree_arbre(texte, &texte_original);
    cree_arbre(filtref, &filtre_arbre);
    // free(files);

    filtre(&texte_filtre, filtre_arbre, &utilises);
    libere(&utilises);
    if (1) {
        dessine("texte", texte_original);
        dessine("filtre", filtre_arbre);
        dessine("filtrage", texte_filtre);
        dessine("en_commun", utilises);

        system("rm *.dot");
    }
    libere(&texte_original);
    libere(&filtre_arbre);
    libere(&texte_filtre);
    libere(&utilises);
    return 0;
}