/* 
 * rocket.h
 * 
 * Copyright (C) 2015 Bernardo <b.b.monteiro@gmail.com>
 *
 * This file is released under the GPLv2
 */

#ifndef __ROCKET_H
#define __ROCKET_H

#include <iostream>
#include <map>

class Component{
	public:
	virtual double m() const; //mass
	virtual double CM() const; //center of mass
	virtual double CN() const; //normal force coefficient
	virtual double Z() const; //center of pressure
};

class RocketComponent: public Component {
	public:
	double x; //starting position, nose==0

	friend std::ostream& operator<< (std::ostream&, const RocketComponent&);
};

class Rocket{
	private:
	double length;
	double diameter;
	std::map<std::string,RocketComponent> part;

	public:
	Rocket(FILE*); //loads rocket from file
	explicit Rocket(int n); //creates an empty rocket with n components
	~Rocket() {}

	Rocket& add(const Component&); //add Component

	friend std::ostream& operator<< (std::ostream&, const Rocket&);

	double& l() {return length;}
	double& d() {return diameter;}
	double m() const;
	double CM() const;
	double CN() const;
	double Z() const;
	double stabilityCoefficient() const {return (Z()-CM())/d;}
};

class Fins: public Component{
	public:
	int n; //number of fins
	double rootChord;
	double AR; //aspectRatio
	double density;
};

class Tube: public Component{
	public:
	double length;
	double linDensity;

	double m() {return length*linDensity;}
	double CM() {return length/2.;}
	double CN() {return 0.;}
	double Z() {return 0.;}
};

//Part: general Component, user must insert data manually
class Part: public Component{
	public
	double mass;
	double cm;
	double cn;
	double z;

	double m() {return mass;}
	double CM() {return cm;}
	double CN() {return cn;}
	double Z() {return z;}
};

class DidNotConverge {}

//optmizeFins: optimizes rootChord of find to achive the stability
//coefficient c. Fins must be in r.
void optimizeFins(Rocket* r, Fins* fins, double c);

#endif //__ROCKET_H
