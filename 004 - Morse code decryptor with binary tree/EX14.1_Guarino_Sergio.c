/*

Algorithmique et programmation

S�rie 14 - Mise en place d'une structure d'arbre binaire
Exercice 1

Sergio Guarino
1�re ann�e ITI du soir

10/06/2019


But du programme:
cr�ation d'un arbre binaire pour le tri d'un tableau de nombres.
Le tri s'effectue par un parcours sym�trique.
Chaque nombre est �valu� selon les conditions suivantes:
s'il est plus grand que la valeur du noeud actuel, il va � droite, sinon � gauche.

*/


#include<stdio.h>
#include<stdlib.h>


// Structure d'un noeud d'arbre
typedef struct node {
    int data;
    int level;
    struct node *right;
    struct node *left;
} node;

// Fonction d'initialisation d'un noeud
void init(node * n)  {
	n->data = -1;
	n->level = 0;
	n->left = NULL;
	n->right = NULL;
}

// Fonction de tri de l'arbre binaire.
// On passe les �l�ments du tableau et on le trie selon la logique suivante:
// si l'�l�ment est plus petit, il va � gauche, si plus grand, � droite du noeud o� l'on se trouve.
void trier(node ** n, int x) {

    // On mets le premier �l�ment au sommet de l'arbre.
    if ((*n)->right == NULL && (*n)->left == NULL && (*n)->data == -1) {
            (*n)->data = x;
            (*n)->level++;
    } else {

        //On v�rifie la valeur du nombre � ajouter. S'il est plus grand ou �gal...
        if (x >= (*n)->data){

            // On v�rifie que la branche de droite soit vide, on cr�e un nouveau noeud et on lui assigne le nombre pass� en argument.
            if ((*n)->right == NULL) {

                // Cr�ation du nouveau noeud et initialisation
                node * newNode = malloc(sizeof(node));
                init(newNode);

                // Comme il s'agit d'un nouveau noeud, il va avoir un niveau en plus que sa racine.
                newNode->level = (*n)->level + 1;

                // On met ce nouveau noued sur la branche de droite du noeud actuel et on lui assigne la valeur pass�e en argument
                (*n)->right = newNode;
                newNode->data = x;

            // Si la branche de droite n'est pas vide, on rentre dans cette branche et on v�rifie tout � nouveau.
            } else
                trier(&(*n)->right, x);

        // Et si le nombre � ajouter est plus petit que celui qui est actuellement dans le noeud...
        } else if (x < (*n)->data) {

            // ...on regarde la branche de gauche et si elle est vide, on cr�e un nouveau noeud et on lui assigne le nombre pass� en argument.
            if ((*n)->left == NULL) {

                // Cr�ation du nouveau noeud et initialisation
                node * newNode = malloc(sizeof(node));
                init(newNode);

                // Comme il s'agit d'un nouveau noeud, il va avoir un niveau en plus que sa racine.
                newNode->level += (*n)->level + 1;

                // On met ce nouveau noued sur la branche de gauche du noeud actuel et on lui assigna la valeur pass�e en argument
                (*n)->left = newNode;
                newNode->data = x;

            // Si la branche de gauche n'est pas vide, on rentre dans cette branche et on v�rifie tout � nouveau.
            } else
                trier(&(*n)->left, x);
        }
    }
}

// Fonction d'affichage de l'arbre
void afficher(node ** n) {

    // Si c'est le dernier noeud d'une branche, on l'affiche
    if ((*n)->right == NULL && (*n)->left == NULL) {

        printf("[ %d ] \t ", (*n)->data);
        printf("Niveau: %d\n\n", (*n)->level);

    // Sinon on regarde d'abord � gauche, et si ce n'est pas vide, on appelle � nouveau la fonction.
    } else if ((*n)->left != NULL){

        afficher(&(*n)->left);

        // Apr�s avoir affiche ce qui est � gauche, on affiche le contenu du noeud actuel.
        printf("[ %d ] \t ", (*n)->data);
        printf("Niveau: %d\n\n", (*n)->level);

        // apr�s avoir affich� le nombre qui est � gauche, on v�rifie s'il y a un �l�ment � sa droite et on l'affiche.
        if ((*n)->right != NULL)
            afficher(&(*n)->right);

    // si la branche de gauche est vide et que celle de droite ne l'est pas...
    } else if ((*n)->left == NULL && (*n)->right != NULL){

            // ...on affiche la valeur actuelle et puis celle qui est � droite.
            printf("[ %d ] \t ", (*n)->data);
            printf("Niveau: %d\n\n", (*n)->level);

            afficher(&(*n)->right);

    }
}

int main() {

	int tab[10] = {17, 19, 20, 15, 25, 5, 18, -7, -4, 22};

	node * noeud = malloc(sizeof(node));
	init(noeud);

	for (int i=0; i<10; i++) {
		trier(&noeud, tab[i]);
	}

	afficher(&noeud);

	free(noeud);

	return 0;
}
