/* 
 * ellipticalstability.h
 * 
 * Copyright (C) 2015,2016 Bernardo <b.b.monteiro@gmail.com>
 *
 * This file is released under the GPLv2
 */

#include "rocket.h"
#include "ellipticalfins.h"
#include <iostream>

int main(){

	std::cout<<"building rocket...\n";
	Rocket r;
	r.length = 30.;
	r.diameter = 2.;

	Part rocketNoFins(0,46.7, 18.08348, 2, 1.76148, 30.0);

	NACAEllipticalFins f;
	f.n = 3;
	f.t = 0.12;
	f.AR = 1.5;
	f.density = 1.25;
	f.rocket=&r;

	r.part["Rocket Without Fins"] = &rocketNoFins;
	r.part["Fins"] = &f;

	std::cout<<r;

#if 0
	for(double d=0; d<r.l();d+=0.5){
		f.rootChord=d;
		std::cout<<d<<"\t"<<f.CN()<<"\t";
		std::cout<<r.stabilityCoefficient()<<"\n";
	}
#endif

	std::cout<<optimizeFins(&r, &f, 1.)<<"\n";
	
	std::cout<<"cof: "<<r.stabilityCoefficient()<<"\n";

	std::cout<<f;

}
