/* 
 * rocketinfo.h
 * 
 * Copyright (C) 2015 Bernardo <b.b.monteiro@gmail.com>
 *
 * This file is released under the GPLv2
 */

#ifndef __ROCKETINFO_H
#define __ROCKETINFO_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_COMPONENTS 10
#define MAX_NAME 10

typedef struct {
	int ncomponents;
	double length;
	double diameter;
	char* description[MAX_COMPONENTS];
	double m[MAX_COMPONENTS]; /*mass of each component*/
	double CM[MAX_COMPONENTS]; /*center of mass of each component*/
	double CN_alpha[MAX_COMPONENTS]; /*CN_alpha of each component*/
	double Z[MAX_COMPONENTS]; /*center of pressure of each component*/
}Rocket;

Rocket* getRocket (FILE* rocketFile);
void printRocket(const Rocket* rocket, FILE* rocketFile);

#endif //__ROCKETINFO_H
