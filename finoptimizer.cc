/* 
 * ellipticalstability.h
 * 
 * Copyright (C) 2015,2016 Bernardo <b.b.monteiro@gmail.com>
 *
 * This file is released under the GPLv2
 */

#include "rocket.h"
#include <limits>
#include <cmath>

//fins must be in r. c is the goal stability coefficient
int optimizeFins(Rocket* r, Fins* fins, double c){
	//solve for r.stabilityCoefficient()-c==0, changing
	//fins.rootChord.
	std::string algorithm="pegasus";
	
	std::cout<<"\n#### FIN OPTIMIZER ####\n";
	std::cout<<"Using algorithm "<<algorithm<<"\n";

	const int max_iter = 500;
	const int max_pre_iter = 16; //maximum iterations to define interval
	const double precision = 1e-7;//micrometers precision

	double a = 0.;

	fins->rootChord = a;
	double fa = r->stabilityCoefficient()-c;
	std::cout<<"a="<<a<<" "<<"fa="<<fa<<"\n";

	//Get b
	double b=0;
	double fb;
	int i=0;
	do{
		b = (i+1)*(r->l()-r->CM())/max_pre_iter;
		fins->rootChord = b;
		fb = r->stabilityCoefficient()-c;
		std::cout<<i+1<<": "<<"b="<<b<<" "<<"fb="<<fb<<"\n";
	}while(fa*fb>0 && i++<max_pre_iter);

	if(fa*fb>0){
		std::cerr<<"Err: function does not changes sign\n";
		throw Did_Not_Converge();
	}
	
	double next;
	double fnext=std::numeric_limits<double>::infinity();
	i=0;

	if(algorithm == "pegasus"){
		std::cout<<"i: x        err\n";
		while(fabs(fnext)>precision && fabs((a-b)/2)>precision && ++i <=max_iter){
			next = a-fa*(b-a)/(fb-fa);
			fins->rootChord = next;
			fnext = r->stabilityCoefficient()-c;

			std::cout<<i<<": "<<next<<", "<<fnext<<"\n";
		
			if(fnext*fa < 0.){
				b = next;
				fb = fnext;
			}else if(fnext*fa > 0.){
				fb = fb*fa/(fa+fnext);
			}else break;
		}
	}else if(algorithm == "bissection"){
		while((fabs(fnext)>precision || fabs((a-b)/2)>precision) && ++i <=max_iter){
			next = (a+b)/2;
			fins->rootChord = next;
			fnext = r->stabilityCoefficient()-c;

			std::cout<<i<<":"<<"["<<a<<","<<b<<"] ["<<fa<<","<<fb<<"] "<<next<<","<<fnext<<"\n";
			if(fnext*fa < 0.){
				b = next;
				fb = fnext;
			}else if(fnext*fa > 0.){
				a = next;
				fa = fnext;
			}else break;
		}
	}else 
		throw Bad_Algorithm();

	if(i>max_iter){
		std::cerr<<"Err: did not converge\n";
		throw Did_Not_Converge();
	}

	std::cout<<"#### DONE! Fins optimized ####\n\n";

	return i;
}
