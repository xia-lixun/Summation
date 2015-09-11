/* 
 * File:   CSum.h
 * Author: lixun
 *
 * Created on September 2, 2015, 1:51 PM
 */

#ifndef CSUMKAHAN_H
#define	CSUMKAHAN_H




#include "instrset.h"
#include "vectorclass.h"
#include "complexvec.h"




class CSumKahan {
    
public:
    CSumKahan();
    virtual ~CSumKahan();

    double Add(double Data);
    double Add(double * Data, int Length);
    
    float Add(float Data);
    float Add(float * Data, int Length);
    
    void ResetSum(void);
    
    double GetSum(void);
    double GetErrMax(void);
    double GetErrMin(void);
    
    float GetSumFloat(void);
    float GetErrMaxFloat(void);
    float GetErrMinFloat(void);

    double Add4d(double * Data, int Length);
    float Add8f(float * Data, int Length);
    
private:
    CSumKahan(const CSumKahan& orig);
    
protected:
    double mSum;
    double mErr;
    double mErrMax;
    double mErrMin;    
    
    float mSum_f;
    float mErr_f;
    float mErrMax_f;
    float mErrMin_f;    
    
    double SetNaN_d(void);
    float SetNaN_f(void);
    
    // SSE/AVX
    Vec4d SumVec4d;
    Vec4d ErrVec4d;
    
    Vec8f SumVec8f;
    Vec8f ErrVec8f;

};

#endif	/* CSUM_H */

