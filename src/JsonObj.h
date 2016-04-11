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

class JsonObj {
public:
	JsonObj();
	virtual ~JsonObj();
	std::string example();
	std::string toJson(std::vector<std::string>& data);
	std::string stringify();// in order to send the JSON trough the websocket as a string


	std::vector< std::pair<std::string, std::string> > _handsVector;
	std::vector< std::pair<std::string, std::string> > _fingersVector;

};

#endif /* SRC_JSONOBJ_H_ */
