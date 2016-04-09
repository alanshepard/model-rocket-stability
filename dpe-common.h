#ifndef __DPE_COMMON_H
#define __DPE_COMMON_H

#include "rocket.h"
#include <cmath>

const Ogive parabola(2.3, 5.485, 14.46982, M_PI*1.8*1.8, 8.64);

const double tubeLinDensity = (5.5+4.9+4.9+6.5+6.0)/(19.9+19.8+19.6+25.7+25.5);

const Engine bandeiranteC_ejection(19.73, 6.86-3.31, 6.86);
const Engine bandeiranteB	  (16.7,  7.63-2.8,  7.63);

#endif //__DPE_COMMON_H
