/* 
 * File:   CMoment.cpp
 * Author: lixun
 * 
 * Created on September 11, 2015, 3:53 PM
 */

#include "CMoment.h"



CMoment::CMoment() {
    
    SampleMean = 0.0;
    SampleVariance = 0.0;

    SampleMean_f = 0.0F;
    SampleVariance_f = 0.0F;
}


CMoment::CMoment(const CMoment& orig) {
}

CMoment::~CMoment() {
}


// Sample Mean: X_hat = Sum{Xi}_{i=1..N}/N  is the unbiased estimate of population mean
// Sum{Xi}_{i=1..N}/N = Sum{Xi}_{i=1..N-1}/N-1 * (N-1/N) + Xn * (1/N)
// That is to equivalent to E{Xi_N} = <E{Xi_N-1} Xn>.<N-1/N 1/N> where <>.<> is inner
// product of tow vectors. This is the online update of sample mean sample by sample.
// Nevertheless updating sample mean sample by sample is a bad idea as every update
// involves multiplication round off error. A better method of calculating sample mean 
// of ultra long data history is to calculate the sample mean of each segment, pushing 
// the results to a queue. The length of the queue is preferably power of 2. The final 
// sample mean estimate would be the product between the sum of the queue against 1/M.
// where M is the length of the queue. if M is a power of 2 then the multiplication is
// likely to be round-error free!
// Note that in this case the sample mean is calculated against a sliding window of the 
// data whose length is m*length(segment).
double CMoment::SampleMean(double* Data, int Length) {
    CSumKahan Sum;
    SampleMean = Sum.Add4d(Data, Length) / (double)Length;
    return SampleMean;
}

float CMoment::SampleMean(float* Data, int Length) {
    CSumKahan Sum;
    SampleMean = (double) Sum.Add8f(Data, Length) / (double) Length;
    SampleMean_f = (float) SampleMean;
    return SampleMean_f;
}




// Var(X) = Var(X-K)
// K = E{X}
// Var(X) = E{X**2} - E{X}**2
//        = ( Sum{X**2} - Sum{X}**2/N ) / N-1
//        = ( Sum{(X-K)**2} - Sum{X-K}**2/N ) / N-1
double CMoment::SampleVariance(double* Data, int Length) {
    
    double K;
    double XmK;
 
    CSumKahan SumX2;
    
    K = SampleMean(Data, Length);
    for(int i = 0; i < Length; i++) {
        XmK = Data[i] - K;
        SumX2.Add(XmK * XmK);
    }
    SampleVariance = SumX2.GetSum() / (double)(Length-1);
    return SampleVariance;
}





float CMoment::SampleVariance(float* Data, int Length) {

    float K;
    float XmK;
 
    CSumKahan SumX2;
    
    K = SampleMean(Data, Length);
    for(int i = 0; i < Length; i++) {
        XmK = Data[i] - K;
        SumX2.Add(XmK * XmK);
    }
    SampleVariance = (double) SumX2.GetSumFloat() / (double)(Length-1);
    SampleVariance_f = (float) SampleVariance;
    return SampleVariance_f;    
}