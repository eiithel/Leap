/*
 * JsonObj.cpp
 *
 *  Created on: 9 avr. 2016
 *      Author: ethel
 */

#include "JsonObj.h"

JsonObj::JsonObj() {
	// TODO Auto-generated constructor stub

}

JsonObj::~JsonObj() {
	// TODO Auto-generated destructor stub
}

using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;

std::string JsonObj::example() {
	// Write json.

	ptree pt;
	ptree children;

	ptree palmPosition, direction, type;
	ptree v1palm,v2palm,v3palm;
	ptree v1dir, v2dir, v3dir;

	v1palm.put("",2);
	v2palm.put("",5);
	v3palm.put("",4);

	v1dir.put("",8);
	v2dir.put("",9);
	v3dir.put("",7);

	type.put("", "left");

	palmPosition.push_back(std::make_pair("", v1palm));
	palmPosition.push_back(std::make_pair("", v2palm));
	palmPosition.push_back(std::make_pair("", v3palm));

	direction.push_back(std::make_pair("", v1dir));
	direction.push_back(std::make_pair("", v2dir));
	direction.push_back(std::make_pair("", v3dir));

	children.push_back(std::make_pair("", type));
	children.push_back(std::make_pair("", palmPosition));
	children.push_back(std::make_pair("", direction));

	pt.put("FrameRate", 3);
	pt.add_child("Hands", children);//{"MyArray":["1","2","3"]}

	/*
	ptree pt;
	ptree children;
	ptree child1, child2, child3;

	child1.put("", 1);
	child2.put("", 2);
	child3.put("", 3);

	children.push_back(std::make_pair("", child1));
	children.push_back(std::make_pair("", child2));
	children.push_back(std::make_pair("", child3));

	pt.add_child("MyArray", children);

	 */

	ptree oroot;

	std::vector< std::pair<std::string, std::string> > hands;
	hands.push_back(std::make_pair("chat","noir"));
	hands.push_back(std::make_pair("chien","bleu"));
	hands.push_back(std::make_pair("grenouille","verte"));


	std::vector< std::pair<std::string, std::string> > fingers;
	fingers.push_back(std::make_pair("pouce","noir"));
	fingers.push_back(std::make_pair("annulaire","bleu"));
	fingers.push_back(std::make_pair("majeur","vert"));

	// Create a node
	ptree hands_node;
	// Add animals as childs
	for (auto &hand : hands)
		hands_node.put(hand.first, hand.second);
	// Add the new node to the root
	oroot.add_child("Hands", hands_node);

	// Create a node
	ptree fingers_node;

	// Add fingers as childs

	for (auto &finger : fingers)
		fingers_node.put(finger.first, finger.second);
	// Add the new node to the root
	oroot.add_child("Fingers", fingers_node);


	std::ostringstream buf;
	write_json (buf, pt, false);
	std::string json = buf.str(); // {"animals":{"chat":"noir","chien":"bleu","grenouille":"verte"}}

	//boost::property_tree::ptree ptChild = oroot.get_child("Fingers");//on recupere Fingers

	return json;

	// Read json.
	/*
  ptree pt2;
  std::istringstream is (json);
  read_json (is, pt2);
  std::string foo = pt2.get<std::string> ("foo");
	 */
}


std::string JsonObj::toJson(std::vector<std::string>& data){
	/*
	type
	data[0]

	position  				direction
	data[1]					data[4]
	data[2]					data[5]
	data[3]					data[6]
	 */

	ptree pt;
	ptree children;

	ptree palmPosition, direction, type;
	ptree v1palm,v2palm,v3palm;
	ptree v1dir, v2dir, v3dir;

	v1palm.put("",data[1]);
	v2palm.put("",data[2]);
	v3palm.put("",data[3]);

	v1dir.put("",data[4]);
	v2dir.put("",data[5]);
	v3dir.put("",data[6]);

	type.put("", data[0]);


	palmPosition.push_back(std::make_pair("", v1palm));
	palmPosition.push_back(std::make_pair("", v2palm));
	palmPosition.push_back(std::make_pair("", v3palm));

	direction.push_back(std::make_pair("", v1dir));
	direction.push_back(std::make_pair("", v2dir));
	direction.push_back(std::make_pair("", v3dir));

	children.push_back(std::make_pair("", type));
	children.push_back(std::make_pair("", palmPosition));
	children.push_back(std::make_pair("", direction));

	pt.put("FrameRate", data[7]);
	pt.add_child("Hands", children);

	std::ostringstream buf;
	write_json (buf, pt, false);
	std::string json = buf.str();
	return json;
}

