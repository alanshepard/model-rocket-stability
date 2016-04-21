#include "rocket.h"
#include "ellipticalfins.h"
#include "dpe-common.h"

int main(){
	Ogive ogiveC=parabola; //select ogive
	//Part payload(ogiveC.X_f(), 2.3+6.0+1.8); //altimetro+baterias+encaixe
	Part payload(ogiveC.X_f(), micropeakMass); //micropeak
	Tube tubeC(19.7, ogiveC.X_f(), tubeLinDensity);
	Engine engineC = bandeiranteC_ejection;

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

	optimizeFins(&dpeC, &f, 1);

	std::cout<<f;
}
