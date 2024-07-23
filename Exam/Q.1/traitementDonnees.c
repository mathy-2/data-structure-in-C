#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Fonction de comparaison pour le tri
int comparaison(const void *a, const void *b) {
    return (*(double *)a - *(double *)b);
}

int main() {
    FILE *fichier = fopen("données.csv", "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    // Variables pour le traitement
    double somme = 0.0;
    int nombre_lignes = 0;
    double valeurs[1000]; // Ajustez la taille en fonction de vos données
    char ligne[100]; // Ajustez la taille en fonction de vos données

    // Mesure du temps avant le traitement
    clock_t debut = clock();

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        // Traitement spécifique (par exemple, calcul de la moyenne)
        double valeur = atof(ligne); // Convertir la chaîne en nombre
        somme += valeur;
        valeurs[nombre_lignes] = valeur;
        nombre_lignes++;
    }

    // Calcul de la moyenne
    double moyenne = somme / nombre_lignes;

    // Tri des valeurs
    qsort(valeurs, nombre_lignes, sizeof(double), comparaison);

    // Calcul de la médiane
    double mediane;
    if (nombre_lignes % 2 == 0) {
        mediane = (valeurs[nombre_lignes / 2 - 1] + valeurs[nombre_lignes / 2]) / 2.0;
    } else {
        mediane = valeurs[nombre_lignes / 2];
    }

    // Maximum et minimum
    double maximum = valeurs[nombre_lignes - 1];
    double minimum = valeurs[0];

    // Mesure du temps après le traitement
    clock_t fin = clock();
    double temps_execution = (double)(fin - debut) / CLOCKS_PER_SEC;

    printf("Moyenne : %.2f\n", moyenne);
    printf("Médiane : %.2f\n", mediane);
    printf("Maximum : %.2f\n", maximum);
    printf("Minimum : %.2f\n", minimum);
    printf("Temps d'exécution : %.4f secondes\n", temps_execution);

    fclose(fichier);
    return 0;
}
