#include "nodes.c"
#include "operations.c"
#include <stdio.h>
#include <time.h>

void update_variable(Node* op, float lr){
    op->value -= lr * op->gradient;
}

Node* evaluate(Node* a, Node* b, float x, float y){
    Node* prediction = add(multiply(a, constant(x)), b);
    Node* inter = subtract(constant(y), prediction);
    Node* loss = multiply(inter, inter);
    return loss;
}


int main(){
    clock_t start = clock();

    Node* a = variable(10.0);
    Node* b = variable(20.0);
    float x[] = {1, 2, 4, 5, 2, 3};
    float y[] = {3, 5, 6, 5, 4, 5};
    int len = 6;
    int max = 1000000;
    for (int i = 0; i < max; i++ ){
        Node* total = constant(0.0);
        for (int i = 0; i < len; i++){
            Node* loss = evaluate(a, b, x[i], y[i]);
            Node* new = add(total, loss);
            total = new;
        }
        backpropagate(total);
        update_variable(a, 0.01);
        update_variable(b, 0.01);
        clear_graph(total);
    }
    printf("a = %f\n",a->value);
    printf("b = %f\n",b->value);
    free(a);
    free(b);

    clock_t end = clock();
    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken: %.6f seconds\n", elapsed);
}
