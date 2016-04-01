/* 
 * ellipticalstability.h
 * 
 * Copyright (C) 2015 Bernardo <b.b.monteiro@gmail.com>
 *
 * This file is released under the GPLv2
 */

/*This library contains functions to calculate the stability of model rockets
 * which use elliptical wings, using the Barrowman method*/

#ifndef _STABILITY_H
#define _STABILITY_H
#include <math.h>

/*CNfin_nointerference: Calculates the normal force coeficient of a set of n
 * fins (n=3,4), without accounting for body interference*/
double CNfins_nointerference(int n, double aspectRatio, double referenceRadius,
		double rootChord, double span);

/*interferenceCoeficient: calculates the interference coeficient for the set of fins.*/
double interferenceCoeficient(double span, double tailRadius);

/*CNfins: Calculates the normal force coeficient of a set of n fins (n=3,4), accounting for body interference, considering a cilindrical body.*/
double CNfins(int n, double aspectRatio, double referenceDiameter, double rootChord, double span);

/*Zfin: returns the center of pressure for a set of fins with the given rootchord*/
double Zfin(double rootChord);

/*stabilityCoefficient: returns the stability coefficient for a
 * elliptical wing with the paramenters provided.*/
double stabilityCoefficient(double density, double M0, double CM0, double CN0,
		double Z0, double length, double t, double aspectRatio,
		int nfins, double bodyRadius, double rootChord);

/*finVolume: returns the volume of an elliptical fin with a simmetrical NACA
 * profile for the parameters provided*/
double finVolumeNACA(double rootChord, double span, double t);

#endif /*_STABILITY.H*/
