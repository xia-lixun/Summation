/* 
 * File:   CBenchMark.h
 * Author: lixun
 *
 * Created on September 7, 2015, 11:42 AM
 */

#ifndef CBENCHMARK_H
#define	CBENCHMARK_H



#include <ctime>



class CBenchMark {
    
public:
    CBenchMark();
    virtual ~CBenchMark();
    
    void TimerStart(void);
    long TimerStop(void);
    long GetTimeElapsed(void);

private:
    CBenchMark(const CBenchMark& orig);

protected:
    timespec TimeStart, TimeStop;
    long Elapsed;    
};

#endif	/* CBENCHMARK_H */

