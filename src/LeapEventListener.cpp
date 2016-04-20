/*
 * LeapEventListener.cpp
 *
 *  Created on: 9 avr. 2016
 *      Author: ethel
 */

#include "LeapEventListener.h"


LeapEventListener::LeapEventListener(): send_msg(false), _pitch(0), _yaw(0),oldRightYaw(0),oldRightPitch(0),oldLeftYaw(0),oldLeftPitch(0){
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

	std::string handtype;//a voir a quoi ca peut servir
	Frame frame = controller.frame();
	//we begin to test the handtype

	/*
	for (Hand hand : frame.hands()) {

		if (hand.isLeft()) {
			handtype = "left";
			handleHand(hand);
		} else {
			handtype = "right";
			handleHand(hand);
		}

	}
	 */

	for(Gesture gesture : frame.gestures()){
		switch (gesture.type()) {
		case gesture.TYPE_CIRCLE:

		handleCircle(gesture);
		//handleCircle ==> envoyer dans channel "/type_circle"

		break;
		case gesture.TYPE_SWIPE:

		handleSwipe(gesture);
		//handSwipe (determinate the sense) and send in channel "/type_swipe"
		default:
			break;
		}

	}

	//std::string msg =this->constructJSON(frame);
	//_client.send_message(msg.c_str(), "/tmp");//envoie des donnees brutes.

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

void LeapEventListener::handleHand(Hand& hand){
	bool isLeft   = hand.isLeft();
	std::string handType  = (isLeft) ? "left" : "right";

	Vector direction = hand.direction();
	_yaw = Math::radiansDegrees(direction.yaw());
	_pitch = Math::radiansDegrees(direction.pitch());

	// Normalize Yaw and Pitch
	_yaw    = Math::constraint(_yaw);
	_pitch *= (isLeft) ? -1 : 1;
	_pitch  = Math::constraint(_pitch);

	// Get PWM Values
	_yaw   = (int) Math::yawDegreeToPWM(_yaw);
	_pitch = (int) Math::pitchDegreeToPWM(_pitch);


	int oldYaw    = (isLeft) ? oldLeftYaw   : oldRightYaw;
	int oldPitch  = (isLeft) ? oldLeftPitch : oldRightPitch;
	if( (fabs((double)(oldPitch - _pitch) > 5))  || (fabs((double)(oldYaw - _yaw) > 5) )) {


		//_jsonObj.put(_yaw, ); //acces au ptree?
		/*
		payload.put(handType + "yaw",   _yaw);
		payload.put(handType + "pitch", _pitch);
		 */
		if (isLeft) {
			oldLeftYaw   = _yaw;
			oldLeftPitch = _pitch;
		} else {
			oldRightYaw   = _yaw;
			oldRightPitch = _pitch;
		}
	}
	else{
		/*
		payload.put(handType + "_yaw", oldYaw);
		payload.put(handType + "_pitch", oldPitch);
		 */
	}

	//return payload;
}

void LeapEventListener::handleCircle(Gesture& gesture){
	if(gesture.state()==gesture.STATE_STOP){//if the movement is finished
		_client.send_message("1", "/gesture/type_circle");// modify message later...
	}
}

void LeapEventListener::handleSwipe(Gesture& gesture){
	if(gesture.state()==gesture.STATE_STOP){
		_client.send_message("1", "/gesture/type_swipe");// modify message later...
	}
}

