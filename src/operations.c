#pragma once
#include "nodes.c"

Node* add(Node* left, Node* right){
    left->reference_counter++;
    right->reference_counter++;
    return new_operation(left->value+right->value, ADD, left, right);
}

Node* subtract(Node* left, Node* right){
    left->reference_counter++;
    right->reference_counter++;
    return new_operation(left->value-right->value, SUBTRACT, left, right);
}

Node* multiply(Node* left, Node* right){
    left->reference_counter++;
    right->reference_counter++;
    return new_operation(left->value*right->value, MULTIPLY, left, right);
}
