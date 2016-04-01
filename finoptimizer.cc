#include "rocket.h"

//fins must be in r. c is the goal stability coefficient
void optimizeFins(Rocket* r, Fins* fins, double c){
	//solve for r.stabilityCoefficient()-c==0, changing
	//fins.rootChord. Implementation of the Pegasus algorithm
	const int max_iter = 300;
	const double precision = 1e-6;

	double a = 0;
	double b = r->l()/2

	fins->rootChord = a
	double fa = r->stabilityCoefficient()-c;

	fins->rootChord = b;
	double fb = r->stabilityCoefficient()-c;
	
	double next = a-fb*(b-a)/(fb-fa);
	fins->rootChord = next;
	double fnext = r->stabilityCoefficient()-c;
	
	int i=0;
	while((b-a)/2<precision && i++ <=max_iter){
		fins->rootChord = next;
		fnext = r->stabilityCoefficient()-c;

		if(fnext*fb < 0.){
			a = next;
			fa = fnext;
		}else if(fnext*fb > 0.){
			fa = fa*fb/(fb+fnext);
		}else break;
	}

	if(i>max_iter)
		throw DidNotConverge();

	fins->rootChord = (b+a)/2.
}
