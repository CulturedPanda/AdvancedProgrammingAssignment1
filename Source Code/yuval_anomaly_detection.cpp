#include "anomaly_detection_util.h"
#include <math.h>

float var(float* x, int size){
    float miu = getAvg(x, size);
    float var = 0;
    for (int i = 0; i < size; i++){
        var += pow((x[i] - miu), 2);
    }
    return var / size;
}

float getAvg(float* x, int size){
    float miu = 0;
    for (int i = 0; i < size; i++){
        miu += x[i];
    }
    return miu / size;
}

float cov(float* x, float* y, int size) {
    float xAvg = getAvg(x, size);
    float yAvg = getAvg(y, size);
    float getE = 0;
    for (int i = 0; i < size; i++) {
        getE += (x[i] - xAvg) * (y[i] - yAvg);
    }
    return getE / size;
}

float pearson(float* x, float* y, int size){
    return cov(x, y, size) / (sqrt(var(x, size)) * sqrt(var(y, size)));
}

Line linear_reg(Point** points, int size){
    float xValues[size];
    float yValues[size];
    for (int i = 0; i < size; i++){
        xValues[i] = points[i]->x;
        xValues[i] = points[i]->y;
    }
    float a = cov(xValues, yValues, size) / var(xValues, size);
    float b = getAvg(yValues, size) - (a * getAvg(xValues, size));
    return Line(a, b);
}

