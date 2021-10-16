#include "anomaly_detection_util.h"
#include <math.h>

float var(float* x, int size){
    float miu = getMiu(x, size);
    float var = 0;
    for (int i = 1; i <= size; i++){
        var += pow((x[i] - miu), 2);
    }
    return var / size;
}

float getMiu(float* x, int size){
    float miu = 0;
    for (int i = 1; i <= size; i++){
        miu += x[i];
    }
    return miu / size;
}
