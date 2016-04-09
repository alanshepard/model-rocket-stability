#include "rocket.h"
#include "ellipticalfins.h"
#include "dpe-common.h"

int main(){
	Ogive ogiveC=parabola; //select ogive
	Part payload(ogiveC.X_f(), 2.3+6.0+1.8); //atimetro+baterias+encaixe
	Tube tubeC(19.7, ogiveC.X_f(), tubeLinDensity);
	Engine engineC = bandeiranteB;

	Rocket dpeC(tubeC.X_f(),1.8);
	engineC.rocket=&dpeC;

	FlatEllipticalFins f;
	f.n = 3;
	f.t = 0.;
	f.AR = 1.5;
	f.density = 0.;
	f.rocket=&dpeC;

	dpeC.part["ogive"] = &ogiveC;
	dpeC.part["payload"] = &payload;
	dpeC.part["tube"] = &tubeC;
	dpeC.part["fins"] = &f;
	dpeC.part["engine"] = &engineC;
	
	std::cout<<dpeC;

	optimizeFins(&dpeC, &f, 1.0);

	std::cout<<f;
}
