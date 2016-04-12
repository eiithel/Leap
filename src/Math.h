/*
 * Math.h
 *
 *  Created on: 12 avr. 2016
 *      Author: ethel
 */

#ifndef SRC_MATH_H_
#define SRC_MATH_H_
#define _USE_MATH_DEFINES

#include <math.h>


int radiansToDegrees(int angleRadians){
	return (angleRadians * 180.0 / M_PI);
}

int constrainAngle(int angleDegre){
	angleDegre = fmod(angleDegre + 180,360);
    if (angleDegre < 0)
    	angleDegre += 360;
    return angleDegre - 180;
}

#endif /* SRC_MATH_H_ */
