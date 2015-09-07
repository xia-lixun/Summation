/* 
 * File:   CBenchMark.cpp
 * Author: lixun
 * 
 * Created on September 7, 2015, 11:42 AM
 */

#include "CBenchMark.h"



CBenchMark::CBenchMark() {
}

CBenchMark::CBenchMark(const CBenchMark& orig) {
}

CBenchMark::~CBenchMark() {
}



void CBenchMark::TimerStart() {
    clock_gettime(CLOCK_MONOTONIC_RAW, &TimeStart);
}

long CBenchMark::TimerStop() {
    clock_gettime(CLOCK_MONOTONIC_RAW, &TimeStop);
    Elapsed = (TimeStop.tv_sec - TimeStart.tv_sec) * 1000000000 + (TimeStop.tv_nsec - TimeStart.tv_nsec);    
    return Elapsed;
}

long CBenchMark::GetTimeElapsed() {
    return Elapsed;
}