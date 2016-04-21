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
#include "Uart.h"
#include "signal.h"

using namespace std;

volatile bool stop = false;

void signalHandler( int signum )
{
	std::cout << "Interrupt signal (" << signum << ") received.\n";
	stop = true;
	exit(0);

}



int main(int argc, char *argv[])
{

	if ((argc > 1 && strcmp(argv[1], "-h") == 0) || (argc > 1 && strcmp(argv[1], "--help") == 0)){
		std::cout << "Usage: mqtt [OPTION...] hello world " << std::endl;
		exit(0);
	}

	signal(SIGINT, signalHandler); // if the user interrupts the process ctrl+C
	signal(SIGTERM, signalHandler);// if the user kills the process


	Controller controller;// start a new thread
	LeapEventListener listener;
	Client client = listener._client;

	controller.addListener(listener);

	while(!stop){

		while(!mosquitto_loop(client._mosq, -1, 1)){
		}
	}


	printf("exit\n");

	return 0;
}





