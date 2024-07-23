#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINE_LENGTH 1024
#define MAX_SUBSCRIBERS 10000
#define NUM_MONTHS 12
#define CONSUMPTION_THRESHOLD 1000  // Exemple de seuil pour le filtrage

typedef struct {
    int id;
    int consumption[NUM_MONTHS];
    int total_annuel;
    int mois_max;
} Subscriber;

void process_data(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Cannot open file");
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];
    int subscriber_count = 0;
    Subscriber subscribers[MAX_SUBSCRIBERS];
    int total_consumption[NUM_MONTHS] = {0};  // Pour le calcul des moyennes mensuelles
    int total_annual_consumption = 0;
    int max_consumption = 0;
    int max_consumer_id = -1;

    // Skip the header line
    fgets(line, MAX_LINE_LENGTH, file);

    while (fgets(line, MAX_LINE_LENGTH, file) && subscriber_count < MAX_SUBSCRIBERS) {
        char *token = strtok(line, ",");
        subscribers[subscriber_count].id = atoi(token);

        subscribers[subscriber_count].total_annuel = 0;
        subscribers[subscriber_count].mois_max = 0;

        for (int i = 0; i < NUM_MONTHS; i++) {
            token = strtok(NULL, ",");
            subscribers[subscriber_count].consumption[i] = atoi(token);
            subscribers[subscriber_count].total_annuel += subscribers[subscriber_count].consumption[i];
            total_consumption[i] += subscribers[subscriber_count].consumption[i];

            if (subscribers[subscriber_count].consumption[i] > subscribers[subscriber_count].consumption[subscribers[subscriber_count].mois_max]) {
                subscribers[subscriber_count].mois_max = i;
            }
        }

        if (subscribers[subscriber_count].total_annuel > max_consumption) {
            max_consumption = subscribers[subscriber_count].total_annuel;
            max_consumer_id = subscribers[subscriber_count].id;
        }

        total_annual_consumption += subscribers[subscriber_count].total_annuel;
        subscriber_count++;
    }

    fclose(file);

    // Calcul des moyennes mensuelles
    double average_consumption[NUM_MONTHS];
    for (int i = 0; i < NUM_MONTHS; i++) {
        average_consumption[i] = (double)total_consumption[i] / subscriber_count;
    }

    // Print results
    printf("Consommation totale annuelle pour chaque abonné (filtré par seuil de %d):\n", CONSUMPTION_THRESHOLD);
    for (int i = 0; i < subscriber_count; i++) {
        if (subscribers[i].total_annuel > CONSUMPTION_THRESHOLD) {
            printf("Abonné %d: Total Annuel = %d, Mois Max = %d\n",
                   subscribers[i].id,
                   subscribers[i].total_annuel,
                   subscribers[i].mois_max + 1);
        }
    }

    printf("\nMoyenne mensuelle de consommation:\n");
    for (int i = 0; i < NUM_MONTHS; i++) {
        printf("Mois %d: %.2f\n", i + 1, average_consumption[i]);
    }

    printf("\nAbonné ayant le plus consommé sur l'année: Abonné %d avec %d KWh]\n", max_consumer_id, max_consumption);
}

int main() {
    const char *filename = "data.csv";
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    process_data(filename);
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Time taken: %f seconds\n", cpu_time_used);
    return 0;
}
