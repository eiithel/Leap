/*
 * LeapEventListener.h
 *
 *  Created on: 9 avr. 2016
 *      Author: ethel
 */

#ifndef SRC_LEAPEVENTLISTENER_H_
#define SRC_LEAPEVENTLISTENER_H_

#include <iostream>
#include "Leap.h"
#include "LeapMath.h"
#include <vector>
#include <math.h>
#include "Client.h"
#include "JsonObj.h"
#include <boost/lexical_cast.hpp>

#include "Math.h"
#include "Uart.h"


using namespace Leap;

class LeapEventListener : public Listener {
public:
	LeapEventListener();
	virtual ~LeapEventListener();
	virtual void onConnect(const Controller&);
	virtual void onDisconnect(const Controller&);
	virtual void onFrame(const Controller&);
	std::string constructJSON(Frame& frame);
	void handleHand(Hand& hand);


	std::vector<Frame> _vec;
	bool send_msg;
	std::string _str;
	int _pitch;
	int _yaw;
	int oldRightYaw,oldRightPitch,oldLeftYaw,oldLeftPitch;
	Client _client;
	JsonObj _jsonObj;
	Uart _arduino;

};

#endif /* SRC_LEAPEVENTLISTENER_H_ */
