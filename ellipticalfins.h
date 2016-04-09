/* 
 * ellipticalstability.h
 * 
 * Copyright (C) 2015,2016 Bernardo <b.b.monteiro@gmail.com>
 *
 * This file is released under the GPLv2
 */

#ifndef __ELLIPTICALFINS_H
#define __ELLIPTICALFINS_H

#include "rocket.h"
#include <cmath>

class EllipticalFins: public Fins{
	public:
	double CN() const;
	double Z() const {return rootChord*.2887793409211;}
	double CM() const {return rootChord/2.;}
	double span() const {return rootChord*AR*M_PI/4;}
};

class NACAEllipticalFins: public EllipticalFins{
	public:
	double t; //maximum thickness, in percentage of rootChord
	double M() const {return density*1.826888*t*rootChord/2*rootChord/2*span();}
};

class FlatEllipticalFins: public EllipticalFins{
	public:
	double t; //thickness
	double M() const {return density*t*AR*rootChord*rootChord;}
};

#endif //__ELLIPTICALFINS_H
