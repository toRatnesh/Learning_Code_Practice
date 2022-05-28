/**********
 *	This example demonstrates about creating an xml document using xercesc library.
 *
 * ***************/

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
#include <xercesc/framework/StdOutFormatTarget.hpp>


using namespace xercesc;

void xml_output_to_stream(DOMDocument* pmyDOMDocument);

DOMElement* getElementNode(DOMDocument* dom_doc,
				const XMLCh* elem_tag_name,
				const XMLCh* attr_name = NULL,
				const XMLCh* attr_val = NULL) {

	DOMElement* elem = NULL;

	DOMNodeList* elem_list = dom_doc->getElementsByTagName(elem_tag_name);
	const XMLSize_t elem_cnt = elem_list->getLength();	
	
	// if there is no element node is present create a new element node and return it
	if(0 == elem_cnt) {
		elem = dom_doc->createElement(elem_tag_name);
		if(attr_name && attr_val)
			elem->setAttribute(attr_name, attr_val);
		std::cout << "No element tag found, creating a new one" << std::endl;
		return elem;

	}

	// traverse and try to find any existing node with same tag name and attributes
	for(XMLSize_t i = 0; i < elem_cnt; ++i) {
		DOMNode * elem_node = elem_list->item(i);
		if(elem_node->getNodeType() && 
		   (DOMNode::ELEMENT_NODE == elem_node->getNodeType()) && 
		   elem_node->hasAttributes()) {

			DOMElement* old_elem = dynamic_cast<DOMElement*>(elem_node);

			// get and check attributes of this element node
			DOMNamedNodeMap* elem_attrs = old_elem->getAttributes();
			const XMLSize_t attrs_len = elem_attrs->getLength();
			
			for(XMLSize_t j = 0; j < attrs_len; ++j) {
				DOMNode* node = elem_attrs->item(i);
				if(node->getNodeType() && (DOMNode::ATTRIBUTE_NODE == node->getNodeType())) {
					DOMAttr* attr = dynamic_cast<DOMAttr*>(node);
					if(XMLString::equals(attr_name, attr->getName()) &&
						XMLString::equals(attr_val, attr->getValue())) {

						elem = old_elem;
						break;
					}

				}
			} // end of for loop for attr	

			if(elem == old_elem)
				break;
		}
		
	} // end of for loop for elements

	// if no existing node is found create a new node and retue it
	if(NULL == elem) {
		elem = dom_doc->createElement(elem_tag_name);
		if(attr_name && attr_val)
			elem->setAttribute(attr_name, attr_val);
		std::cout << "Existing elemets does not match, creating a new element" << std::endl;
		return elem;
	}

	std::cout << "Existing element found" << std::endl;	
	return elem;

}


int main(int argc, char *argv[]) {

	//XMLCh temp_buff[64];

	XMLPlatformUtils::Initialize();

	DOMImplementation *p_domImpl = DOMImplementationRegistry::getDOMImplementation(XMLString::transcode("Core"));
	DOMDocument *p_domDoc = p_domImpl->createDocument(0, XMLString::transcode("root"), 0);

	DOMElement *p_root_elem = p_domDoc->getDocumentElement();

	DOMText *root_text_01 = p_domDoc->createTextNode(XMLString::transcode("Text_root_01"));
	p_root_elem->appendChild(root_text_01);

	DOMElement* element =  NULL;
	DOMText* text = NULL;
	element = getElementNode(p_domDoc, XMLString::transcode("Student"));
	text = p_domDoc->createTextNode(XMLString::transcode("Student text value"));
	
	if(element && element->getNodeType() && (DOMNode::ELEMENT_NODE == element->getNodeType()))
		p_root_elem->appendChild(element);

	if(text && text->getNodeType() && (DOMNode::TEXT_NODE == text->getNodeType()))
		element->appendChild(text);



/*
	DOMElement *root_child_student = p_domDoc->createElement(XMLString::transcode("Student"));
	p_root_elem->appendChild(root_child_student);
	DOMText* student_text_01 = p_domDoc->createTextNode(XMLString::transcode("Text_Student_01"));
	root_child_student->appendChild(student_text_01);


	DOMElement* student_child_batch = p_domDoc->createElement(XMLString::transcode("Batch"));
	student_child_batch->setAttribute(XMLString::transcode("Subject"), XMLString::transcode("Math"));
	student_child_batch->setAttribute(XMLString::transcode("ID"), XMLString::transcode("B01"));
	DOMText* batch_text = p_domDoc->createTextNode(XMLString::transcode("Ratnesh"));
	student_child_batch->appendChild(batch_text);
	root_child_student->appendChild(student_child_batch);

	DOMText* student_text_02 = p_domDoc->createTextNode(XMLString::transcode("Text_Student_02"));
	root_child_student->appendChild(student_text_02);

	student_child_batch = p_domDoc->createElement(XMLString::transcode("Batch"));
	student_child_batch->setAttribute(XMLString::transcode("Subject"), XMLString::transcode("Math"));
	student_child_batch->setAttribute(XMLString::transcode("ID"), XMLString::transcode("B01"));
	batch_text = p_domDoc->createTextNode(XMLString::transcode("Ratnesh"));
	student_child_batch->appendChild(batch_text);
	root_child_student->appendChild(student_child_batch);

	DOMText* student_text_03 = p_domDoc->createTextNode(XMLString::transcode("Text_Student_03"));
	root_child_student->appendChild(student_text_03);

	DOMText* root_text_02 = p_domDoc->createTextNode(XMLString::transcode("Text_root_02"));
	p_root_elem->appendChild(root_text_02);	

	DOMElement *root_child_others = p_domDoc->createElement(XMLString::transcode("Othres"));
	root_child_others->setAttribute(XMLString::transcode("Company"), XMLString::transcode("Airtel"));
	root_child_others->setAttribute(XMLString::transcode("NoOfEmployee"), XMLString::transcode("15"));
	p_root_elem->appendChild(root_child_others);
	DOMText* others_text_01 = p_domDoc->createTextNode(XMLString::transcode("Text_Others"));
	root_child_others->appendChild(others_text_01);

	DOMText* root_text_03 = p_domDoc->createTextNode(XMLString::transcode("Text_root_03"));
	p_root_elem->appendChild(root_text_03);

*/

	xml_output_to_stream(p_domDoc);

	p_domDoc->release();
	XMLPlatformUtils::Terminate();

	return 0;

}


void xml_output_to_stream(DOMDocument* pmyDOMDocument) {
	DOMImplementation    *pImplement    = NULL;
	DOMLSSerializer      *pSerializer   = NULL;
	XMLFormatTarget      *pTarget       = NULL;

	pImplement = DOMImplementationRegistry::getDOMImplementation(XMLString::transcode("LS"));	
	pSerializer = ((DOMImplementationLS*)pImplement)->createLSSerializer();
	pSerializer->setNewLine(XMLString::transcode("\n"));

	DOMConfiguration* pDomConfiguration = pSerializer->getDomConfig();
	pDomConfiguration->setParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true);

	pTarget = new StdOutFormatTarget();

	DOMLSOutput* pDomLsOutput = ((DOMImplementationLS*)pImplement)->createLSOutput();
	pDomLsOutput->setByteStream(pTarget);

	pSerializer->write(pmyDOMDocument, pDomLsOutput);

}

/**********
 *	END OF FILE
 * *********/
