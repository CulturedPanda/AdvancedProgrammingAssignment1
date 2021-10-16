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

float pearson(float* x, float* y, int size){
    return cov(x, y, size) / (sqrt(var(x, size)) * sqrt(var(y, size)));
}

