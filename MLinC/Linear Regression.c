#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void lin_reg(double x[], double y[], int n, double *slope, double *bias)
{
    double sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0, x_bar = 0,
    y_bar = 0, xy_bar = 0;
    for(int i = 0; i < n; i++)
    {
        sum_x += x[i];
        sum_y += y[i];
        sum_xy += x[i]*y[i];
        sum_x2 += x[i]*x[i];
    }
    x_bar = sum_x/n;
    y_bar = sum_y/n;
    xy_bar = sum_xy/n;
    *slope = (sum_xy - (sum_x * sum_y)/n)/
             (sum_x2 - (sum_x * sum_x)/n);
    *bias = y_bar - (*slope * x_bar);
}

//Can read CSV for non - hardcoded data
void read_csv(const char* filename, double x[], double y[], int* n)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file\n");
        return;
    }
    char line[1024];
    int i = 0;
    // Skip header if exists
    fgets(line, 1024, file);
    while (fgets(line, 1024, file) && i < *n)
    {
        char* token = strtok(line, ",");
        x[i] = atof(token);
        token = strtok(NULL, ",");
        y[i] = atof(token);
        i++;
    }
    *n = i;
    fclose(file);
}

int main()
{
    double x[1000], y[1000];  // Increased array size to handle larger datasets
    int n = 1000;  // Maximum number of points to read

    // Read data from CSV file
    read_csv("LinAlg.csv", x, y, &n);

    // Check if data was read successfully
    if (n == 0)
    {
        printf("No data was read from the file\n");
        return 1;
    }

    double slope, bias;

    // Perform linear regression
    lin_reg(x, y, n, &slope, &bias);

    // Output results
    printf("Number of data points: %d\n", n);
    printf("Slope (m): %f\n", slope);
    printf("Intercept (b): %f\n", bias);

    // Predict and display values
    printf("\nPredicted values:\n");
    for (int i = 0; i < n; i++)
    {
        double y_pred = slope * x[i] + bias;
        printf("x: %f, y_actual: %f, y_predicted: %f\n",
               x[i], y[i], y_pred);
    }

    return 0;
}
