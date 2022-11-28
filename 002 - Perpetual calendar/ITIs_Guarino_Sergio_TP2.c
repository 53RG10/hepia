/*

Algorithmique et programmation

Série 7 - Le Calendrier

Sergio Guarino
1ère année ITI du soir

15/01/2019

*/

#include <stdio.h>

// Fonction de calcul de l'année bissextile
int isLeap(int year) {
    if ((year%4 == 0 && year%100 != 0) || year%400 == 0)
        return 1;

    else
        return 0;
}

// Fonction pour connaitre le nombre de jours entre une année donnée et le 1er Janvier 1900
int daysToYear(int year) {
    int days = 0;
    for (int i=year; i>1900; i--){
        days += 365;
        days += isLeap(i);
    }
    return days;
}

// Fonction qui retourne le nombre de jours d'un mois d'une année
int daysInMonth(int year, int month) {
    switch(month) {
        case 2:
            if (isLeap(year))
                return 29;
            else
                return 28;

        case 4:
        case 6:
        case 9:
        case 11:
            return 30;

        default:
            return 31;
    }
}

// Fonction qui calcule le nombre de jours découlés depuis le 1er Janvier d'une année donnée
int daysFromJan(int year, int month) {
    int days = 0;
    for (int i=month-1; i > 0; i--) {
        days += daysInMonth(year, i);
    }

    if (month>1)
        days += isLeap(year);

    return days;
}

// Fonction qui retourne le jour de la semaine
int firstDay(int days) {
    switch(days%7 + 1) {
        case 1:
            return printf("Lundi");
        case 2:
            return printf("Mardi");
        case 3:
            return printf("Mercredi");
        case 4:
            return printf("Jeudi");
        case 5:
            return printf("Vendredi");
        case 6:
            return printf("Samedi");
        case 7:
            return printf("Dimanche");
        default:
            return 0;
    }
}

// Script d'initialisation du calendrier
int initCalendar(int year, int month, int calendar[6][7]) {
	for (int i=0; i<6; i++) {
		for (int j=0; j<7; j++) {
            calendar[i][j] = 0;
		}
    }
}

// Fonction d'affichage du calendrier
int showCalendar(int year, int month, int days, int calendar[6][7]) {
    printf("\n\n L   M   M   J   V   S   D \n");  // d'abord on affiche la ligne avec les jours de la semaine
    int k;
    int i=0;

    for (int m = days%7; m>0; m--){
        if (i == 0)                             // si le premier jour du mois n'est pas un lundi,
            printf("    ");                     // on affiche des espaces
    }

    for (int j=days%7, k=1; j<7 && k<=daysInMonth(year, month); j++, k++) {
        if (k<10)                               // on ajoute un espace si le jour est plus petit que 10,
            printf(" ");                        // pour améliorer l'affichage
        printf("%d  ", calendar[i][j]+k);       // on affiche le jour du mois, suivi d'un espace
        if (j == 6) {                           // au but de la colonne...
            i++;                                // ...on passe à la ligne suivante...
            j=-1;                               // ...et à la première colonne
                                                // (c'est -1 à la place que 0, car la boucle for va incrementer j)
            putchar('\n');
        }
    }
}

int main() {
    int an = 1900, mois = 1, jours = 0;         // initialisation des variables
    int calendar[6][7];                         // et du tableau pour afficher le calendrier

    printf("Bonjour! Ce programme affichera un calendrier pour une date donnée.\n");
    printf("Choisir une année (après 1900): "); // on demande de choisir une année...
    scanf("%d", &an);

    printf("\nChoisir un mois (1 - 12): ");     // ...et un mois
    scanf("%d", &mois);

    jours = daysToYear(an) + daysFromJan(an, mois); // calcul du nombre des jours découlés depuis le 1er Janvier 1900
    printf("\nDans ce mois il y a %d jours", daysInMonth(an, mois));

    printf("\nLe premier jour du mois c'est: ");
    firstDay(jours);

    printf("\nLe premier jour de l'année c'est: ");
    firstDay(daysToYear(an));

    initCalendar(an, mois, calendar);           // on initialise le calendrier...
    showCalendar(an, mois, jours, calendar);    // ...et on l'affiche

    return 0;
}
