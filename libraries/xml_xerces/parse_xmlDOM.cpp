/*********
 *	This example demonstrates about parsing an xml data using xercesc library
 * **********/

#include <iostream>

#include <cstdio>
#include <cstdlib>
#include <cstring>


#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMDocumentType.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMNodeIterator.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMText.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/XMLUni.hpp>

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>

using namespace xercesc;


int iterate_node(DOMNode* node) {

	if(!node->getNodeType()) {
		std::clog << "Node type is null" << '\n';
		return 1;
	}

	DOMNode::NodeType node_t = node->getNodeType();

	switch(node_t) {
		case (DOMNode::ELEMENT_NODE):
			{
				DOMElement* elem = dynamic_cast<DOMElement*>(node);
				std::clog << "Element tag name is 	: " << XMLString::transcode(elem->getTagName()) << '\n';

				// process attribute nodes of the element
				DOMNamedNodeMap* elem_attrs = node->getAttributes();
				const XMLSize_t attrs_len = elem_attrs->getLength();
				for(XMLSize_t i = 0; i < attrs_len; i++) {
					DOMNode* attr_node = elem_attrs->item(i);
					iterate_node(attr_node);
				} // end of for loop

				// process child nodes of the element nodes
				DOMNodeList* elem_childs = elem->getChildNodes();
				const XMLSize_t childs_len = elem_childs->getLength();
				for(XMLSize_t i = 0; i < childs_len; i++) {
					DOMNode* child_node = elem_childs->item(i);
					iterate_node(child_node);
				} // end of for loop
				break;
			}

		case (DOMNode::ATTRIBUTE_NODE):
			{
				DOMAttr* attr = dynamic_cast<DOMAttr*>(node);
				std::clog << "Attribute name    : " << XMLString::transcode(attr->getName()) << '\n';
				std::clog << "Attribute value   : " << XMLString::transcode(attr->getValue()) << '\n';
				break;
			}

		case (DOMNode::TEXT_NODE):
			{
				DOMText* text_node = dynamic_cast<DOMText*>(node);
				std::clog << "Text node value is : " << XMLString::transcode(text_node->getNodeValue()) << '\n';
				break;
			}

		default:
			std::clog << "Node type is not processed" << '\n';
	} // end of switch

	return 0;

}

int main(const int argc, const char * const argv[]) {

	if(2 != argc ) {
		std::clog << "Usage: " << argv[0] << " <xml_file_to_parse>\n";
		return 0;
	}

	XercesDOMParser *xml_parser = nullptr;
	//	const char * xmlFile = "test.xml";



	try {
		XMLPlatformUtils::Initialize();
	}
	catch (const XMLException& exp) {
		char* err_msg = XMLString::transcode(exp.getMessage());
		std::clog << "Exception during initialization " << err_msg << '\n';
		XMLString::release(&err_msg);
		return 1;
	}

	xml_parser = new XercesDOMParser();

	xml_parser->setValidationScheme( XercesDOMParser::Val_Never );
	xml_parser->setDoNamespaces( false );

	ErrorHandler* errHandler = (ErrorHandler*) new HandlerBase();
	xml_parser->setErrorHandler(errHandler);

	try {
		//xml_parser->parse(xmlFile);
		xml_parser->parse(argv[1]);

		DOMDocument* domDoc = xml_parser->getDocument();
		std::clog << "domDoc node type is 	: " << domDoc->getNodeType() << '\n';
		std::clog << "domDoc node name is 	: " << XMLString::transcode(domDoc->getNodeName()) << '\n';

		DOMElement* domElem = domDoc->getDocumentElement();
		std::clog << "Element tag name is 	: " << XMLString::transcode(domElem->getTagName()) << '\n';
		std::clog << "domElem node type is 	: " << domElem->getNodeType() << '\n';
		std::clog << "domElem node name is 	: " << XMLString::transcode(domElem->getNodeName()) << '\n';
		iterate_node(domElem->getAttributes()->item(0));

	/*

		DOMNodeList *elem_list = domDoc->getElementsByTagName(XMLString::transcode("root"));
		const XMLSize_t elem_cnt = elem_list->getLength();

		for(XMLSize_t i = 0; i < elem_cnt; i++) {
			std::clog << "Node name : " << XMLString::transcode(elem_list->item(i)->getNodeName())
				<< "	Node parent name : " << XMLString::transcode(elem_list->item(i)->getParentNode()->getNodeName())
				<< "	Node grand parent name : " << XMLString::transcode(elem_list->item(i)->getParentNode()->getParentNode()->getNodeName())
				<< '\n';
			iterate_node(elem_list->item(i));
		}
		
		std::clog << '\n';
		DOMNodeList *elem_list02 = domDoc->getElementsByTagName(XMLString::transcode("Others"));
		iterate_node(elem_list02->item(0));
		
		DOMNodeList *elem_list03 = domDoc->getElementsByTagName(XMLString::transcode("root"));
		iterate_node(elem_list03->item(0));
*/

		DOMNodeList * children = domElem->getChildNodes();
		const XMLSize_t nodeCount = children->getLength();
			

		for(XMLSize_t i = 0; i < nodeCount; i++) {
			DOMNode* cur_node = children->item(i);
			std::clog << "Inside loop i	: " << (i+1) << '\n';
			iterate_node(cur_node);
			//std::clog << "Node name is 	: " << XMLString::transcode(cur_node->getNodeName()) << '\n';
			//std::clog << "Node type is 	: " << cur_node->getNodeType() << '\n';
/*
			   if ((cur_node->getNodeType()) && 
			   (DOMNode::ELEMENT_NODE == cur_node->getNodeType())) {

			   DOMElement* cur_elem = dynamic_cast<DOMElement*>(cur_node);
			   std::clog << "Element tag name is 	: " << XMLString::transcode(cur_elem->getTagName()) << '\n';


			   DOMNamedNodeMap* elem_attrs = cur_node->getAttributes();
			   XMLSize_t attrs_len = elem_attrs->getLength();

			   for(XMLSize_t attr_index = 0; attr_index < attrs_len; attr_index++) {
			   DOMNode* attr_node = elem_attrs->item(attr_index);

			   if((attr_node->getNodeType()) && 
			   (DOMNode::ATTRIBUTE_NODE == attr_node->getNodeType()) ) {

			   DOMAttr* attr = dynamic_cast<DOMAttr*>(attr_node);

			   std::clog << "Attribute name 	: " << XMLString::transcode(attr->getName()) << '\n';
			   std::clog << "Attribute value 	: " << XMLString::transcode(attr->getValue()) << '\n';
			   }


			   } // end of for loop for attributes



			   if(XMLString::equals(cur_elem->getTagName(), XMLString::transcode("Student"))) {

			   const XMLCh * name = cur_elem->getAttribute(XMLString::transcode("Name"));
			   std::clog << "Student name is	: " << XMLString::transcode(name) << '\n';

			   const XMLCh * age = cur_elem->getAttribute(XMLString::transcode("Age"));
			   std::clog << "Student age is	: " << XMLString::transcode(age) << '\n';
			   }
			   else if(XMLString::equals(cur_elem->getTagName(), XMLString::transcode("Others"))) {

			   const XMLCh * com = cur_elem->getAttribute(XMLString::transcode("Company"));
			   std::clog << "Company name is	: " << XMLString::transcode(com) << '\n';

			   const XMLCh * nemp = cur_elem->getAttribute(XMLString::transcode("NoOfEmployee"));
			   std::clog << "Company age is	: " << XMLString::transcode(nemp) << '\n';
			   }

			   } 
			   */

		} // end of for loop


	} // end of try
	catch (const XMLException& exp) {
		char* err_msg = XMLString::transcode(exp.getMessage());
		std::clog << "Exception during initialization " << err_msg << '\n';
		XMLString::release(&err_msg);
		return 1;
	}


	delete xml_parser;
	delete errHandler;

	return 0;
}

/******
 *	END OF FILE
 * *****/
