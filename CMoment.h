/* 
 * File:   CMoment.h
 * Author: lixun
 *
 * Created on September 11, 2015, 3:53 PM
 */

#ifndef CMOMENT_H
#define	CMOMENT_H

#include "CSumKahan.h"




class CMoment {
    
public:
    CMoment();
    virtual ~CMoment();
    
    double SampleMean(double * Data, int Length);
    double SampleVariance(double * Data, int Length);
    
    float SampleMean(float * Data, int Length);
    float SampleVariance(float * Data, int Length);
    
private:
    CMoment(const CMoment& orig);
    
protected:
    double SampleMean;
    double SampleVariance;
    
    float SampleMean_f;
    float SampleVariance_f;
};

#endif	/* CMOMENT_H */

