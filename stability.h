/* 
 * stability.h
 * 
 * Copyright (C) 2015 Bernardo <b.b.monteiro@gmail.com>
 *
 * This file is released under the GPLv2
 */

/*This library contains functions to calculate the stability of model rockets
 * which use elliptical wings*/

#ifndef STABILITY_H
#define STABILITY_H
#include <math.h>

/*Barowman method*/

/*CNfin_nointerference: Calculates the normal force coeficient of a set of n fins (n=3,4), without accounting for body interference*/
double CNfins_nointerference(int n, double aspectRatio, double referenceRadius, double rootChord, double span){

	return (n*aspectRatio*(M_PI*span*rootChord))/(4*pow(referenceRadius,2))/(2+sqrt(4+pow(aspectRatio,2)));
}

/*interferenceCoeficient: calculates the interference coeficient for the set of fins.*/
double interferenceCoeficient(double span, double tailRadius){
	register const double t=(span+tailRadius)/tailRadius;

	return 2/(M_PI*pow(1-1/t,2))*((1+1/pow(t,4))*(0.5*atan(1/2*(t-1/t)))-1/pow(t,2)*((t-1/t)+2*atan(1/t)));
}

/*CNfins: Calculates the normal force coeficient of a set of n fins (n=3,4), accounting for body interference, considering a cilindrical body.*/
double CNfins(int n, double aspectRatio, double bodyRadius, double rootChord, double span){
	return interferenceCoeficient(span,bodyRadius)*CNfins_nointerference(n,aspectRatio,bodyRadius,rootChord,span);
}

/*Zfin: returns the center of pressure for a set of fins with the given
 * paramenters. chordDisplacement is the longitudinal distance between
 * the leading edge of fin root and the leading edge of fin tip*/
double Zfin(double finStart, double rootChord){
	return rootChord*(1/2-2/(3*M_PI));
}

#endif
