#include <stdio.h>   // Inclusion de la bibliothèque standard d'entrée/sortie
#include <stdlib.h>  // Inclusion de la bibliothèque standard pour la gestion de la mémoire

// Définition de la structure d'un nœud
struct Node {
    int data;            // Champ de données du nœud
    struct Node* next;   // Pointeur vers le nœud suivant
};

// Fonction pour ajouter un nœud au début de la liste
void push(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node)); // Allocation dynamique de mémoire pour un nouveau nœud
    new_node->data = new_data;  // Initialisation du champ de données du nouveau nœud
    new_node->next = *head_ref; // Le nouveau nœud pointe vers l'ancien premier nœud
    *head_ref = new_node;       // Mise à jour du pointeur de tête pour qu'il pointe vers le nouveau nœud
}

// Fonction pour afficher la liste
void printList(struct Node* node) {
    while (node != NULL) {         // Parcours de la liste jusqu'à la fin
        printf("%d , ", node->data); // Affichage des données du nœud actuel
        node = node->next;         // Passage au nœud suivant
    }
    printf("Comptabilité\n");              // Affichage de la fin de la liste
}

int main() {
    struct Node* head = NULL; // Initialisation de la liste vide

    // Ajout de nœds
    push(&head, 1);  // Ajoute 1 au début de la liste
    push(&head, 2);
    push(&head, 3);
    push(&head, 4);

    // Affichage de la liste
    printList(head); // Affiche la liste: 3 -> 2 -> 1 -> NULL

    return 0;
}
