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
#include "stability.h"
#include "ellipticalWing.h"
#define PRECISION 1e-4
#define DENSITY 0 /*PLA density*/

double stabilityCoeficient(double M0, double CM0, double CN0, double Z0, double length, double t, double aspectRatio, int nfins, double bodyRadius, double a);

main(){
	const double M0=30, CM0=20, CN0=1, Z0=1, length=40, t=0.08, aspectRatio=2, bodyRadius=1;
	int nfins=3;

	double a=1;

	printf("a=%lf\n stability coeficient = %lf\n",a,stabilityCoeficient(M0,CM0,CN0,Z0,length,t,aspectRatio, nfins, bodyRadius, a));

	return 0;
}

/*stabilityCoeficient: returns the stability coeficient for a
 * elliptical wing with the paramenters provided. The wing is modelled
 * as a trapezoidal wing using ellipticalWing.h*/

double stabilityCoeficient(double M0, double CM0, double CN0, double Z0, double length, double t, double aspectRatio, int nfins, double bodyRadius, double a){

	/*center of pressure*/
	//printf("a=%lf\n",a);
	const double rootChord=ellipticalRootChord(a);
	const double tipChord=ellipticalTipChord(a);
	const double span=ellipticalSpan(a,aspectRatio);
	const double sweepAngle=0;
	double CNt,Zt,Z;
	
	if(a!=0){
		CNt=CNfins(nfins,aspectRatio,bodyRadius,rootChord,tipChord,span,sweepAngle);
		printf("CNt=%lf\n",CNt);

		Zt=Zfin(length-2*a,rootChord,tipChord,(rootChord-tipChord)/2); 
		printf("Zt=%lf\n",Zt);

		Z=(CN0 * Z0 + CNt * Zt)/(CN0+CNt);
		printf("Z=%lf\n",Z);
	}else CNt=0,Zt=0,Z=Z0;

	/*center of mass*/
	double Mt=nfins*ellipticalVolume(a,span,t)*DENSITY;

	/*considering that the center of mass of each fin is in the middle of
	 * the chord. This is an approximation which results in a more
	 * conservative stability coeficient (i.e. it yields smaller stability
	 * coeficients)*/
	double CMt=length-a;

	double CM=(CM0*M0+CMt*Mt)/(M0+Mt);

	/*stability coeficient*/
	return (Z-CM)/(2*bodyRadius);
}
