#include <TinyDeep/Lineal.h>
#include <TinyDeep/Maths.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <errno.h>

extern int errno;

struct Lineal {
    float weight, bias;
};

float lineal_compute_cost(float w, float b, float* xs, float* ys, size_t size){
    float result = 0.0f;

    for (size_t i = 0; i < size; i++)
    {
        float p = xs[i] * w + b;
        float d = p - ys[i];
        result += d * d;
    }
    result /= size;

    return result;
}


float lineal_compute_cost_derivate_weight(float w, float b, float* xs, float* ys, size_t size){
    float result = 0.0f;

    for (size_t i = 0; i < size; i++)
    {
        float p = xs[i] * w + b;
        float d = p - ys[i];
        result += d * xs[i];
    }
    result = (2.0f / size) * result;

    return result;
}

float lineal_compute_cost_derivate_bias(float w, float b, float* xs, float* ys, size_t size){
    float result = 0.0f;

    for (size_t i = 0; i < size; i++)
    {
        float p = xs[i] * w + b;
        result += p - ys[i];
    }
    result = (2.0f / size) * result;

    return result;
}


Lineal* lineal_create(void){
    srand( time(0) );

    Lineal* new_linear = malloc( sizeof(Lineal) );
    if(new_linear == NULL) {
        perror("Error: ");
        return NULL;
    }

    new_linear->weight = f_random();
    new_linear->bias = f_random();

    return new_linear;
}

float lineal_predict(Lineal* m, float x){
    if(m == NULL) {
        errno = EINVAL;
        perror("Error: ");
        return NAN;
    }

    return x * m->weight + m->bias;
}

void lineal_train(Lineal* m, float* xs, float* ys, size_t size, const float learning_rate, const float epochs){
    if(m == NULL) {
        perror("Error: ");
        return;
    }

    for (size_t i = 0; i < epochs; i++)
    {
        float dw = lineal_compute_cost_derivate_weight(m->weight, m->bias, xs, ys, size);
        float db = lineal_compute_cost_derivate_bias(m->weight, m->bias, xs, ys, size);

        m->weight -= learning_rate * dw;
        m->bias -= learning_rate * db;

        float cost = lineal_compute_cost(m->weight, m->bias, xs, ys, size);
        if( (i+1) % 100 == 0 ) printf("Loss: %f | Epoch: %zu\n", cost, i);
    }
    

}

void lineal_destroy(Lineal** m){
    if( m == NULL  && *m == NULL ) return;

    *m = NULL;
    free(*m);
}