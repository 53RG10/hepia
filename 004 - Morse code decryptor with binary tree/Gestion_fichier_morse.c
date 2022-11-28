#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main() {

/*------------------------------------------------------------------------*/

// Gestion des fichiers

    const int maxChar = 5;
    char str[maxChar];


    const char nomFichier[] = "code-morse.txt";
    FILE *file;
    file = fopen(nomFichier, "r"); // ouverture du fichier


    //const int tailleFichier = fileSize(fichier);
    //printf("Taille du fichier: %d mots\n", tailleFichier);

    int * tab;
    int tailleTab = 52;
    tab = malloc(tailleTab * sizeof(int));
    for (int i=0; i<tailleTab; i++){
        fscanf(file, "%s", str);
        tab[i] = (int)str;
        printf("[ %s ]\n", tab[i]);
        for (int j=0; j<maxChar; j++) {
            if (i % 2 == 1 && (str[j] == '.' || str[j] == '-'))
            printf("\t %c \n", str[j]);

        }
    }


    //printf("\n\n/------------------/\n\n");

    //tailleTableau = clean(fichier, tab, tailleFichier);

    //printf("Nouvelle taille du tableau: %d mots\n", tailleTableau);

/*------------------------------------------------------------------------*/
}
