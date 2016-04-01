#include "ellipticalstability.h"

double CNfins(int n, double aspectRatio, double referenceDiameter, double rootChord, double span){

	double CN = (M_PI*n*aspectRatio*(span*rootChord)/(pow(referenceDiameter,2)))/(2+sqrt(4+pow(aspectRatio,2)));

	const double t=(span+referenceDiameter/2)/(referenceDiameter/2);

	CN *= 2/(M_PI*pow(1-1/t,2))*((1+pow(t,-4)*0.5*atan(0.5*(t-1/t)))-pow(t,-2)*((t-1/t)+2*atan(1/t)));
	return CN;
}

double Zfin(double rootChord){
	return rootChord*(1/2-2/(3*M_PI));
}

double stabilityCoefficient(double density, double M0, double CM0, double CN0, double Z0, double length, double t, double aspectRatio, int nfins, double bodyDiameter, double rootChord){

	/*center of pressure*/
	const double span=rootChord*aspectRatio*M_PI/4;
	double CNt,Zt,Z;
	
	if(rootChord!=0){
		CNt=CNfins(nfins,aspectRatio,bodyDiameter,rootChord,span);

		Zt=length-rootChord + Zfin(rootChord); 

		Z=(CN0 * Z0 + CNt * Zt)/(CN0+CNt);
	}else CNt=0,Zt=0,Z=Z0;

	/*center of mass*/
	double Mt=nfins*finVolumeNACA(rootChord,span,t)*density;

	double CMt=length-rootChord/2; /* considering that the center of mass of
					* each fin is in the middle of the
					* chord. This is an approximation which
					* results in a more conservative
					* stability coefficient (i.e. it yields
					* smaller stability coefficients)*/

	double CM=(CM0*M0+CMt*Mt)/(M0+Mt);

	/*stability coefficient*/
	return (Z-CM)/(bodyDiameter);
}

double finVolumeNACA(double rootChord, double span, double t){
	 return 1.826888*t*rootChord/2*rootChord/2*span;
 }
