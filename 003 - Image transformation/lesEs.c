#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//////////////////////////////////////////////////////////////////////////////

// lit une ligne de caractères (maxchar caract.) depuis un fichier et la mémorise
// dans laLigne

void LireLigne(FILE* fid, const int maxchar, char laLigne[])

{  int i;

   for (i=0; i<maxchar; i++)
       laLigne[i] = '\0';

   i=0;
   while ( (laLigne[i] = fgetc(fid)) != '\n')
      i++;
}

//////////////////////////////////////////////////////////////////////////////

// lit le préambule d'un fichier au format pgm
// les variables sont retournées dans plusieurs tableaux de caractères
// Attention dimX, dimY et nbGris ne sont pas des entiers, mais des "Strings"

void LireEntetePgm(char nomFichier[], char genre[], char comment[], char dimX[], char dimY[], char nbGris[], const int maxchar)

{  FILE* fid;
   char uneLigne[maxchar];
   fid = fopen(nomFichier, "r");

   LireLigne(fid, maxchar, uneLigne);
   strcpy(genre, uneLigne);

   LireLigne(fid, maxchar, uneLigne);
   strcpy(comment, uneLigne);

   fscanf(fid, "%s", dimX);
   fscanf(fid, "%s", dimY);
   fscanf(fid, "%s", nbGris);

   fclose(fid);

}

//////////////////////////////////////////////////////////////////////////////

// Lit les niveaux de gris d'une image pgm et stockage dans image
// Attention: dimX et dimY sont de type int

void LireImagePgm(char nomFichier[], int dimX, int dimY, int image[dimX][dimY], const int maxchar)

{  FILE* fid;
   char uneLigne[maxchar];
   int   i;
   int   j;

   fid = fopen(nomFichier, "r");

   LireLigne(fid, maxchar, uneLigne);
   LireLigne(fid, maxchar, uneLigne);

   fscanf(fid, "%s", uneLigne);
   fscanf(fid, "%s", uneLigne);
   fscanf(fid, "%s", uneLigne);

   for (i=0; i<dimY; i++)
       for (j=0; j<dimX; j++)
	       fscanf(fid, "%d", &image[i][j]);

   fclose(fid);
}

//////////////////////////////////////////////////////////////////////////////

// Ecrit dans un fichier une image pgm
// D'abord le préambule d'un fichier au format pgm
// Puis les niveaux de gris de l'image
// Attention dimX, dimY et nbGris ne sont pas des entiers, mais des "Strings"

void EcrireImagePgm(char nomFichier[], char genre[], char comment[], char dimX[], char dimY[], char nbGris[], int image[atoi(dimX)][atoi(dimY)])

{  FILE* fid;
   int   i, j, nbLi, nbCol;

   nbLi  = atoi(dimY);          // nbre de lignes
   nbCol = atoi(dimX);          // nbre de colonnes

   fid = fopen(nomFichier, "w");

   fprintf(fid, "%s",   genre);
   fprintf(fid, "%s",   comment);
   fprintf(fid, "%s ",  dimX);
   fprintf(fid, "%s\n", dimY);
   fprintf(fid, "%s\n", nbGris);

   for (i=0; i<nbLi; i++)
   {
       for (j=0; j<nbCol; j++)
	       fprintf(fid, "%d ", image[i][j]);
	   fprintf(fid, "\n");
   }

   fclose(fid);
}

//////////////////////////////////////////////////////////////////////////////

// Transformation de l'image --> imageTransf

void transfImage(int nbLi, int nbCol, int nbGris, int image[nbLi][nbCol], int imageTransf[nbLi][nbCol])
{   int i, j;

	for (i=0; i<nbLi; i++)
	   for (j=0; j<nbCol; j++)
		   imageTransf[i][j] = nbGris - image[i][j];
}

//////////////////////////////////////////////////////////////////////////////

int main2(void) {
    return 0;
}
