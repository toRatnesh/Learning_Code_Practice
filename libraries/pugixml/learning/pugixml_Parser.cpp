/*******************
 *	This example demonstrates to parse a file using pugixml (used version is 1.10)
 *
 *
 *	It will take an xml file as input and print all the data present in the xml file.
 *
 * ************************/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include "pugixml.hpp"

int printAllDataRecursively(pugi::xml_node Node) {

	switch(Node.type()) {
		case pugi::node_null:
			fprintf(stdout, "Node is null\n");
			break;
		case pugi::node_document:
			fprintf(stdout, "Node name: %s\n", Node.name());
			break;
		case pugi::node_element:
			//fprintf(stdout, "Node name: %s value: %s\n", Node.name(), Node.value());
			fprintf(stdout, "Node name: %s\n", Node.name());
			break;
		case pugi::node_pcdata:
			fprintf(stdout, "Node value: %s\n", Node.value());
			break;
		default:
			fprintf(stdout, "Node type not implemented\n");
	}
	
	// Node attributes
	for(pugi::xml_attribute attr =  Node.first_attribute(); attr; attr = attr.next_attribute()) {
		if(attr) {
			fprintf(stdout, "Attribute name: %s,	value: %s\n", attr.name(), attr.value());
		}
	}

	// call recursively for its children then for siblings
	for(pugi::xml_node node = Node.first_child(); node; node = node.next_sibling()) {
		printAllDataRecursively(node);
	}


	return 0;

}

int main (const int argc, const char * const argv[]) {

	if(2 != argc) {
		fprintf(stdout, "Usage: %s <xml_file_to_parse>\n", argv[0]);
		return 0;
	}

	try {
		pugi::xml_document doc;
		pugi::xml_parse_result result = doc.load_file(argv[1]);

		if(result) {
			fprintf(stdout, "[%s::%d] Successfully parsed XML file: %s\n", __FILE__, __LINE__, result.description());
		}	
		else {
			fprintf(stdout, "[%s::%d] Failed to parse XML file, Error: %s\n", __FILE__, __LINE__, result.description());
			return 1;
		}
	
			
		pugi::xml_node docNode = doc.document_element();
		
		/*
		fprintf(stdout, "Document node name: %s value : %s\n", docNode.name(), docNode.value());
		for(pugi::xml_attribute attr =  docNode.first_attribute(); attr; attr = attr.next_attribute()) {
			fprintf(stdout, "Attribute name: %s value: %s\n", attr.name(), attr.value());
		}
		*/
		printAllDataRecursively(docNode);

	}
	catch (const std::exception & exp) {
		fprintf(stderr, "[%s::%d] Std exception caught: %s\n", __FILE__, __LINE__, exp.what());
	}
	catch(...) {
		fprintf(stderr, "[%s::%d] Exception caught\n", __FILE__, __LINE__);
	}


	return 0;
}

/*********
 *	END OF FILE
 * *********/
