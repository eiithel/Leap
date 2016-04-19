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

using boost::property_tree::ptree;


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

struct Payload_s
{
	ptree pt;
	ptree children;

	ptree palmPosition, direction, type;
	ptree v1palm,v2palm,v3palm;
	ptree v1dir, v2dir, v3dir;
};

typedef struct Payload_s Payload_s;

struct yp_s
{
	ptree pt;
	ptree children;

	ptree yaw;
	ptree pitch;
};

typedef struct yp_s yp_s;


class JsonObj {
public:
	JsonObj();
	virtual ~JsonObj();
	std::string example();
	std::string toJson(Message_s& data);
	std::string put(std::string& data, ptree& node);


	std::string stringify();// in order to send the JSON trough the websocket as a string


	std::vector< std::pair<std::string, std::string> > _handsVector;
	std::vector< std::pair<std::string, std::string> > _fingersVector;
	Payload_s _payload;

};

#endif /* SRC_JSONOBJ_H_ */
