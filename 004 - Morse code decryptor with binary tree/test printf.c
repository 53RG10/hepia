#include<stdio.h>
#include<stdlib.h>

void afficher(int i) {
    printf("Valeur de i: %d\n", i);
}

int main() {
    afficher(0);
    afficher(1);
    afficher(2);
    int k = 0;
    afficher(k);
    return 0;
}
