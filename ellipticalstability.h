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

	return (n*aspectRatio*M_PI*(span*rootChord)/(4*pow(referenceRadius,2)))/(2+sqrt(4+pow(aspectRatio,2)));
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
	return finStart+rootChord*(1/2-2/(3*M_PI));
}

/*stabilityCoefficient: returns the stability coefficient for a
 * elliptical wing with the paramenters provided.*/
double stabilityCoefficient(double density, double M0, double CM0, double CN0, double Z0, double length, double t, double aspectRatio, int nfins, double bodyRadius, double rootChord){

	/*center of pressure*/
	const double span=rootChord*aspectRatio*M_PI/2;
	double CNt,Zt,Z;
	
	if(rootChord!=0){
		CNt=CNfins_nointerference(nfins,aspectRatio,bodyRadius,rootChord,span);

		Zt=Zfin(length-rootChord,rootChord); 

		Z=(CN0 * Z0 + CNt * Zt)/(CN0+CNt);
	}else CNt=0,Zt=0,Z=Z0;

	/*center of mass*/
	double Mt=nfins*1.826889*t*pow(rootChord/2,2)*span*density;

	double CMt=length-rootChord/2; /* considering that the center of mass of
					* each fin is in the middle of the
					* chord. This is an approximation which
					* results in a more conservative
					* stability coefficient (i.e. it yields
					* smaller stability coefficients)*/

	double CM=(CM0*M0+CMt*Mt)/(M0+Mt);

	/*stability coefficient*/
	return (Z-CM)/(2*bodyRadius);
}

#endif
