//
// Created by marya on 23/10/2023.
//

#include "list.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>



void change_maj_to_min( char *s) {
   for (int i = 0; s[i] != '\0'; i++) {
       if (s[i] >= 'A' && s[i] <= 'Z') {
        s[i] = s[i] + 32; // Conversion en minuscule
        }

    }
}



int comparerString1( char *s1, char *s2) {
    int i = 0;
    int n1 = strlen(s1);
    int n2 = strlen(s2);

    while (i < n1 && i < n2 && s1[i] == s2[i]) {     // Compare characters until a mismatch is found or the end of either string is reached
        i++;
    }

    if (i < n1 && i < n2) {
        if (s1[i] < s2[i]) {
            return 1; //S1 < S2
        } else {
            return - 1; // S1> S2;
        }
    } else {
        if (n1 == n2) {
            return 0; // s1=S2
        } else if (i >= n1) {
            return 1; //s1<S2
        } else {
            return -1; // s1>S2
        }
    }
}




void transformerNom(char *res) {
    char nomComplet[256];  // Déclaration d'un tableau pour stocker le nom complet

    printf("Veuillez entrer le nom complet : ");
    gets(nomComplet);  // Utilise la fonction gets pour saisir le nom complet.

    char *espace = NULL; // Pointeur pour l'emplacement de l'espace.

    // Parcourt la chaîne jusqu'à trouver un espace ou la fin de la chaîne.
    for (int i = 0; nomComplet[i] != '\0'; i++) {
        if (nomComplet[i] == ' ') {
            espace = &nomComplet[i];
            break; // Sort de la boucle dès qu'un espace est trouvé.
        }
    }

    // Si un espace est trouvé, divise le nom complet en prénom et nom.
    if (espace != NULL) {
        *espace = '\0'; // Remplace l'espace par un caractère nul pour séparer le prénom et le nom.

        // Copie le nom de famille dans le tableau res.
        strcpy(res, espace + 1);

        // Ajoute un tiret bas pour séparer le nom de famille du prénom.
        strcat(res, "_");

        // Copie le prénom dans le tableau res.
        strcat(res, nomComplet);
    } else {
        // Si aucun espace n'est trouvé, copie simplement le nom complet dans res.
        strcpy(res, nomComplet);
    }
    change_maj_to_min(res);
}

