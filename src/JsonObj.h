/*
 * JsonObj.h
 *
 *  Created on: 9 avr. 2016
 *      Author: ethel
 */

#ifndef SRC_JSONOBJ_H_
#define SRC_JSONOBJ_H_

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/detail/json_parser_error.hpp>
#include <boost/property_tree/detail/json_parser/read.hpp>
#include <boost/property_tree/detail/json_parser_write.hpp>

#include <boost/property_tree/json_parser.hpp>

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


class JsonObj {
public:
	JsonObj();
	virtual ~JsonObj();
	std::string example();
	std::string toJson(Message_s& data);


	std::string stringify();// in order to send the JSON trough the websocket as a string


	std::vector< std::pair<std::string, std::string> > _handsVector;
	std::vector< std::pair<std::string, std::string> > _fingersVector;

};

#endif /* SRC_JSONOBJ_H_ */
