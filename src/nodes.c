#pragma once
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum OperationType {
    VARIABLE,
    CONSTANT,
    ADD,
    SUBTRACT,
    MULTIPLY,
} OperationType;

typedef struct Node {
    float value;
    float gradient;
    OperationType operation;
    struct Node* left;
    struct Node* right;
    size_t reference_counter;
} Node;

Node* new_operation(float value, OperationType operation, Node* left, Node* right){
    Node* x = malloc(sizeof(Node));
    if (x == NULL){
        perror("Malloc Error");
        exit(1);
    }
    x->value = value;
    x->gradient = 0.0;
    x->operation = operation;
    x->left = left;
    x->right = right;
    x->reference_counter = 0;
    return x;
}

void clear_graph(Node* operation){
    if (!operation) return;

    if (operation->operation == VARIABLE){
        operation->reference_counter--;
        operation->gradient = 0.0;
        return;
    }
    
    if (--operation->reference_counter == 0){
        clear_graph(operation->left);
        clear_graph(operation->right);
        free(operation);
    }
}

Node* variable(float value){
    Node* x =  new_operation(value, VARIABLE, NULL, NULL);
    x->reference_counter++;
    return x;
}

Node* constant(float value){
    return new_operation(value, CONSTANT, NULL, NULL);
}


void internal_backprop(Node* node, float gradient){
    switch (node->operation) {
        case ADD:
            internal_backprop(node->left, gradient);
            internal_backprop(node->right, gradient);
            break;
        case SUBTRACT:
            internal_backprop(node->left, gradient);
            internal_backprop(node->right, -gradient);
            break;
        case MULTIPLY:
            internal_backprop(node->left, gradient*node->right->value);
            internal_backprop(node->right, gradient*node->left->value);
            break;
        case VARIABLE:
            node->gradient += gradient;
            break;
        case CONSTANT:
            break;
    }
}

void backpropagate(Node* node){
    node->reference_counter++;
    internal_backprop(node, 1.0);
}
