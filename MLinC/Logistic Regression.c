#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Squishing Function
double sigmoid(double z)
{
    return 1.0 / (1.0 + exp(-z));
}

//Likelihood of Happening
double likelihood_probability(double *X, double *y, double *w, int m, int n)
{
    double log_likelihood = 0.0;
    for (int i =0; i<m; i++)
    {
        double h = sigmoid(w[0]*X[i*n] + w[1]); //Hypothesis value
        log_likelihood += (y[i]*log(h) + (1 - y[i]) * log(1-h));
    }

    return log_likelihood/m;
}

//Gradient decent for Optimisation of Logistic Regression
void gradient_decent(double *X, double *y, double *w, int m, int n, double learning_rate, int iterations)
{
    for(int i = 0; i < iterations; i++)
    {
        double *grad = (double*)calloc(n,sizeof(double));


    // Compute the gradient
    for(int j = 0; j <m; j++)
    {
        double h = sigmoid(w[0] * X[j * n] + w[1]);
        grad[0] += ((h - y[j])*X[j*n]);
        grad[1] += (h - y[j]);
    }

    //Updating Params
    w[0] -= (learning_rate/m)*grad[0];
    w[1] -= (learning_rate/m)*grad[1];

    free(grad);

    //Printing the likelihood
    if(i % 100 ==0)
    {
        printf("On Interation %d Likelihood is: %f\n",i, likelihood_probability(X, y, w,m, n));
    }

    }
}

int predict(double * X, double *w, int m)
{
    double z = w[1] + X[0] * w[0];
    return sigmoid(z) >=0.5 ? 1 : 0;
}

int main()
{
    int m = 5;
    int n = 1;

    double X[] = {1,2,3,4,5};
    double y[] = {0,0,1,1,0};

    double w[] = {0.0,0.0}; // Using Weight, bias

    double learning_rate = 0.1;
    int iterations = 1000;

    gradient_decent(X, y, w, m, n, learning_rate, iterations);
    // Print the final parameters
        printf("Trained W: W[1] = %f, W[0] = %f\n", w[1], w[0]);

        // Make a prediction for a new input
        double new_X[] = {5};  // New input feature
        int prediction = predict(new_X, w, 1);
        printf("Prediction for X = 5: %d\n", prediction);

        return 0;
}
