/***********
 *	This example demonstrates about the use of pugixml to generate an xml 
 *
 * ************/


#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <iostream>
#include <string>
#include <fstream>

#include "pugixml.hpp"


struct xml_string_writer: pugi::xml_writer
{
	std::string result;

	virtual void write(const void* data, size_t size)
	{
		result.append(static_cast<const char*>(data), size);
	}
};

std::string node_to_string(pugi::xml_node node)
{
	xml_string_writer writer;
	node.print(writer);

	return writer.result;
}



int main(int argc, char * argv[]) {

	pugi::xml_node temp_node;
	pugi::xml_attribute temp_attr;

	pugi::xml_document doc;
	pugi::xml_node docNode = doc.append_child("root");
	docNode.append_attribute("xmlns:root") = "root namespace URI";
	//docNode.append_child(pugi::node_pcdata).set_value("Text_root_01");

	temp_node = docNode.append_child("Student");
	//temp_node.append_child(pugi::node_pcdata).set_value("Text_Student_01");
	temp_node = temp_node.append_child("Batch");
	temp_node.append_attribute("Subject") = "Math";
	temp_node.append_attribute("ID") = "B01";
	temp_node.append_child(pugi::node_pcdata).set_value("Ratnesh");

	temp_node = docNode.child("Student");
	//temp_node.append_child(pugi::node_pcdata).set_value("Text_Student_02");

	temp_node = temp_node.append_child("Batch");
	temp_node.append_attribute("Subject") = "Physics";
	temp_node.append_attribute("ID") = "B02";
	temp_node.append_child(pugi::node_pcdata).set_value("Kshitij");

	temp_node = docNode.child("Student");
	//temp_node.append_child(pugi::node_pcdata).set_value("Text_Student_03");


	//docNode.append_child(pugi::node_pcdata).set_value("Text_root_02");


	temp_node = docNode.append_child("Others");
	temp_node.append_attribute("Company") = "Airtel";
	temp_node.append_attribute("NoOfEmployee") = 15;
	temp_node.append_child(pugi::node_pcdata).set_value("Text_Others");

	//docNode.append_child(pugi::node_pcdata).set_value("Text_root_03");

	std::ofstream l_ofs("write_file.xml");
	doc.save(l_ofs);
	std::cout << '\n';

    std::cout << node_to_string(docNode) << '\n';
	return 0;
}

/*******
 *	END OF FILE
 * *****/
