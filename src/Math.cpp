/*
 * Math.cpp
 *
 *  Created on: 19 avr. 2016
 *      Author: ethel
 */

#include "Math.h"

Math::Math() {
	// TODO Auto-generated constructor stub

}

Math::~Math() {
	// TODO Auto-generated destructor stub
}

int Math::radiansDegrees(int angleRadians){
	return (angleRadians * 180.0 / M_PI);
}

int Math::constraint(int angleDegre){
	angleDegre = fmod(angleDegre + 180,360);
	if (angleDegre < 0)
		angleDegre += 360;
	return angleDegre - 180;
}

/**
 * Force a value to be between 0 and 180 degrees for servo
 * @param value degree value returned by Leap Controller
 * @return normalized value between 0-180
 */
int Math::normalizeDegree(int value){
	value = (value > 90)  ? 90  : value;
	value = (value < -90) ? -90 : value;
	return value+90;
}

double Math::pitchDegreeToPWM(double degree){
	double a = 0.00061728395;
	double b = 2.38888888889;
	double c = 150;
	return a*(degree*degree) + b*degree + c;
}

/**
 * Get a PWM value from degree closely modeled by a quadratic equation
 * @param degree pitch degree value
 * @return PWM value
 */
double Math::yawDegreeToPWM(double degree){
	double a = 0.0;
	double b = 3.19444444;
	double c = 150;
	return a*(degree*degree) + b*degree + c;
}

