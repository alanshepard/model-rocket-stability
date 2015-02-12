/* 
 * stabilitycoeficient.c
 * 
 * Copyright (C) 2015 Bernardo <b.b.monteiro@gmail.com>
 *
 * This file is released under the GPLv2
 */

/*Expected input: 
 * M0: rocket's mass without fins;
 * CM0: rocket's center of mass without fins. Origin is on the tip of the nose;
 * CN0: rocket's normal force coeficient without fins;
 * Z0: rocket's center of pressure without fins;
 * diameter: rocket's diameter;
 * length: rocket's length;
 * t: fin's profile maximum thickness in relation to the chord;
 * aspectRatio: desired aspect ratio for the fins.
 */

/*This program uses cm,g,s units*/

#include <stdio.h>
#include <math.h>
#include "ellipticalstability.h"
#define PRECISION 1e-4
#define DENSITY 1.25 /*PLA density (g/cm^3)*/


main(){
	const double M0=46.7, CM0=18.08348, CN0=2, Z0=1.76148, length=30.778, t=0.12, aspectRatio=1.5, bodyRadius=1;
	int nfins=3;

	double rootChord=3.111;

	printf("rootChord=%lf\n stability coeficient = %lf\n",rootChord,stabilityCoefficient(DENSITY,M0,CM0,CN0,Z0,length,t,aspectRatio, nfins, bodyRadius, rootChord));

	return 0;
}
