/*

Algorithmique et programmation

Série 8 - Transformation d'images

Sergio Guarino
1ère année ITI du soir

04/03/2019

*/

#include "lesEs.c"
#include <math.h>

//symetrie verticale
void symetrie_v(int nbLi, int nbCol, int image[nbLi][nbCol], int imageTransf[nbLi][nbCol]) {
    int i, j;

	for (i=0; i<nbLi; i++)
	   for (j=0; j<nbCol; j++)
		   imageTransf[i][j] = image[nbLi-i-1][j];
}

// symetrie horizontale
void symetrie_h(int nbLi, int nbCol, int image[nbLi][nbCol], int imageTransf[nbLi][nbCol]) {
    int i, j;

	for (i=0; i<nbLi; i++)
	   for (j=0; j<nbCol; j++)
		   imageTransf[i][j] = image[i][nbCol-j-1];
}
//fonction de zoom 2x
void zoom2(int nbLi, int nbCol, int image[nbLi][nbCol], int imageTransf[nbLi*2][nbCol*2]){
    int i, j;

    for (i=0; i<nbLi; i++)
        for (j=0; j<nbCol; j++) {
                imageTransf [i*2]    [j*2]    = image[i][j]; //on multiplie par 2 chaque case du tableau imageTransf...
                imageTransf [i*2]    [j*2+1]  = image[i][j]; //...en on copie ces valeurs dans les cases adjacentes.
                imageTransf [i*2+1]  [j*2]    = image[i][j];
                imageTransf [i*2+1]  [j*2+1]  = image[i][j];
        }
}

//fonction pour effet photomaton
void photomaton(int nbLi, int nbCol, int image[nbLi][nbCol], int imageTransf[nbLi][nbCol]){
    int i, j;

    for (i=0; i<nbLi; i++)
        for (j=0; j<nbCol; j++) {

            if (i%2 == 0 && j%2 == 0)
                imageTransf    [(nbLi + i) / 2]   [(nbCol + j) / 2]    = image[i][j];

            else if (i%2 == 1 && j%2 == 0)
                imageTransf    [(nbLi + i) / 2]   [j/2]                = image[i][j];

            else if (i%2 == 0 && j%2 == 1)
                imageTransf    [i/2]              [(nbCol + j) / 2]    = image[i][j];

            else if (i%2 == 1 && j%2 == 1)
                imageTransf    [i/2]              [j/2]                = image[i][j];
    }
}

//initialisation de l'image pour éviter d'afficher la fonction précédente.
void reset(int nbLi, int nbCol, int image[nbLi][nbCol]){
    int i,j;
   for (i=0; i<nbLi; i++)
        for (j=0; j<nbCol; j++)
            image[i][j] = 0;
}
// fonction de rotation de l'image.
void rotation(int nbLi, int nbCol, double angle, int image[nbLi][nbCol], int imageTransf[nbLi][nbCol]) {
    int i, j, m, n, h, l;
    float cosa, sina;

    cosa = cos(angle);
    sina = sin(angle);

    l = nbCol/2;
    h = nbLi/2;

    for (i=0; i<nbLi; i++)
        for (j=0; j<nbCol; j++) {
            m = (int) ( ( (i-h)*cosa - (j-l)*sina) + h); //on fait la rotation de l'image à partir du centre
            n = (int) ( ( (j-l)*cosa + (i-h)*sina) + l);

            if ( m < nbLi && m >= 0 && n < nbCol && n > 0 ) //on s'assure de ne pas sortir des bords
                imageTransf[m][n] = image[i][j];
            else
                continue;
        }
}

int main(void) {
    const int MAXCHAR = 200;  // nbre maximal de car. pour une ligne

    char  genre  [MAXCHAR];   // Informations pour l'entête d'une image au format pgm
    char  comment[MAXCHAR];   // commentaire en pgm
    char  dimX   [MAXCHAR];   // nbre de colonnes
    char  dimY   [MAXCHAR];   // nbre de lignes
    char  nbGris [MAXCHAR];   // nbre de niveaux de gris
    char  dimX2  [MAXCHAR];
    char  dimY2  [MAXCHAR];

    LireEntetePgm("lenna.pgm", genre, comment, dimX, dimY, nbGris, MAXCHAR);

    const int intNbGris = atoi(nbGris);
    const int intDimX   = atoi(dimX);
    const int intDimY   = atoi(dimY);
    const int intDimX2  = intDimX*2;
    const int intDimY2  = intDimY*2;

    int   image [intDimY][intDimX];   // déclaration de l'image originale à mémoriser
    int   image2[intDimY][intDimX];  // déclaration de l'image qui est le résultat d'une transf.
    int   image3[intDimY2][intDimX2];

    double angle = 298 * M_PI / 180; //saisie de l'angle de rotation de l'image.

    LireImagePgm("lenna.pgm", intDimX, intDimY, image, MAXCHAR);

    transfImage(intDimY, intDimX, intNbGris, image, image2);
    EcrireImagePgm("lenna2.pgm", genre, comment, dimX, dimY, nbGris, image2);

    symetrie_v(intDimY, intDimX, image, image2);
    EcrireImagePgm("lenna3.pgm", genre, comment, dimX, dimY, nbGris, image2);

    symetrie_h(intDimY, intDimX, image, image2);
    EcrireImagePgm("lenna4.pgm", genre, comment, dimX, dimY, nbGris, image2);

    zoom2(intDimY, intDimX, image, image3);
    sprintf(dimX2, "%d", intDimX2);
    sprintf(dimY2, "%d", intDimY2);
    EcrireImagePgm("lenna5.pgm", genre, comment, dimX2, dimY2, nbGris, image3);

    photomaton(intDimY, intDimX, image, image2);
    EcrireImagePgm("lenna6.pgm", genre, comment, dimX, dimY, nbGris, image2);

    reset(intDimY, intDimX, image2);
    rotation(intDimY, intDimX, angle, image, image2);
    EcrireImagePgm("lenna7.pgm", genre, comment, dimX, dimY, nbGris, image2);

    return 0;
}
