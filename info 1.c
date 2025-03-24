#include <stdio.h>
#include <stdlib.h>

typedef struct Noeud {
    int valeur;
    struct Noeud *suivant;
} Noeud;

Noeud *cree(int _value) {
    Noeud *NV = (Noeud *)malloc(sizeof(Noeud));
    NV->valeur = _value;
    NV->suivant = NULL;
    return NV;
}

void affiche(Noeud *debut) {
    Noeud *courant = debut;
    while (courant != NULL) {
        printf("la valeur est %d\n", courant->valeur);
        courant = courant->suivant;
    }
}

Noeud *ajouterD(Noeud *debut, int _value) {
    Noeud *NV = (Noeud *)malloc(sizeof(Noeud));
    NV->valeur = _value;
    NV->suivant = debut;
    return NV;
}

Noeud *ajouterF(Noeud *debut, int _value) {
    Noeud *NV = (Noeud *)malloc(sizeof(Noeud));
    NV->valeur = _value;
    NV->suivant = NULL;
    if (debut == NULL) return NV;
    Noeud *courant = debut;
    while (courant->suivant != NULL) {
        courant = courant->suivant;
    }
    courant->suivant = NV;
    return debut;
}

void rechercher(Noeud *debut, int _value) {
    Noeud *courant = debut;
    while (courant != NULL) {
        if (courant->valeur == _value) {
            printf("la valeur existe\n");
            return;
        }
        courant = courant->suivant;
    }
    printf("la valeur n'existe pas\n");
}

int taille(Noeud *debut) {
    int taille = 0;
    Noeud *courant = debut;
    while (courant != NULL) {
        taille++;
        courant = courant->suivant;
    }
    return taille;
}

Noeud *insertion(Noeud *debut, int pos, int val) {
    Noeud *NV = (Noeud *)malloc(sizeof(Noeud));
    NV->valeur = val;
    NV->suivant = NULL;
    int size = taille(debut);
    if (pos < 1 || pos > size + 1) {
        printf("la position est incorrecte\n");
        return debut;
    }
    if (pos == 1) {
        NV->suivant = debut;
        return NV;
    }
    Noeud *courant = debut;
    for (int i = 1; i < pos - 1; i++) {
        courant = courant->suivant;
    }
    NV->suivant = courant->suivant;
    courant->suivant = NV;
    return debut;
}

Noeud *suppressionD(Noeud *debut) {
    if (debut == NULL) {
        printf("la liste est vide\n");
        return NULL;
    }
    Noeud *P = debut;
    debut = debut->suivant;
    free(P);
    return debut;
}

Noeud *suppressionF(Noeud *debut) {
    if (debut == NULL) {
        printf("la liste est vide\n");
        return NULL;
    }
    if (debut->suivant == NULL) {
        free(debut);
        return NULL;
    }
    Noeud *courant = debut;
    while (courant->suivant->suivant != NULL) {
        courant = courant->suivant;
    }
    free(courant->suivant);
    courant->suivant = NULL;
    return debut;
}

Noeud *suppressionP(Noeud *debut, int pos) {
    if (debut == NULL) {
        printf("la liste est vide\n");
        return NULL;
    }
    int size = taille(debut);
    if (pos < 1 || pos > size) {
        printf("la position est invalide\n");
        return debut;
    }
    if (pos == 1) {
        Noeud *tmp = debut;
        debut = debut->suivant;
        free(tmp);
        return debut;
    }
    Noeud *courant = debut;
    for (int i = 1; i < pos - 1; i++) {
        courant = courant->suivant;
    }
    Noeud *tmp = courant->suivant;
    courant->suivant = tmp->suivant;
    free(tmp);
    return debut;
}

Noeud *modifierD(Noeud *debut, int _value) {
    if (debut == NULL) return NULL;
    debut->valeur = _value;
    return debut;
}

Noeud *modifierF(Noeud *debut, int _value) {
    if (debut == NULL) {
        printf("la liste est vide\n");
        return NULL;
    }
    Noeud *courant = debut;
    while (courant->suivant != NULL) {
        courant = courant->suivant;
    }
    courant->valeur = _value;
    return debut;
}

Noeud *modifierP(Noeud *debut, int pos, int _value) {
    if (debut == NULL) {
        printf("la liste est vide\n");
        return NULL;
    }
    int size = taille(debut);
    if (pos < 1 || pos > size) {
        printf("la position est invalide\n");
        return debut;
    }
    Noeud *courant = debut;
    for (int i = 1; i < pos; i++) {
        courant = courant->suivant;
    }
    courant->valeur = _value;
    return debut;
}

int main() {
    Noeud *debut = NULL;
    Noeud *P = cree(10);
    Noeud *D = cree(20);
    Noeud *T = cree(30);

    printf("adresse du noeud P : %p\n", P);
    printf("adresse du noeud D : %p\n", D);
    printf("adresse du noeud T : %p\n", T);

    debut = P;
    P->suivant = D;
    D->suivant = T;

    affiche(debut);

    debut = ajouterD(debut, 100);
    affiche(debut);

    debut = ajouterF(debut, 200);
    affiche(debut);

    rechercher(debut, 20);

    printf("la taille est %d\n", taille(debut));

    debut = insertion(debut, 3, 555);
    affiche(debut);

    debut = suppressionD(debut);
    affiche(debut);

    debut = suppressionF(debut);
    affiche(debut);

    debut = suppressionP(debut, 2);
    affiche(debut);

    debut = modifierD(debut, 2024);
    affiche(debut);

    debut = modifierF(debut, 2025);
    affiche(debut);

    debut = modifierP(debut, 1, 2000);
    affiche(debut);

    return 0;
}
