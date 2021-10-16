/*
     anomaly_detection_util.cpp
    Authors:
    1. Yuval Uner ID: 322558842
    2. Nadav Elgrabli ID: 316082791
*/
#include "anomaly_detection_util.h"
#include <math.h>
#include <stdlib.h>

// Returns the mathematical average of from an array of floats
float getAvg(float* x, int size) {
    float miu = 0;
    for (int i = 0; i < size; i++) {
        miu += x[i];
    }
    return miu / size;
}

// returns the variance of X and Y 
float var(float* x, int size) {
    float miu = getAvg(x, size);
    float var = 0;
    for (int i = 1; i <= size; i++) {
        var += pow((x[i] - miu), 2);
    }
    return var / size;
}

// returns the covariance of X and Y 
float cov(float* x, float* y, int size) {
    float xAvg = getAvg(x, size);
    float yAvg = getAvg(y, size);
    float getE = 0;
    for (int i = 0; i < size; i++) {
        getE += (x[i] - xAvg) * (y[i] - yAvg);
    }
    return getE / size;
}

// returns the Pearson correlation coefficient of X and Y 
float pearson(float* x, float* y, int size) {
    return cov(x, y, size) / (sqrt(var(x, size)) * sqrt(var(y, size)));
}

// performs a linear regression and return s the line equation 
Line linear_reg(Point** points, int size) {
    float* xValues = new float[size];
    float* yValues = new float[size];
    for (int i = 0; i < size; i++) {
        xValues[i] = points[i]->x;
        yValues[i] = points[i]->y;
    }
    float a = cov(xValues, yValues, size) / var(xValues, size);
    float b = getAvg(yValues, size) - (a * getAvg(xValues, size));
    delete[] xValues;
    delete[] yValues;
    return Line(a, b);
}
// returns the deviation between point p and the line equation of the points 
float dev(Point p, Point** points, int size) {
    Line line = linear_reg(points, size);
    float deviation = abs(line.f(p.x) - p.y);
    return deviation;
}

// returns the deviation between point p and the line 
float dev(Point p, Line l) {
    return abs(l.f(p.x) - p.y);
}
