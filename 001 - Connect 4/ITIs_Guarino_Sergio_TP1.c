/*

Algorithmique et programmation

Série 6 - Le jeu "Puissance 4"

Sergio Guarino
1ère année ITI du soir

14/12/2018

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const char symbole = '-'; //symbole affiché pour remplir les cases vides du tableau

// Fonction pour obtenir la colonne du joueur
int getCol(){
	char col;
	while(1){
		col = getchar();//le joueur rentre sa colonne (chiffre entre 1 et 6)
		if(col>='1'&&col<='7') {
			break;
		}
	}
	return col-'1';
}

// Fonction pour obtenir une valeur de 1 à 3 rentrée au clavier
int getInput(){
	char input;
	while(1){
		input = getchar();//le joueur rentre la modalité de jeu
		if(input>='1'&&input<='3'){
			break;
		}
	}
	return input;
}

// Fonction pour afficher le tableau
int show(int X, int Y, char array[X][Y]) {
	for (int i=0; i<X; i++) {
		for (int j=0; j<Y; j++) {
			putchar(' ');
			putchar(array[i][j]);
		}
		putchar('\n');
	}
	// boucle pour afficher la liste des colonnes à la fin du tableau
	for (int i=0; i<Y; i++) {
		putchar(' ');
		printf("%d", i+1);
	}

	putchar('\n');
	return 0;
}

// Fonction pour initialiser le tableau pour afficher le caractère de la variable symbole
int init(int X, int Y, char array[X][Y]) {
	for (int i=0; i<X; i++) {
		for (int j=0; j<Y; j++) {
			array[i][j] = symbole;
		}
	}
	return 0;
}

// Fonction pour returner la première ligne libre pour positionner la case
int checkRow (int X, int Y, char array[X][Y], int col) {
	for (int i=0; i<X; i++) {
		if (array[X-1-i][col] == symbole) {
			return (i+1);
		}
	}
	return 0;
}

// Fonction pour vérifier si la colonne est pleine
int fullCol (int X, int Y, char array[X][Y], int col) {
	if (array[X-6][col] != symbole) {
		return 1;
	} else
		return 0;
}

// Fonction pour écrire dans le tableau la case choisie par le joueur ou l'ordi
int write (int X, int Y, char array[X][Y], int col, char symbol) {
	int ligne_libre;
	ligne_libre = checkRow(X,Y,array,col);
	array[X-ligne_libre][col] = symbol; //la colonne sélectionnée prends la valeur du symbole en input
	return 0;
}

// Fonction pour remplacer dans le tableau la case de la colonne choisie (utilisé par l'AI)
int substitute (int X, int Y, char array[X][Y], int col, char symbol) {
	int ligne_libre;
	ligne_libre = checkRow(X,Y,array,col);
	array[X-ligne_libre+1][col] = symbol; //la colonne sélectionnée prends la valeur du symbole en input
	return 0;
}

// Vérifie si dans le tableu il y a un gagnant
int checkWinner(int X, int Y, char array[X][Y]){
    for (int i=0; i<X; i++) {
        for (int j=0; j<Y; j++) {
            if (array[i][j] != symbole) {
                if (array[i][j] == array[i+1][j] &&  //contrôle verticalement vers le bas
                    array[i][j] == array[i+2][j] &&
                    array[i][j] == array[i+3][j] )
                    {
                    return 1;
                }

                    else if (array[i][j] == array[i][j-1] && // check horizontal vers la gauche
                            array[i][j] == array[i][j-2] &&
                            array[i][j] == array[i][j-3] )
                    {
                    return 1;
                }

                    else if ( i>2 && j>2 && //check diagonal \ (from top left to bottom right)
                            array[i][j] == array[i-1][j-1] &&
                            array[i][j] == array[i-2][j-2] &&
                            array[i][j] == array[i-3][j-3] )
                    {
                    return 1;
                }

                    else if ( i>2 && j<4 && //check diagonal / (from bottom left to top right)
                            array[i][j] == array[i-1][j+1] &&
                            array[i][j] == array[i-2][j+2] &&
                            array[i][j] == array[i-3][j+3] )
                    {
                    return 1;
                }
            }
        }
    }
  return 0; //s'il n'y a pas de gagnants returner 0.
}

// Fonction à executer après que le joueur a joué. S'il a gagné, le jeu se termine
int playerWins(int X, int Y, char array[X][Y]){
	if (checkWinner(X, Y, array) == 1) { //vérifie si le joueur a gagné
		show(X, Y, array);
		printf("Félicitations! Vous avez gagné!\n\n");
		exit(0); //arrête le programme
	} else
		return 0;
}

// Fonction à executer après que l'ordinateur a joué. S'il a gagné, le jeu se termine
int AIWins(int X, int Y, char array[X][Y]){
	if (checkWinner(X, Y, array) == 1) { //vérifie si l'ordinateur a gagné
		show(X, Y, array);
        printf("Game Over! Vous avez perdu :(\n\n");
        exit(0); //arrête le programme
    } else
	    return 0;
}

// Fonction pour rentrer dans le tableau la case choisie par le joueur
int player(int X, int Y, char array[X][Y], char symbol) {
    //le programme demande à l'utilisateur de choisir une colonne
    int col;
    printf("Choisir la colonne: ");
    col=getCol();
    while (fullCol(X,Y,array,col)) {
        printf("Colonne pleine! Merci d'en choisir une autre: ");
        col=getCol();
    }
    write(X,Y,array,col,symbol);
    return 0;
}

// Fonction pour rentrer dans le tableau la case choisie par l'ordinateur au hasard
int randomAI(int X, int Y, char array[X][Y]) {
    //colonne choisie aléatoirement par l'ordinateur
    int col;
    col = rand() % 7; // genère un nombre aléatoire entre '0' et '6'
    while (fullCol(X,Y,array,col)) {
        col = rand() % 7;
    }
    printf("\nL'ordinateur a choisi la colonne: %d\n", col+1);
    write(X,Y,array,col,'O');
    return 0;
}

// Fonction pour rentrer dans le tableau la case choisie par l'ordinateur "intelligent"
int AI(int X, int Y, char array[X][Y]) {
	int col;
	int write_test = 0;
	// on vérifie si le joueur peut gagner et on lui empèche de le faire
    for (int i=0; i<Y; i++) {
		col = i; // on pose col = i pour faciliter la lecture
		if (fullCol(X,Y,array,col)) { //si la colonne est pleine, passe au i suivant
			continue;
		}
		else {
			write(X,Y,array,col,'X'); // vérifie si le joueur peut gagner
			if (checkWinner(X, Y, array) == 1) { //si le joueur a gagné, l'ordinateur mets la case à la place du joueur
				substitute(X,Y,array,col,'O'); // l'ordinateur remplace la case testée avant
				printf("\nLe joueur pourrait gagner, donc l'ordinateur choisi la colonne: %d\n", col+1);
				write_test = 1; // cette variable sert à dire au programme que l'on a écrit quelque chose, donc il ne doit pas commencer la deuxième boucle
			} else {
				substitute(X,Y,array,col,symbole); //si le joueur ne pouvait pas gagner, le programme efface la case que l'ordinateur a choisi et continue
				continue;
			}
		}
	}

	// si le joueur ne va pas gagner au prochain coup, l'ordinateur va essayer de gagner
	if (write_test == 0) { // on s'assure que l'ordinateur n'aille pas déjà choisi une case
		for (int i=0; i<Y; i++) {
			col = i; // on pose col = i pour faciliter la lecture
			if (fullCol(X,Y,array,col)) { //si la colonne est pleine, passe au i suivant
				continue;
			}
			else {
				write(X,Y,array,col,'O'); // mets la case dans la colonne i
				if (checkWinner(X, Y, array) == 1) { //si l'ordinateur a gagné, le jeu termine
					printf("\nL'ordinateur peut gagner, donc il choisi la colonne: %d\n", col+1);
					AIWins(X, Y, array);
				}
				else {
					substitute(X,Y,array,col,symbole); //si l'ordinateur n'a pas gagné, il efface la case qu'il a choisi et continue
					continue;
				}
			}			
		}
	}

	if (write_test == 0) {
		randomAI(X, Y, array); // si le 2 boucles se terminent (donc si ni l'ordinateur ni le joueur peuvent gagner), envoyer une case au hasard.
    }
    return 0;
}

// Fonction pour faire jouer 2 joueur l'un contre l'autre.
int playerPlayer(int X, int Y, char array[X][Y]) {
    while (1) {
		printf("Joueur 1. ");
        player(X, Y, array, 'X');
		playerWins(X, Y, array);

		printf("Joueur 2. ");
        player(X, Y, array, 'O');
		playerWins(X, Y, array);

		show(X, Y, array);
    }
    return 0;
}

// Fonction pour jouer contre un ordinateur qui joue au hasard.
int playerRandomAI(int X, int Y, char array[X][Y]) {
    while (1) {
        player(X, Y, array, 'X');
		playerWins(X, Y, array);

        randomAI(X, Y, array);
		AIWins(X, Y, array);

		show(X, Y, array);
    }
    return 0;
}

// Fonction pour jouer contre un ordinateur "intelligent", qui essaie de gagner s'il peut ou empèche le joueur de gagner.
int playerAI(int X, int Y, char array[X][Y]) {
    while(1) {
		player(X, Y, array, 'X');
		playerWins(X, Y, array);

		AI(X, Y, array);
		AIWins(X, Y, array);

		show(X, Y, array);
    }
    return 0;
}

// Fonction de bienvenue. Ici on choisi quel version du jeu on veut jouer.
int chooseGame(int X, int Y, char array[X][Y]) {
    printf("\n\n\nBienvenue!"
	   "\n\nCeci est le jeu de Puissance 4!"
	   "\n\nL'ojectif est d'aligner 4 cases horizontalement, verticalement ou en diagonale."
	   "\n\nChoisir la modalité du jeu: "
	   "\nTaper 1 pour jouer contre une autre personne"
	   "\nTaper 2 pour jouer contre l'ordinateur (niveau simple)"
	   "\nTaper 3 pour jouer contre l'ordinateur (niveau plus élevé)"
	   "\nVotre choix: ");

    switch(getInput()) {
	case '1':
	    playerPlayer(X, Y, array);
	    break;
	case '2':
	    playerRandomAI(X, Y, array);
	    break;
	case '3':
	    playerAI(X, Y, array);
	    break;
    }
    return 0;
}

// Fonction main
void main(){
	//initialisation générateur nombres aléatoires
	srand((unsigned) time(0));

	const int M = 6;        //nombre de lignes
	const int N = 7;        //nombre de colonnes
	char tableau[M][N];     //création du tableau de taille MxN

	init(M, N, tableau);    //initialisation du tableau vide

	chooseGame(M, N, tableau); // message de bienvenue et demande au joueur de choisir la modalité de jeu.
}
