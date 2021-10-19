/*
     anomaly_detection_util.cpp
    Authors:
    1. Yuval Uner ID: 322558842
    2. Nadav Elgrabli ID: 316082791
*/
#include "anomaly_detection_util.h"
#include <math.h>
#include <iostream>

using namespace std;

// Returns the absolute value of a float
float absValue(float val){
    if (val < 0){
        return -val;
    }
    return val;
}

// Returns the mathematical average of from an array of floats
float getAvg(float* x, int size) {
    if (size <= 0){
        throw "Size must be a positive integer";
    }
    float miu = 0;
    for (int i = 0; i < size; i++) {
        miu += x[i];
    }
    return miu / size;
}

// returns the variance of X and Y 
float var(float* x, int size) {
    if (size <= 0){
        throw "Size must be a positive integer";
    }
    float miu = getAvg(x, size);
    float var = 0;
    for (int i = 0; i < size; i++) {
        var += pow((x[i] - miu), 2);
    }
    return var / size;
}

// returns the covariance of X and Y 
float cov(float* x, float* y, int size) {
    if (size <= 0){
        throw "Size must be a positive integer";
    }
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
    float deviation = absValue(line.f(p.x) - p.y);
    return deviation;
}

// returns the deviation between point p and the line 
float dev(Point p, Line l) {
    return absValue(l.f(p.x) - p.y);
}

//-----------------------------------------------------------------------

bool wrong(float val, float expected){
	return val<expected-0.001 || val>expected+0.001;
}

// this is a simple test to put you on the right track
int main(){
	const int N=10;
	float x[]={1,2,3,4,5,6,7,8,9,10};
	float y[]={2.1,4.2,6.1,8.1,10.3,12.2,14.4,16.1,18.2,20.3};

	Point* ps[N];
	for(int i=0;i<N;i++)
		ps[i]=new Point(x[i],y[i]);

	Line l=linear_reg(ps,N);
	Point p(4,8);

	float v[]={var(x,N),cov(x,y,N),pearson(x,y,N),l.a,l.b,l.f(4),dev(p,l)};
	float e[]={8.25,16.63,0.999,2.015,0.113,8.176,0.176};


	for(int i=0;i<7;i++)
		if(wrong(v[i],e[i]))
			cout<<"error for check "<<i<<" (-14)"<<endl;


	for(int i=0;i<N;i++)
		delete ps[i];

	cout<<"done"<<endl;
	return 0;
}