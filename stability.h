/*stability.h*/
/*This library contains functions to calculate the stability of model rockets*/

#ifndef STABILITY_LIB
#define STABILITY_LIB

/*Barowman method*/

/*CNfin_nointerference: Calculates the normal force coeficient of a set of n fins (n=3,4), without accounting for body interference*/
double CNfins_nointerference(int n, double aspectRatio, double referenceRadius, double rootChord, double tipChord, double span, double sweepAngle){

	return (n*aspectRatio*(rootChord+tipChord)/(2*referenceRadius)*span/referenceRadius)/(2+sqrt(4+pow(aspectRatio/cos(sweepAngle),2)));
}

/*interferenceCoeficient: calculates the interference coeficient for the set of fins.*/
double interferenceCoeficient(double span, double bodyRadius){
	return 1+bodyRadius/(span+bodyRadius);
}

/*CNfins: Calculates the normal force coeficient of a set of n fins (n=3,4), accounting for body interference.*/
double CNfins(int n, double aspectRatio, double bodyRadius, double rootChord, double tipChord, double span, double sweepAngle){
	return interferenceCoeficient(span,bodyRadius)*CNfins_nointerference(n,aspectRatio,bodyRadius,rootChord,tipChord,span,sweepAngle);
}

/*Zfin: returns the center of pressure for a set of fins with the given
 * paramenters. chordDisplacement is the longitudinal distance between
 * the leading edge of fin root and the leading edge of fin tip*/
double Zfin(double finStart, double rootChord, double tipChord, double chordDisplacement){
	return finStart+chordDisplacement/3*((rootChord+2*tipChord)/(rootChord+tipChord))+1/6*(rootChord+tipChord-rootChord*tipChord/(rootChord+tipChord));
}

#endif
