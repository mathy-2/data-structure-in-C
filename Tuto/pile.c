#include <stdio.h>   // Inclusion de la bibliothèque standard d'entrée/sortie
#include <stdlib.h>  // Inclusion de la bibliothèque standard pour la gestion de la mémoire

// Définition de la structure d'un nœud de pile
struct StackNode {
    int data;             
    struct StackNode* next; 
};

// Fonction pour créer un nouveau nœud de pile
struct StackNode* newNode(int data) {
    struct StackNode* stackNode = (struct StackNode*)malloc(sizeof(struct StackNode)); 
    stackNode->data = data; 
    stackNode->next = NULL; 
    return stackNode;       // Retourne le pointeur vers le nouveau nœud
}

// Fonction pour vérifier si la pile est vide
int isEmpty(struct StackNode* root) {
    return !root; 
}

// Fonction pour ajouter un élément à la pile
void push(struct StackNode** root, int data) {
    struct StackNode* stackNode = newNode(data); 
    stackNode->next = *root; 
    *root = stackNode;      
    printf("%d pushed to stack\n", data);
}

// Fonction pour retirer un élément de la pile
int pop(struct StackNode** root) {
    if (isEmpty(*root))      
        return -1;           
    struct StackNode* temp = *root; 
    *root = (*root)->next;   
    int popped = temp->data;  
    free(temp);               

    return popped;
}

// Fonction pour afficher le sommet de la pile
int peek(struct StackNode* root) {
    if (isEmpty(root))
        return -1;            
    return root->data;        
}

int main() {
    struct StackNode* root = NULL; // Initialisation de la pile vide

    // Opérations sur la pile
    push(&root, 10); // Ajoute 10 à la pile
    push(&root, 20);
    push(&root, 30);
    

    printf("%d popped from stack\n", pop(&root)); // Retire et affiche l'élément du sommet de la pile
    printf("Top element is %d\n", peek(root));    // Affiche l'élément au sommet de la pile

    return 0;
}
