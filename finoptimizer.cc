#include "rocket.h"
#include <limits>
#include <cmath>

//fins must be in r. c is the goal stability coefficient
int optimizeFins(Rocket* r, Fins* fins, double c){
	//solve for r.stabilityCoefficient()-c==0, changing
	//fins.rootChord.
	std::string algorithm="pegasus";

	const int max_iter = 100;
	const double precision = 2*r->d()*std::numeric_limits<double>::epsilon();

	double a = 0.;
	double b = r->l()/2;

	fins->rootChord = a;
	double fa = r->stabilityCoefficient()-c;
	std::cout<<"fa="<<fa<<"\n";

	fins->rootChord = b;
	double fb = r->stabilityCoefficient()-c;
	std::cout<<"fb="<<fb<<"\n";
	
	double next;
	double fnext=std::numeric_limits<double>::infinity();
	int i=0;

	if(algorithm=="pegasus"){
		std::cout<<"got here!\n";
		while(fabs(fnext)>precision && fabs((a-b)/2)>precision && i++ <=max_iter){
			next = a-fa*(b-a)/(fb-fa);
			fins->rootChord = next;
			fnext = r->stabilityCoefficient()-c;

			std::cout<<i<<":"<<next<<","<<fnext<<"\n";
		
			if(fnext*fa < 0.){
				b = next;
				fb = fnext;
			}else if(fnext*fa > 0.){
				fb = fb*fa/(fa+fnext);
			}else break;
		}

	}else if(algorithm=="bissection"){
		while(fabs(fnext)>precision && fabs((a-b)/2)>precision && i++ <=max_iter){
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
	}else throw Bad_Algorithm();


	if(i>max_iter)
		throw Did_Not_Converge();

	return i;
}
