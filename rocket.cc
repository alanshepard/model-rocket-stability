/* 
 * rocket.h
 * 
 * Copyright (C) 2015,2016 Bernardo <b.b.monteiro@gmail.com>
 *
 * This file is released under the GPLv2
 */

#include "rocket.h"

double Rocket::M() const{
	double sum = 0.;
	for (CI p=part.begin(); p!=part.end(); p++)
		sum += p->second->M();
	
//	if(sum<0)
//		throw Bad_Range();

	return sum;
}

double Rocket::CM() const{
	double moment = 0.;
	for (CI p=part.begin(); p!=part.end(); p++)
		moment += (p->second->x - p->second->CM()) * p->second->M();

//	if(moment<0)
//		throw Bad_Range();

	return moment/M();
}

double Rocket::CN() const{
	double sum = 0.;
	for (CI p=part.begin(); p!=part.end(); p++)
		sum += p->second->CN();
	
//	if(sum<0)
//		throw Bad_Range();

	return sum;
}


double Rocket::Z() const{
	double moment = 0.;
	for (CI p=part.begin(); p!=part.end(); p++)
		moment += (p->second->x - p->second->Z()) * p->second->CN();

//	if(moment<0)
//		throw Bad_Range();

	return moment/CN();
}

std::ostream& operator<< (std::ostream& o, const Rocket& r){
	o<<"l: " <<r.l() <<"\n";
	o<<"d: " <<r.d() <<"\n";
	o<<"m: " <<r.M() <<"\n";
	o<<"CM: "<<r.CM()<<"\n";
	o<<"CN: "<<r.CN()<<"\n";
	o<<"Z: " <<r.Z() <<"\n";
	o<<"Stability Coefficient: "<<r.stabilityCoefficient()<<"\n";

	for(Rocket::CI p=r.part.begin(); p!=r.part.end(); p++){
		o<<"#"<<p->first<<"\n";
		o<<*(p->second)<<"\n";
	}

	o<<"Stability Coefficient: "<<r.stabilityCoefficient()<<"\n";

	return o;
}

void Component::print(std::ostream& o) const{
	o<<"x: " <<x   <<"\n";
	o<<"m: " <<M() <<"\n";
	o<<"CM: "<<CM()<<"\n";
	o<<"CN: "<<CN()<<"\n";
	o<<"Z: " <<Z() <<"\n";
}
