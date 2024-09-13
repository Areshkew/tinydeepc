#ifndef __LINEAL__
#define __LINEAL__

/* 
 * Lineal Model: 
 * The Lineal structure represents a linear model where:
 *   y = x * w
 * Here, 'w' is the weight (or coefficient) that is learned from the data,
 * 'x' is the input, and 'y' is the predicted output. This is a simple 
 * linear regression model.
 */
typedef struct Lineal Lineal;

/* 
 * Function: lineal_create
 * -----------------------
 * Creates and initializes a new Lineal model (structure).
 * 
 * Returns:
 *   A pointer to the newly created Lineal structure, which contains the 
 *   weight (w) for the linear model. The weight is initialized to a random 
 *   value or a default.
 */
Lineal* lineal_create(void);

/* 
 * Function: lineal_train
 * ----------------------
 * Trains the linear model by updating the weight (w) using a dataset of inputs 
 * (x) and their corresponding outputs (y).
 *
 * Arguments:
 *   model - A pointer to the Lineal structure (the model to train).
 *   x     - A pointer to an array of input data (the feature values).
 *   y     - A pointer to an array of output data (the true target values).
 *
 * Description:
 *   This function computes the cost function C(w) and its derivative (as shown 
 *   in the image). It updates the weight (w) by performing gradient descent 
 *   or another optimization algorithm. The goal is to minimize the cost function:
 * 
 *       C(w) = (1/n) * Σ (x_i * w - y_i)^2
 *
 *   The derivative of the cost function (for weight update) is:
 * 
 *       C'(w) = (1/n) * Σ 2 * (x_i * w - y_i) * x_i
 */
void lineal_train(Lineal* m, float* xs, float* ys, size_t size, const float learning_rate, const float epochs);

/* 
 * Function: lineal_predict
 * ------------------------
 * Predicts the output (y) for a given input (x) using the trained linear model.
 *
 * Arguments:
 *   model - A pointer to the Lineal structure (the trained model).
 *   x     - The input value for which to predict the output.
 *
 * Returns:
 *   The predicted output (y) for the given input x, computed as:
 * 
 *       y = x * w
 *
 * Description:
 *   Once the model is trained, you can use this function to make predictions
 *   on new data points using the weight (w) learned during training.
 */
float lineal_predict(Lineal* m, float x);

/* 
 * Function: lineal_destroy
 * ------------------------
 * Frees the memory allocated for the Lineal model.
 *
 * Arguments:
 *   model - A pointer to a pointer to the Lineal structure. After calling 
 *           this function, the pointer is set to NULL to avoid dangling 
 *           references.
 *
 * Description:
 *   This function should be called when the Lineal model is no longer needed 
 *   to properly free the allocated memory and prevent memory leaks.
 */
void lineal_destroy(Lineal** m);

#endif
