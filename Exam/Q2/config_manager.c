#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

typedef struct {
    char db_host[256];
    int db_port;
    char db_user[256];
    char db_password[256];
} Config;

// Fonction pour lire la configuration à partir d'un fichier
void read_config(const char *filename, Config *config) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open configuration file");
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        char key[256];
        char value[256];
        sscanf(line, "%[^=]=%s", key, value);

        if (strcmp(key, "db_host") == 0) {
            strcpy(config->db_host, value);
        } else if (strcmp(key, "db_port") == 0) {
            config->db_port = atoi(value);
        } else if (strcmp(key, "db_user") == 0) {
            strcpy(config->db_user, value);
        } else if (strcmp(key, "db_password") == 0) {
            strcpy(config->db_password, value);
        }
    }

    fclose(file);
}

// Fonction pour écrire la configuration dans un fichier
void write_config(const char *filename, const Config *config) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Failed to open configuration file for writing");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "db_host=%s\n", config->db_host);
    fprintf(file, "db_port=%d\n", config->db_port);
    fprintf(file, "db_user=%s\n", config->db_user);
    fprintf(file, "db_password=%s\n", config->db_password);

    fclose(file);
}

// Fonction pour simuler la connexion à une base de données
void connect_to_database(const Config *config) {
    // Ici, nous simulons simplement la connexion à une base de données en affichant les paramètres.
    // Dans une application réelle, vous utiliseriez ces paramètres pour établir une connexion.
    printf("Connecting to database at %s:%d with user %s\n",
           config->db_host, config->db_port, config->db_user);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <config_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    Config config;
    read_config(argv[1], &config);
    connect_to_database(&config);

    // Exemple de mise à jour des paramètres de configuration
    strcpy(config.db_password, "new_password");
    write_config(argv[1], &config);

    printf("Configuration updated successfully.\n");

    return 0;
}
