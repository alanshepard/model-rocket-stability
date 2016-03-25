/* 
 * rocketinfo.h
 * 
 * Copyright (C) 2015 Bernardo <b.b.monteiro@gmail.com>
 *
 * This file is released under the GPLv2
 */


/*List of symbols: 
 * M0: rocket's mass without fins;
 * CM0: rocket's center of mass without fins. Origin is on the tip of the nose;
 * CN0: rocket's normal force coefficient without fins;
 * Z0: rocket's center of pressure without fins;
 * diameter: rocket's diameter;
 * length: rocket's length;
 * t: fin's profile maximum thickness in relation to the chord;
 * aspectRatio: desired aspect ratio for the fins.
 */


#include <stdio.h>
enum field {M0,CM0,CN0,Z0,DIAMETER,LENGTH};


