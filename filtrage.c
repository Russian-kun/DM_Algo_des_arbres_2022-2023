#include "ABR.h"
#define NB_ARGS 5

typedef struct entry_dict_s {
    char* mot;
    int val;
} entry_t;

typedef struct dict_s {
    int size;
    struct entry_dict_s entry_t[NB_ARGS];
} dict_t;

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
    filtre(&((*A)->fg), filtref, utilises);
    filtre(&((*A)->fd), filtref, utilises);
    if (res > 0) {
        Noeud* supprime_noeud = *A;
        *A = (*A)->fg;
        // ajout(A, supprime_noeud->mot);
        free(supprime_noeud);
    }
    return res;
}

dict_t get_params(int argc, char* argv[]) {
    dict_t dict;
    dict.size = 0;
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            // dict.entry_t[i].mot = "help";
            // dict.entry_t[i].val = 1;
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

int is_visuel(dict_t dict) {
    for (int i = 0; i < dict.size; i++) {
        if (strcmp(dict.entry_t[i].mot, "visuel") == 0) {
            return dict.entry_t[i].val;
        }
    }
    return 0;
}

int main(int argv, char* argc[]) {
    if (argv < 3) {
        printf("Usage: ./filtre <texte> <filtre>\n");
        printf("  -h, --help  \tAffiche l'aide.\n");
        return 1;
    }
    dict_t dict = get_params(argv, argc);
    char** files = get_files(dict);
    char* texte = files[0];
    char* filtref = files[1];
    int v = is_visuel(dict);
    free(files);

    Arbre texte_filtre = NULL, texte_original = NULL, filtre_arbre = NULL, utilises = NULL;
    cree_arbre(texte, &texte_filtre);
    cree_arbre(texte, &texte_original);
    cree_arbre(filtref, &filtre_arbre);

    filtre(&texte_filtre, filtre_arbre, &utilises);
    // affiche sur le terminal les mots présents dans le fichier
    // texte mais qui ne sont pas dans filtre, puis les mots
    // présents simultanément dans les deux fichiers.
    printf("Mots présents dans le texte mais pas dans le filtre: \n");
    parcours_infixe(texte_filtre);
    printf("\nMots présents dans le texte et dans le filtre: \n");
    parcours_infixe(utilises);
    if (v) {
        dessine("texte", texte_original);
        dessine("filtre", filtre_arbre);
        dessine("filtrage", texte_filtre);
        dessine("en_commun", utilises);

        system("rm *.dot");
    }
    libere(&texte_filtre);
    libere(&texte_original);
    libere(&filtre_arbre);
    libere(&utilises);
    return 0;
}
