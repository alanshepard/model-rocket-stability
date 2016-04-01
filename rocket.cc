#include "rocket.h"

double Rocket::m() const{
	double sum = 0;
	for (int i=0; i<nparts; i++)
		sum += part[i].m();
	
	return sum;
}

double Rocket::CM() const{
	double moment = 0;
	for (int i=0; i<nparts; i++)
		moment += (x+part[i].CM()) * part[i].m();

	return moment/m();

double Rocket::CN() const{
	double sum = 0.;
	for (int i=0; i<nparts; i++)
		sum += part[i].CN();
	
	return sum;
}


double Rocket::Z() const{
	double moment = 0.;
	for (int i=0; i<nparts; i++)
		moment += (x+part[i].Z()) * part[i].CN();

	return moment/CN();
}
