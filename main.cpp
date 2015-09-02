/* 
 * File:   main.cpp
 * Author: lixun
 *
 * Created on September 2, 2015, 12:56 PM
 */
#include <time.h>
#include <cstdlib>
#include <stdio.h>
#include <math.h>
#include <gmpxx.h>
#include "CSumKahan.h"

using namespace std;


/*
 * 
 */
int main(int argc, char** argv) {

    mpf_class x0, x1, x2, x3, x4, x5, x6, x7;
    mpf_class r;
    
    x0 = "0.00000001";
    x1 = "10000000.0";
    x2 = "0.00000001";
    x3 = "10000000.0";
    x4 = "0.00000001";
    x5 = "10000000.0";
    x6 = "0.00000001";
    x7 = "10000000.0";
    
    r = x0+x1;
    r += x2;
    r += x3;
    r += x4;
    r += x5;
    r += x6;
    r += x7;
    printf("GMP Sum: %12.12f\n", r.get_d());

    
    double x[8];
    x[0] = 0.00000001;
    x[1] = 10000000.0;
    x[2] = 0.00000001;
    x[3] = 10000000.0;
    x[4] = 0.00000001;
    x[5] = 10000000.0;
    x[6] = 0.00000001;
    x[7] = 10000000.0; 

    CSumKahan acc;
    printf("My Sum: %12.12f\n", acc.Add(x, 8));    
    printf("My Sum: %12.12f\n", acc.GetSum());    
    printf("My ErrMax: %12.12f\n", acc.GetErrMax());        
    printf("My ErrMin: %12.12f\n", acc.GetErrMin());  
    
    double y = 0.0;
    for(int i = 0; i < 8; i++) {
        y += x[i];
    }
    printf("Naive Sum: %12.12f\n", y);
    printf("==================\n");
    
    double DataTest[8192];
    double offset = 0.4;    
    srand(time(NULL));  
    for(int i = 0; i < 8192; i++) {
        DataTest[i] = ((double) rand()) / (double)RAND_MAX - offset;
    }
    acc.Reset();
    printf("Kahan Sum(random): %12.12f\n", acc.Add(DataTest, 8192));
    
    y = 0.0;
    r = 0.0;
    for(int i = 0; i < 8192; i++) {
        y += DataTest[i];
        x0 = DataTest[i];
        r += x0;
    }
    printf("Naive Sum(random): %12.12f\n", y);
    printf("GMP Sum(random): %12.12f\n", r.get_d());
    printf("==================\n");    
    printf("= Try different offset values for different summation conditional number.\n");    
    printf("==================\n");    
    return 0;
}

