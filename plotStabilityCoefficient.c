/* 
 * plotStabilityCoefficient.c
 * 
 * Copyright (C) 2015 Bernardo <b.b.monteiro@gmail.com>
 *
 * This file is released under the GPLv2
 */

/* This program outputs a series of ordenated pairs to use for ploting a graph
 * of stability coefficient vs root chord (suggested plotting program:
 * gnuplot).
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
#define DENSITY 0 /*PLA density*/


main(){
	const double M0=30, CM0=20, CN0=1, Z0=1, length=40, t=0.08, aspectRatio=2, bodyRadius=1;
	int nfins=3;

	double rootChord;

	for(rootChord=0;rootChord<length;rootChord+=PRECISION)
		printf("%lf %lf\n",rootChord,stabilityCoefficient(DENSITY,M0,CM0,CN0,Z0,length,t,aspectRatio, nfins, bodyRadius, rootChord));

	return 0;
}
