/*
 * LeapEventListener.cpp
 *
 *  Created on: 9 avr. 2016
 *      Author: ethel
 */

#include "LeapEventListener.h"

LeapEventListener::LeapEventListener(): send_msg(false), _pitch(0), _yaw(0){
	// TODO Auto-generated constructor stub
	_client.init_connection();


}

LeapEventListener::~LeapEventListener() {
	// TODO Auto-generated destructor stub
	_vec.clear();
}

const std::string fingerNames[] = {"Thumb", "Index", "Middle", "Ring", "Pinky"};
const std::string boneNames[] = {"Metacarpal", "Proximal", "Middle", "Distal"};
const std::string stateNames[] = {"STATE_INVALID", "STATE_START", "STATE_UPDATE", "STATE_END"};


int radian_to_degree(int  ENTER) {
	double Pi = 3.14159265;
	int degrees = (ENTER * 180) / Pi;
	return degrees;
}

/**
 * Force a value to be between 0 and 180 degrees for servo
 * @param value degree value returned by Leap Controller
 * @return normalized value between 0-180
 */
int normalizeDegree(int value){
	value = (value > 90)  ? 90  : value;
	value = (value < -90) ? -90 : value;
	return value+90;
}

/**
 * Get a PWM value from degree closely modeled by a quadratic equation
 * @param degree pitch degree value
 * @return PWM value
 */
static double pitchDegreeToPWM(double degree){
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
static double yawDegreeToPWM(double degree){
	double a = 0.0;
	double b = 3.19444444;
	double c = 150;
	return a*(degree*degree) + b*degree + c;
}


void LeapEventListener::onConnect(const Controller& controller) {
	std::cout << "Connected" << std::endl;
	// Enable gestures, set Config values:

	controller.enableGesture(Gesture::TYPE_SWIPE);
	controller.enableGesture(Gesture::TYPE_CIRCLE);
	controller.enableGesture(Gesture::TYPE_KEY_TAP);
	controller.enableGesture(Gesture::TYPE_SCREEN_TAP);

	controller.config().setFloat("Gesture.Swipe.MinLength", 200.0);
	controller.config().save();
}

//Not dispatched when running in a debugger
void LeapEventListener::onDisconnect(const Controller& controller) {
	std::cout << "Disconnected" << std::endl;
}

void LeapEventListener::onFrame(const Controller& controller) {

	Frame frame = controller.frame();

	std::string msg =this->constructJSON(frame);
	_client.send_message(msg.c_str(), "/tmp");//envoie des donnees brutes.
	//_client.send_message("json_instruction", "/instructions");

}

std::string LeapEventListener::constructJSON(Frame& frame){

	Message_s msg;

	JsonObj obj;

	HandList hands = frame.hands();
	const Hand hand = hands[0];//pour le moment je ne gère qu'une main a la fois.
	std::string handType = hand.isLeft() ? "Left hand" : "Right hand";
	msg.handType = handType;

	const Vector normal = hand.palmNormal();
	float fps = frame.currentFramesPerSecond();

	std::string x = boost::lexical_cast<std::string>(normal.x);
	std::string y = boost::lexical_cast<std::string>(normal.y);
	std::string z = boost::lexical_cast<std::string>(normal.z);

	msg.xp=x;
	msg.yp=y;
	msg.zp=z;

	const Vector direction = hand.direction();

	std::string x1 = boost::lexical_cast<std::string>(direction.x);
	std::string y1 = boost::lexical_cast<std::string>(direction.y);
	std::string z1 = boost::lexical_cast<std::string>(direction.z);
	std::string fp = boost::lexical_cast<std::string>(fps);

	msg.xd=x1;
	msg.yd=y1;
	msg.zd=z1;
	msg.fps=fp;

	std::string result2 = obj.toJson(msg);

	return result2;
}


