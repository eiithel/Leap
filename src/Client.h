/*
 * Client.h
 *
 *  Created on: 9 avr. 2016
 *      Author: ethel
 */

#ifndef CLIENT_H_
#define CLIENT_H_

#include <iostream>
#include <mosquitto.h>
#include <stdio.h>
#include <stdint.h>
#include <cstring>
#include "JsonObj.h"


class Client {
public:
	Client();
	virtual ~Client();

	char _id[30];
	char *_host;
	int _port;
	int _keepalive;
	bool _clean_session;
	struct mosquitto *_mosq;

	int init_connection();
	bool send_message(const  char * message, const char *topic);
	bool send_Json(const  JsonObj * json);


private:


};

#endif /* CLIENT_H_ */
