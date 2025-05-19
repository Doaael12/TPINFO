#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Etudiant {
    int id;
    char nom[50];
    float moyenne;
    struct Etudiant* suivant;
    struct Etudiant* precedent;
} Etudiant;

Etudiant* creer_etudiant() {
    Etudiant* nouveau = (Etudiant*)malloc(sizeof(Etudiant));
    printf("Entrez l'ID de l'etudiant: ");
    scanf("%d", &nouveau->id);
    printf("Entrez le nom de l'etudiant: ");
    scanf("%s", nouveau->nom);
    printf("Entrez la moyenne de l'etudiant: ");
    scanf("%f", &nouveau->moyenne);
    nouveau->suivant = NULL;
    nouveau->precedent = NULL;
    return nouveau;
}

int longueur(Etudiant* tete) {
    int count = 0;
    Etudiant* courant = tete;
    while (courant != NULL) {
        count++;
        courant = courant->suivant;
    }
    return count;
}

Etudiant* ajouter_position(Etudiant* tete, Etudiant* nouveau, int position) {
    if (position < 0 || position > longueur(tete)) {
        printf("Position invalide.\n");
        return tete;
    }

    if (position == 0) {
        nouveau->suivant = tete;
        if (tete != NULL) {
            tete->precedent = nouveau;
        }
        return nouveau;
    }

    Etudiant* courant = tete;
    for (int i = 0; i < position - 1; i++) {
        if (courant == NULL) {
            printf("Position invalide.\n");
            return tete;
        }
        courant = courant->suivant;
    }

    nouveau->suivant = courant->suivant;
    nouveau->precedent = courant;
    if (courant->suivant != NULL) {
        courant->suivant->precedent = nouveau;
    }
    courant->suivant = nouveau;

    return tete;
}

Etudiant* supprimer_position(Etudiant* tete, int position) {
    if (tete == NULL || position < 0 || position >= longueur(tete)) {
        printf("Position invalide.\n");
        return tete;
    }

    if (position == 0) {
        Etudiant* temp = tete->suivant;
        if (temp != NULL) {
            temp->precedent = NULL;
        }
        free(tete);
        return temp;
    }

    Etudiant* courant = tete;
    for (int i = 0; i < position; i++) {
        if (courant == NULL) {
            printf("Position invalide.\n");
            return tete;
        }
        courant = courant->suivant;
    }

    if (courant->precedent != NULL) {
        courant->precedent->suivant = courant->suivant;
    }
    if (courant->suivant != NULL) {
        courant->suivant->precedent = courant->precedent;
    }
    free(courant);

    return tete;
}

void afficher_liste(Etudiant* tete) {
    Etudiant* courant = tete;
    while (courant != NULL) {
        printf("ID: %d, Nom: %s, Moyenne: %.2f\n", courant->id, courant->nom, courant->moyenne);
        courant = courant->suivant;
    }
}

Etudiant* derniere_cellule(Etudiant* tete) {
    Etudiant* courant = tete;
    while (courant != NULL && courant->suivant != NULL) {
        courant = courant->suivant;
    }
    return courant;
}

void afficher_liste_inverse(Etudiant* dernier) {
    Etudiant* courant = dernier;
    while (courant != NULL) {
        printf("ID: %d, Nom: %s, Moyenne: %.2f\n", courant->id, courant->nom, courant->moyenne);
        courant = courant->precedent;
    }
}

int chercher_etudiant(Etudiant* tete, int id) {
    Etudiant* courant = tete;
    while (courant != NULL) {
        if (courant->id == id) {
            return 1;
        }
        courant = courant->suivant;
    }
    return 0;
}

Etudiant* tri(Etudiant* tete) {
    if (tete == NULL || tete->suivant == NULL) {
        return tete;
    }

    int swapped;
    Etudiant* ptr1;
    Etudiant* lptr = NULL;

    do {
        swapped = 0;
        ptr1 = tete;

        while (ptr1->suivant != lptr) {
            if (ptr1->moyenne > ptr1->suivant->moyenne) {
                float tempMoyenne = ptr1->moyenne;
                ptr1->moyenne = ptr1->suivant->moyenne;
                ptr1->suivant->moyenne = tempMoyenne;

                int tempId = ptr1->id;
                ptr1->id = ptr1->suivant->id;
                ptr1->suivant->id = tempId;

                char tempNom[50];
                strcpy(tempNom, ptr1->nom);
                strcpy(ptr1->nom, ptr1->suivant->nom);
                strcpy(ptr1->suivant->nom, tempNom);

                swapped = 1;
            }
            ptr1 = ptr1->suivant;
        }
        lptr = ptr1;
    } while (swapped);

    return tete;
}

Etudiant* modifier_moyenne(Etudiant* tete, int position, float nouvelle_moyenne) {
    if (tete == NULL || position < 0 || position >= longueur(tete)) {
        printf("Position invalide.\n");
        return tete;
    }

    Etudiant* courant = tete;
    for (int i = 0; i < position; i++) {
        courant = courant->suivant;
    }
    courant->moyenne = nouvelle_moyenne;
    return tete;
}

int main() {
    Etudiant* tete = NULL;
    int choix, position, id;
    float nouvelle_moyenne;

    do {
        printf("\nMenu:\n");
        printf("1. Creer un etudiant\n");
        printf("2. Afficher la liste\n");
        printf("3. Afficher la liste en inverse\n");
        printf("4. Ajouter un etudiant a une position\n");
        printf("5. Supprimer un etudiant a une position\n");
        printf("6. Rechercher un etudiant par ID\n");
        printf("7. Trier la liste par moyenne\n");
        printf("8. Modifier la moyenne d'un etudiant\n");
        printf("9. Quitter\n");
        printf("Choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1: {
                Etudiant* nouveau = creer_etudiant();
                tete = ajouter_position(tete, nouveau, 0);
                break;
            }
            case 2:
                afficher_liste(tete);
                break;
            case 3:
                afficher_liste_inverse(derniere_cellule(tete));
                break;
            case 4: {
                Etudiant* nouveau = creer_etudiant();
                printf("Entrez la position: ");
                scanf("%d", &position);
                tete = ajouter_position(tete, nouveau, position);
                break;
            }
            case 5:
                printf("Entrez la position: ");
                scanf("%d", &position);
                tete = supprimer_position(tete, position);
                break;
            case 6:
                printf("Entrez l'ID: ");
                scanf("%d", &id);
                if (chercher_etudiant(tete, id)) {
                    printf("Etudiant trouve.\n");
                } else {
                    printf("Etudiant non trouve.\n");
                }
                break;
            case 7:
                tete = tri(tete);
                break;
            case 8:
                printf("Entrez la position: ");
                scanf("%d", &position);
                printf("Entrez la nouvelle moyenne: ");
                scanf("%f", &nouvelle_moyenne);
                tete = modifier_moyenne(tete, position, nouvelle_moyenne);
                break;
            case 9:
                printf("Au revoir!\n");
                break;
            default:
                printf("Choix invalide.\n");
        }
    } while (choix != 9);

    while (tete != NULL) {
        Etudiant* temp = tete;
        tete = tete->suivant;
        free(temp);
    }

    return 0;
}
