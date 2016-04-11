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



using namespace Leap;


struct Message_s
{
	std::string handType;
	//palmNormal vector
	std::string xp;
	std::string yp;
	std::string zp;

	//direction vector
	std::string xd;
	std::string yd;
	std::string zd;

	std::string fps;
};

typedef struct Message_s Message_s;


class LeapEventListener : public Listener {
public:
	LeapEventListener();
	virtual ~LeapEventListener();
	virtual void onConnect(const Controller&);
	virtual void onDisconnect(const Controller&);
	virtual void onFrame(const Controller&);
	std::string constructJSON(Frame& frame);


	std::vector<Frame> _vec;
	bool send_msg;
	std::string _str;
	int _pitch;
	int _yaw;
	Client _client;
	JsonObj _jsonObj;


};

#endif /* SRC_LEAPEVENTLISTENER_H_ */
