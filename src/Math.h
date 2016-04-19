/*
 * Math.h
 *
 *  Created on: 19 avr. 2016
 *      Author: ethel
 */

#ifndef SRC_MATH_H_
#define SRC_MATH_H_

#define _USE_MATH_DEFINES

#include <math.h>

/*
 * all the functions in Math.h are static defined
 * I want global functions to use in the project.
 */


class Math {
public:
	Math();
	virtual ~Math();

	static int radiansDegrees(int angleRadians);

	static int constraint(int angleDegre);

	static int normalizeDegree(int value);

	static double pitchDegreeToPWM(double degree);

	static double yawDegreeToPWM(double degree);

};

#endif /* SRC_MATH_H_ */
