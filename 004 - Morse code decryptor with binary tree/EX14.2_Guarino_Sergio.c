/*

Algorithmique et programmation

Série 14 - Mise en place d'une structure d'arbre binaire
Exercice 2

Sergio Guarino
1ère année ITI du soir

10/06/2019


*/


#include<stdio.h>
#include<stdlib.h>
//#include<string.h>

// Structure d'un noeud d'arbre
typedef struct node {
    int lettre;
    int morse[4];
    int level;
    struct node *right;
    struct node *left;
} node;

// Fonction d'initialisation d'un noeud
void init(node * n)  {
	n->lettre = 0;
	n->morse[0] = 0;
	n->level = 0;
	n->left = NULL;
	n->right = NULL;
}

// Fonction qui transforme un fichier en tableu
// Attention! On suppose que la taille du fichier (et donc du tableau) soit connue
void fileToTab (char nomFichier[50], int * tab) {

    FILE *file;
    file = fopen(nomFichier, "r");

    int i = 0;
    while (!feof(file)) {
        tab[i] = getc(file);
        i++;
    }

    fclose(file);
}

// Fonction d'affichage de l'arbre
void afficher(node ** n) {

    if ((*n)->right == NULL && (*n)->left == NULL && (*n)->lettre != 0) {
        printf("Lettre: %c \n", (*n)->lettre);
        printf("Niveau: %d\n\n", (*n)->level);

    } else if ((*n)->left != NULL ){
        printf("Lettre: %c \n", (*n)->lettre);
        printf("Niveau: %d\n\n", (*n)->level);

        afficher(&(*n)->left);
        printf("Lettre: %c \n", (*n)->lettre);
        printf("Niveau: %d\n\n", (*n)->level);

        if ((*n)->right != NULL)
            afficher(&(*n)->right);

    } else if ((*n)->left == NULL && (*n)->right != NULL){
            printf("Lettre: %c \n", (*n)->lettre);
            printf("Niveau: %d\n\n", (*n)->level);
            afficher(&(*n)->right);
    }
}

void copyNode (node ** N1, node ** N2){
    //(*N1)->lettre = (*N2)->lettre;
    //for (int i=0; i<4; i++) {
        //(*N1)->morse[i] = (*N2)->morse[i];
    //}
    (*N1)->level = (*N2)->level;
    printf("level: %d", (*N2)->level);
}

// Fonction pour placer un élément dans l'arbre
void checkNode (node ** n, node ** newNode, int m, int i) {

    node * Node2 = malloc(sizeof(node));
    init(Node2);

    int s = i;
    int mm =0;
    mm = (*newNode)->morse[s+1];
    s++;

    if (mm == '-' || mm == '.') {

        if ((*n)->left == NULL && mm == '-') {
            (*n)->left = Node2;
        } else if ((*n)->right == NULL && mm == '.') {
            (*n)->right = Node2;
        }

        if ((*n)->left != NULL && m == '-') {
            checkNode(&(*n)->left, &(*newNode), mm, s);
        } else if ((*n)->right != NULL && m == '.') {
            checkNode(&(*n)->right, &(*newNode), mm, s);
        }

    } else {
        if (m == '-') {
            printf("Test -");/*
            //copyNode(&(*n)->left, &(*newNode));
            (*n)->left->lettre = (*newNode)->lettre;
            (*n)->left->level = (*newNode)->level;
            for (int u=0; u<4; u++){
                (*n)->left->morse[u] = (*newNode)->morse[u];
            }*/
        } else if (m == '.') {
            printf("Test .");
            //(*n)->right->lettre = (*newNode)->lettre;
            (*n)->right->level = (*newNode)->level;
            //for (int u=0; u<4; u++){
                //(*n)->right->morse[u] = (*newNode)->morse[u];
            //}
            //copyNode(&(*n)->right, &(*newNode));
        }
    }

}

// Fonction pour placer un noeud dans un arbre binaire
void placeNode (node ** n, node ** newNode) {
    int m = (*newNode)->morse[0];
    checkNode(&(*n), &(*newNode), m, 0);
}

// Fonction de création de l'arbre binaire du code morse
void makeTree (node ** n, int * tab, int tabSize) {

    int j=0, c, m;

    node * newNode = malloc(sizeof(node));
    init(newNode);

    for (int i = 0; i<tabSize; i++) {
        c = tab[i];
        if (c >= 'A' && c <= 'Z') {
            newNode->lettre = c;
        } else if (c == '.' || c == '-') {
            newNode->morse[j] = c;
            j++;
        } else if (c == 10) {
            newNode->level = j;
            while (j<4) {
                newNode->morse[j] = 0;
                j++;
            }
            j = 0;
            placeNode(&(*n), &newNode);
        } else {
            continue;
        }
    }
}



int main () {


   	node * noeud = NULL;
	noeud = malloc(sizeof(node));
	init(noeud);

/*------------------------------------------------------------------------*/

// Gestion des fichiers et création des tableaux

    int tailleTab = 161;
    int tailleTab2 = 3009;
    int * tab, *tab2;
    tab = malloc(tailleTab * sizeof(int));
    tab2 = malloc(tailleTab2 * sizeof(int));

    fileToTab("code-morse.txt", tab);
    fileToTab("texte-morse.txt", tab2);

/*------------------------------------------------------------------------*/

    makeTree(&noeud, tab, tailleTab);

    afficher(&noeud);

	free(noeud);
	return 0;
}
