/* 
 * finoptimizer.c
 * 
 * Copyright (C) 2015 Bernardo <b.b.monteiro@gmail.com>
 *
 * This file is released under the GPLv2
 */


/*Expected input: 
 * M0: rocket's mass without fins;
 * CM0: rocket's center of mass without fins. Origin is on the tip of the nose;
 * CN0: rocket's normal force coefficient without fins;
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
#define PRECISION 1e-7
#define DENSITY 1.25 /*PLA density (g/cm^3)*/
#define INTENDED_STABILITY_COEFICIENT 1
//#define DEBUG

double stabilityCoefficient(double M0, double CM0, double CN0, double Z0, double length, double t, double aspectRatio, int nfins, double bodyRadius, double a);

main(){
	double M0=46.7, CM0=18.08348, CN0=2, Z0=1.76148, length=30.778, t=0.12, aspectRatio=1.5, bodyRadius=1;
	int nfins=3;

	/*Get input data*/
	
	double x; /*x is approaching a*/
	double interval[2]={0,length/2}; /*we know a is in this interval*/
	double step=(interval[1]-interval[0])/2;

#ifdef DEBUG
	int iterationCounter=0; /*DEBUG*/
#endif

	/*This loop progressively diminishes the size of the interval, until it
	 * is smaller than the precision*/
	while(interval[1]-interval[0]>PRECISION){

#ifdef DEBUG
		fprintf(stderr,"iteration %u, interval: %lf %lf\n",++iterationCounter,interval[0],interval[1]); /*DEBUG*/
#endif

		double current,last=-HUGE_VAL; /*stores stability coeficients*/
		for(x=interval[0];(current=stabilityCoefficient(M0,CM0,CN0,Z0,length,t,aspectRatio, nfins, bodyRadius, x))<=INTENDED_STABILITY_COEFICIENT;x+=step){

#ifdef DEBUG
			fprintf(stderr,"x=%lf, coefficient=%lf\n",x,current); /*DEBUG*/
#endif

			if(x>interval[1] || current<last){ /*passed by the maximum value without noticing it*/
				/*prepare for a finer search*/
				step/=2;
				
				/*if step is too small, no solution could be found. Exit with error*/
				if(step<PRECISION){
					fprintf(stderr,"Err1: No solution could be found. Try increasing the aspect ratio.\n");
					return 1;
				}

				x=interval[0]-step; /*step will be added on the end of this iteration, so we must compensate for it*/
				last=-HUGE_VAL;
				continue;
			}
			last=current;
		}

#ifdef DEBUG		
		fprintf(stderr,"x=%lf, coefficient=%lf\n",x,current); /*DEBUG*/
#endif

		/*update parameters increasing the accuracy. Each in
		 * each iteration the accuracy doubles*/
		interval[0]=x-step;
		interval[1]=x;
		step=(interval[1]-interval[0])/2;
	}

	double a=(interval[0]+interval[1])/2;

	/*print results*/
	printf("a=(%lf+-%lf)cm\n",a,PRECISION/2);
	printf("b=%lfcm\n",ellipticalSpan(a,aspectRatio));
	printf("mass=%lfg\n",nfins*ellipticalVolume(a,ellipticalSpan(a,aspectRatio),t)*DENSITY);
	printf("t=%lf\n",t);
	printf("aspect ratio = %lf\n",aspectRatio);
	printf("stability coefficient = %lf\n",stabilityCoefficient(M0,CM0,CN0,Z0,length,t,aspectRatio, nfins, bodyRadius, a));
	printf("profile: NACA00%02.lf; maximum thickness: %lfcm\n",t*100,2*a*t);

	printf("\n");
}

/*stabilityCoefficient: returns the stability coefficient for a
 * elliptical wing with the paramenters provided. The wing is modelled
 * as a trapezoidal wing using ellipticalWing.h*/

double stabilityCoefficient(double M0, double CM0, double CN0, double Z0, double length, double t, double aspectRatio, int nfins, double bodyRadius, double a){

	/*center of pressure*/
	const double rootChord=ellipticalRootChord(a);
	const double tipChord=ellipticalTipChord(a);
	const double span=ellipticalSpan(a,aspectRatio);
	const double sweepAngle=0;
	double CNt,Zt,Z;
	
	if(a!=0){
		CNt=CNfins(nfins,aspectRatio,bodyRadius,rootChord,tipChord,span,sweepAngle);

		Zt=Zfin(length-2*a,rootChord,tipChord,(rootChord-tipChord)/2); 

		Z=(CN0 * Z0 + CNt * Zt)/(CN0+CNt);
	}else CNt=0,Zt=0,Z=Z0;

	/*center of mass*/
	double Mt=nfins*ellipticalVolume(a,span,t)*DENSITY;

	double CMt=length-a; /*considering that the center of mass of each fin 
			      * is in the middle of the chord. This is an
			      * approximation which results in a more
			      * conservative stability coefficient (i.e. it
			      * yields smaller stability coefficients)*/

	double CM=(CM0*M0+CMt*Mt)/(M0+Mt);

	/*stability coefficient*/
	return (Z-CM)/(2*bodyRadius);
}
