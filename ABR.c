#include "ABR.h"

Noeud* alloue_noeud(char* mot) {
    // alloue la mémoire pour le nouveau noeud
    Noeud* nouveau_noeud = (Noeud*)malloc(sizeof(Noeud));
    // alloue la mémoire pour la chaîne de caractères 'nouveau_mot'
    char* nouveau_mot = (char*)malloc((strlen(mot) + 1) * sizeof(char));
    // ça copie le chaîne de caractère 'mot' dans la mémoire allouée pour 'nouveau_mot'
    strcpy(nouveau_mot, mot);
    // assigne 'nouveau_mot' au champ 'mot' du nouveau noeud
    nouveau_noeud->mot = nouveau_mot;
    nouveau_noeud->fd = NULL;
    nouveau_noeud->fg = NULL;
    return nouveau_noeud;
}

void parcours_infixe(Arbre A) {
    if (A != NULL) {
        parcours_infixe(A->fg);
        printf("%s\n", A->mot);
        parcours_infixe(A->fd);
    }
}

Noeud* ajout(Arbre* A, char* mot) {
    if (*A == NULL) {
        *A = alloue_noeud(mot);
    } else if (strcmp(mot, (*A)->mot) < 0)
        return ajout(&((*A)->fg), mot);
    else if (strcmp(mot, (*A)->mot) > 0)
        return ajout(&((*A)->fd), mot);
    return NULL;
}

Noeud* extrait_max(Arbre* A) {
    if (*A == NULL)
        return NULL;
    else if ((*A)->fd == NULL) {
        Noeud* supprime_noeud = *A;
        *A = (*A)->fg;
        return supprime_noeud;
    }
    return extrait_max(&((*A)->fd));
}

Noeud* suppression(Arbre* A, char* mot) {
    Noeud* p = *A;
    Noeud* parent = NULL;
    while (p != NULL && strcmp(p->mot, mot) != 0) {  // Recherche du noeud à supprimer
        parent = p;
        if (strcmp(mot, p->mot) < 0) {
            p = p->fg;
        } else {
            p = p->fd;
        }
    }
    if (p == NULL) return NULL;  // le mot n'est pas présent dans l'arbre
    Noeud* q = NULL;
    if (p->fg == NULL) {  // cas où le noeud à supprimer n'a pas de fils gauche
        q = p->fd;
    } else if (p->fd == NULL) {  // cas où le noeud à supprimer n'a pas de fils droit
        q = p->fg;
    } else {  // cas général où le noeud à supprimer a deux fils
        // Recherche du plus grand noeud dans le sous-arbre gauche
        Noeud* r = p->fg;
        Noeud* rp = p;
        while (r->fd != NULL) {
            rp = r;
            r = r->fd;
        }
        // Echange du contenu du noeud à supprimer avec celui du plus grand noeud du sous-arbre gauche
        q = r;
        if (rp != p) {
            rp->fd = q->fg;
            q->fg = p->fg;
        }
        q->fd = p->fd;
    }
    if (parent == NULL) {  // cas où le noeud à supprimer est la racine de l'arbre
        *A = q;
    } else if (p == parent->fg) {  // cas où le noeud à supprimer est le fils gauche de son parent
        parent->fg = q;
    } else {  // cas où le noeud à supprimer est le fils droit de son parent
        parent->fd = q;
    }
    // Libération de la mémoire occupée par le noeud supprimé
    free(p->mot);
    free(p);
    return q;
}
/*
On initialise deux pointeurs 'p' et 'parent' à la racine de l'arbre.
On utilise 'p' pour parcourir l'arbre et 'parent' pour suivre le parent du noeud
courant 'p'.

On effectue une recherche dans l'arbre pour trouver le noeud contenant le mot mot.
Si mot est plus petit que le mot contenu dans le noeud courant 'p', on se déplace
vers le fils gauche de 'p', sinon on se déplace vers le fils droit de 'p'.
Si on trouve le noeud contenant mot, on sort de la boucle avec 'p' pointant sur ce
noeud, sinon on sort de la boucle avec 'p' valant NULL.

Sinon, on cherche le noeud 'q' qui va remplacer le noeud 'p' dans l'arbre. Si 'p'
n'a pas de fils gauche, on prend 'q' égal à son fils droit, sinon si 'p' n'a pas de
fils droit, on prend 'q' égal à son fils gauche. Dans le cas général où 'p' a
deux fils, on recherche le plus grand noeud dans le sous-arbre gauche de 'p'
en partant de 'p->gauche'. On stocke le parent du plus grand noeud trouvé dans
'rp', et le noeud trouvé lui-même dans 'r'. On échange ensuite le contenu des
noeuds 'p' et 'q', c'est-à-dire leur champ 'mot' et leur fils gauche et droit.
Si le plus grand noeud trouvé 'r' n'est pas le fils gauche de 'p', on connecte
'rp' à 'q->gauche'. Enfin, on renvoie le pointeur 'q'.

Si 'p' est la racine de l'arbre, on met 'q' à la racine de l'arbre en faisant
'*A = q'. Sinon, si 'p' est le fils gauche de son parent 'parent', on met 'q' à
la place de 'p' comme fils gauche de 'parent', sinon on met 'q' à la place de 'p'
comme fils droit de 'parent'.
*/

void libere(Arbre* A) {
    if (*A != NULL) {
        libere(&((*A)->fg));
        libere(&((*A)->fd));
        free((*A)->mot);
        free(*A);
        *A = NULL;
    }
}

void ecrireDebut(FILE* f) {
    fprintf(f, "digraph arbre {\n\tnode [shape=record, height =.1]\n\tedge [tailclip =false , arrowtail = dot, dir=both];\n");
}

void ecrireFin(FILE* f) {
    fprintf(f, "}");
}

void ecrireArbre(FILE* f, Arbre a) {
    assert(a != NULL);

    char* val = a->mot;
    fprintf(f, "\tn%p [label =\"<gauche> | <valeur> %s | <droit>\"];\n", a, val);
    if (a->fg) {
        fprintf(f, "\tn%p:gauche:c -> n%p:valeur;\n", a, a->fg);
        ecrireArbre(f, a->fg);
    }
    if (a->fd) {
        fprintf(f, "\tn%p:droit:c -> n%p:valeur;\n", a, a->fd);
        ecrireArbre(f, a->fd);
    }
}

void dessine(char* nom, Arbre A) {
    FILE* f = fopen(nom, "w");
    ecrireDebut(f);
    ecrireArbre(f, A);
    ecrireFin(f);
}

int cree_arbre(char* nom, Arbre* A) {
    FILE* f = fopen(nom, "r");
    if (f == NULL) {
        return 0;
    }
    char mot[100];
    while (fscanf(f, "%s", mot) != EOF) {
        ajout(A, mot);
    }
    fclose(f);
    return 1;
}