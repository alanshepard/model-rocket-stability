/*ellipticalWing.h*/
/*This library is used to model an elipitical wing with a NACA four-series
 * profile to a trapezoidal wing to which the Barrowman method may be
 * applied.*/

#ifndef ELLIPTICALWING_H
#define ELLIPTICALWING_H
#include <math.h>

/*t is the maximum thickness of the profile in relation to the chord.*/

/*a is the larger semi-axis of the ellipse, b is the smaller semi-axis of the
 * ellipses.*/

/*Some constants are used without explanation. For an explanation, please refer
 * to the author notes*/

/*TAPERRATIO: tipChord/rootChord of the trapezoid which best approximates an
 * ellipse.*/
#define TAPERRATIO 0.340287364086 

double ellipticalRootChord(double a){
	return a*M_PI/(1+TAPERRATIO);
}

double ellipticalTipChord(double a){
	return TAPERRATIO*ellipticalRootChord(a);
}

double ellipticalVolume(double a,double b,double t){
	return 1.826888*t*a*a*b;
}

double ellipticalSpan(double a, double aspectRatio){
	return aspectRatio*a*M_PI/2;
}


#endif
