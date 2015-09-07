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
    
    mSum_f = 0.0F;
    mErr_f = 0.0F;
    mErrMax_f = mErr_f;
    mErrMin_f = mErr_f;
    
    SumVec4d = Vec4d(0.0);
    ErrVec4d = Vec4d(0.0);    
    
    SumVec8f = Vec8f(0.0F);
    ErrVec8f = Vec8f(0.0F);    
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
   
    SumVec4d = Vec4d(0.0);
    ErrVec4d = Vec4d(0.0);    
    
    SumVec8f = Vec8f(0.0F);
    ErrVec8f = Vec8f(0.0F);
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
    if(Length < 0) {
        return SetNaN_d();
    } else if(Length == 0) {
        return mSum;
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
    if(Length < 0) {
        return SetNaN_f();
    } else if(Length == 0) {
        return mSum_f;
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










double CSumKahan::Add4d(double * Data, int Length) {
    
    if(Length < 4) {
        Add(Data, Length);
    } else {
        Vec4d DataVec4d;
        Vec4d InputCompensatedVec4d;
        Vec4d SumConvergeVec4d;
        
        int i;
        for(i = 0; i+4 <= Length; i += 4) {
            DataVec4d.load(Data);
            InputCompensatedVec4d = DataVec4d - ErrVec4d; 
            SumConvergeVec4d = SumVec4d + InputCompensatedVec4d;
            ErrVec4d = (SumConvergeVec4d - SumVec4d) - InputCompensatedVec4d;
            SumVec4d = SumConvergeVec4d;
            Data += 4;
        }

        double mSumVec4d[4];
        SumVec4d.store(mSumVec4d);
        Add(mSumVec4d, 4);
        Add(Data, Length-i);
    }
    return mSum;        
}




float CSumKahan::Add8f(float * Data, int Length) {
    
    if(Length < 8) {
        Add(Data, Length);
    } else {
        Vec8f DataVec8f;
        Vec8f InputCompensatedVec8f;
        Vec8f SumConvergeVec8f;
        
        int i;
        for(i = 0; i+8 <= Length; i += 8) {
            DataVec8f.load(Data);
            InputCompensatedVec8f = DataVec8f - ErrVec8f; 
            SumConvergeVec8f = SumVec8f + InputCompensatedVec8f;
            ErrVec8f = (SumConvergeVec8f - SumVec8f) - InputCompensatedVec8f;
            SumVec8f = SumConvergeVec8f;
            Data += 8;
        }

        float mSumVec8f[8];
        SumVec8f.store(mSumVec8f);
        Add(mSumVec8f, 8);
        Add(Data, Length-i);
    }
    return mSum_f;        
}