#include <stdio.h>
#include <TinyDeep/Lineal.h>

int main(){
    float xs[] = {-1.0,  0.0, 1.0, 2.0, 3.0, 4.0};
    float ys[] = {-3.0, -1.0, 1.0, 3.0, 5.0, 7.0};
    size_t size = sizeof(xs) / sizeof(xs[0]);

    Lineal* model = lineal_create();
    lineal_train(model, xs, ys, size, 0.01, 500);

    printf("Predict 10: %f", lineal_predict(model, 10));
    lineal_destroy(&model);
    return 0;
}