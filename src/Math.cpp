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
