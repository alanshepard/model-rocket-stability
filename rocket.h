/* 
 * rocket.h
 * 
 * Copyright (C) 2015,2016 Bernardo <b.b.monteiro@gmail.com>
 *
 * This file is released under the GPLv2
 */

#ifndef __ROCKET_H
#define __ROCKET_H

#include <iostream>
#include <ostream>
#include <map>

class Component{
	public:
	virtual ~Component(){}

	virtual double M() const=0; //mass
	virtual double CM() const=0; //center of mass
	virtual double CN() const=0; //normal force coefficient
	virtual double Z() const=0; //center of pressure
	virtual void print(std::ostream&) const;
	double x; //starting position, nose==0

};

class Bad_Range { };

class Rocket{

	public:
	double length;
	double diameter;

	std::map<std::string,Component*> part;
	typedef std::map<std::string,Component*>::const_iterator CI;
	
	Rocket(double ll, double dd){
		length = ll;
		diameter = dd;
	}

	//Rocket(FILE*); //loads rocket from file
	//Rocket(); //creates an empty rocket
	//~Rocket() {}

	friend std::ostream& operator<< (std::ostream&, const Rocket&);

	double l() const {return length;}
	double d() const {return diameter;}
	double M() const;
	double CM() const;
	double CN() const;
	double Z() const;
	double stabilityCoefficient() const {return (Z()-CM())/d();}
};

class Fins: public Component{
	public:
	Rocket* rocket; //rocket for reference diameter
	int n; //number of fins
	double rootChord;
	double AR; //aspectRatio
	double density;
	virtual double span() const=0;
};

class Tube: public Component{
	public:
	double length;
	double linDensity;
	
	Tube(ll,ld){length=ll; linDensity=ld;}

	double M() const {return length*linDensity;}
	double CM() const {return length/2.;}
	double CN() const {return 0.;}
	double Z() const {return 0.;}
};

//Part: general Component, user must insert data manually
class Part: public Component{
	public:
	double m;
	double cm;
	double cn;
	double z;

	double M() const {return m;}
	double CM() const {return cm;}
	double CN() const {return cn;}
	double Z() const {return z;}
};

class Ogive: public Component{
	public:
	double m;
	double cm;
	double volume;
	double area; //base area
	double length;

	Ogive(double mass, double centerOfMass, double vv, double aa, double ll){
		x = 0.;
		m = mass;
		cm = centerOfMass;
		volume = vv;
		area = aa;
		length = ll;
	}

	double M() const {return m;}
	double CM() const {return cm;}
	double CN() const {return 2.0;}
	double Z() const {return length-(volume/area);}
};


//optmizeFins: optimizes rootChord of find to achive the stability
//coefficient c. Fins must be in r.
int optimizeFins(Rocket* r, Fins* fins, double c);
class Did_Not_Converge {};
class Bad_Algorithm {};

inline std::ostream& operator<< (std::ostream& o, const Component& c){
	  c.print(o); // delegate the work to a polymorphic member function.
	    return o;
}

#endif //__ROCKET_H
