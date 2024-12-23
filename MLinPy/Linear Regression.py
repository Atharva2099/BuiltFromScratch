import numpy as np
import pandas as pd

def linear_regression(X, y):
    n = len(X)  # Number of data points
    sum_x, sum_y, sum_xy, sum_x2 = 0, 0, 0, 0

    # Calculate the necessary sums
    for i in range(n):
        sum_x += X[i]
        sum_y += y[i]
        sum_xy += X[i] * y[i]
        sum_x2 += X[i] ** 2

    # Calculate the slope (m) and bias (b)
    m = (sum_xy - (sum_x * sum_y) / n) / (sum_x2 - (sum_x ** 2) / n)
    b = (sum_y - m * sum_x) / n

    return m, b

def main():
    # Sample data
    Time = [5, 7, 12, 16, 20]
    Mass = [40, 120, 180, 210, 240]

    # Perform linear regression
    Slope, Bias = linear_regression(Time, Mass)

    # Output the results
    print(f"Slope: {Slope}")
    print(f"Bias (Intercept): {Bias}")

if __name__ == "__main__":
    main()
