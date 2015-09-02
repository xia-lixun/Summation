/* 
 * File:   CSum.cpp
 * Author: lixun
 * 
 * Created on September 2, 2015, 1:51 PM
 */


#include "CSumKahan.h"



CSumKahan::CSumKahan() {
        
    mSum = 0.0;
    mErr = 0.0;
    mErrMax = mErr;
    mErrMin = mErr;
}

CSumKahan::CSumKahan(const CSumKahan& orig) {
}

CSumKahan::~CSumKahan() {
}






void CSumKahan::Reset() {
    
    mSum = 0.0;
    mErr = 0.0;
    mErrMax = mErr;
    mErrMin = mErr;

    mSum_f = 0.0F;
    mErr_f = 0.0F;
    mErrMax_f = mErr_f;
    mErrMin_f = mErr_f;     
}



double CSumKahan::SetNaN_d() {
    
    unsigned int mNaN[2];
    double *pNaN = (double *) mNaN;
    
    mNaN[0] = 0xFFFFFFFF;
    mNaN[1] = 0xFFFFFF7F;
    
    return *pNaN;
}


float CSumKahan::SetNaN_f() {
    
    unsigned int mNaN;
    float *pNaN = (float *) &mNaN;
    
    mNaN = 0xFFFFFF7F;
    
    return *pNaN;
}



double CSumKahan::Add(double Data) {
    
    double mInputCompensated;
    double mSumConverge;
    
    mInputCompensated = Data - mErr;
    mSumConverge  = mSum + mInputCompensated;
    mErr = (mSumConverge - mSum) - mInputCompensated;
    mSum = mSumConverge;
    
    mErrMax = (mErr >= mErrMax) ? mErr:mErrMax;
    mErrMin = (mErr <= mErrMin) ? mErr:mErrMin;

    return mSum;
}




double CSumKahan::Add(double * Data, int Length) {
    
    double mInputCompensated;
    double mSumConverge;
    
    // check if length is valid
    if(Length <= 0) {
        return SetNaN_d();
    }
    
    for(int i = 0; i < Length; i++) {
        mInputCompensated = Data[i] - mErr;
        mSumConverge  = mSum + mInputCompensated;
        mErr = (mSumConverge - mSum) - mInputCompensated;
        mSum = mSumConverge;
        
        mErrMax = (mErr >= mErrMax) ? mErr:mErrMax;
        mErrMin = (mErr <= mErrMin) ? mErr:mErrMin;
    }
    return mSum;
}






float CSumKahan::Add(float Data) {
    
    float mInputCompensated_f;
    float mSumConverge_f;
    
    mInputCompensated_f = Data - mErr_f;
    mSumConverge_f  = mSum_f + mInputCompensated_f;
    mErr_f = (mSumConverge_f - mSum_f) - mInputCompensated_f;
    mSum_f = mSumConverge_f;
    
    mErrMax_f = (mErr_f >= mErrMax_f) ? mErr_f:mErrMax_f;
    mErrMin_f = (mErr_f <= mErrMin_f) ? mErr_f:mErrMin_f;

    return mSum_f;
}


float CSumKahan::Add(float * Data, int Length) {
    
    float mInputCompensated_f;
    float mSumConverge_f;
    
    // check if length is valid
    if(Length <= 0) {
        return SetNaN_f();
    }
    
    for(int i = 0; i < Length; i++) {
        mInputCompensated_f = Data[i] - mErr_f;
        mSumConverge_f  = mSum_f + mInputCompensated_f;
        mErr_f = (mSumConverge_f - mSum_f) - mInputCompensated_f;
        mSum_f = mSumConverge_f;
        
        mErrMax_f = (mErr_f >= mErrMax_f) ? mErr:mErrMax_f;
        mErrMin_f = (mErr_f <= mErrMin_f) ? mErr:mErrMin_f;
    }
    return mSum_f;
}



double CSumKahan::GetSum() {
    return mSum;
}


double CSumKahan::GetErrMax() {
    return mErrMax;
}


double CSumKahan::GetErrMin() {
    return mErrMin;
}


float CSumKahan::GetSumFloat() {
    return mSum_f;
}


float CSumKahan::GetErrMaxFloat() {
    return mErrMax_f;
}


float CSumKahan::GetErrMinFloat() {
    return mErrMin_f;
}
