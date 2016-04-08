#include "ellipticalfins.h"

double EllipticalFins::CN() const{
	if(fabs(rootChord)<1e-7)
		return 0.;

	double cn = (M_PI * n * AR * (span()*rootChord) /
			(pow(rocket->d(),2))) /
		(2+sqrt(4+pow(AR,2)));
	
	//interference
	const double tau = (span()+rocket->d()/2) / (rocket->d()/2);

	cn *= 2/(M_PI*pow(1-1/tau,2)) *
		((1+pow(tau,-4)*0.5*atan(0.5*(tau-1/tau))) - pow(tau,-2) *
		 ((tau-1/tau)+2*atan(1/tau)));
	return cn;
}
