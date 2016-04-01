#ifndef __ELLIPTICALFINS_H
#define __ELLIPTICALFINS_H

#include "rocket.h"

class EllipticalFins: public Fins{
	public:
	double CN();
	double Z();
	double span();

	//Automatically calculates an elliptical set of fins to get the right stability coefficient
	EllipticalFins(const Rocket&, double stabilityCoefficient, Fins baseFins);
};

class NACAEllipticalFins: public EllipticalFins{
	public:
	double t; //maximum thickness, in percentage of rootChord
	double m();
	double CM();
};

class FlatEllipticalFins: public EllipticalFins{
	public:
	double t; //thickness
	double m();
	double CM();
};

#endif //__ELLIPTICALFINS_H
