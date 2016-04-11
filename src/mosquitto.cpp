//============================================================================
// Name        : mosquitto.cpp
// Author      : eiithel
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <cstring>
#include <iostream>


#include <vector>
#include "Client.h"
#include "LeapEventListener.h"
#include <boost/lexical_cast.hpp>

using namespace std;


int main(int argc, char *argv[])
{

	if ((argc > 1 && strcmp(argv[1], "-h") == 0) || (argc > 1 && strcmp(argv[1], "--help") == 0)){
		std::cout << "Usage: mqtt [OPTION...] " << std::endl;
		exit(0);
	}


	Controller controller;// start a new thread
	LeapEventListener listener;
	Client client = listener._client;

	controller.addListener(listener);

	while(!mosquitto_loop(client._mosq, -1, 1)){
	}

	return 0;
}





