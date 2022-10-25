#include <stdio.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>



int parse_config(xmlDocPtr docptr, xmlNodePtr confnode) {

    xmlNodePtr node = confnode->xmlChildrenNode;
    while(NULL != node) {
        xmlChar * value = NULL;
        value = xmlNodeListGetString(docptr, node->xmlChildrenNode, 1);
        if(!xmlStrcmp(node->name, (const xmlChar *)"log")) {
            fprintf(stdout, "Node: %s,  value: %s\n", node->name, value);
        }
        else if(!xmlStrcmp(node->name, (const xmlChar *)"loglevel")) {
            fprintf(stdout, "Node: %s,  value: %s\n", node->name, value);
        }
        else if(!xmlStrcmp(node->name, (const xmlChar *)"timeout")) {
            fprintf(stdout, "Node: %s,  value: %s\n", node->name, value);
        }
        else if(!xmlStrcmp(node->name, (const xmlChar *)"logappend")) {
            //if(!xmlStrcmp(value, (const xmlChar *)"true")) 
            if(value) {
                fprintf(stdout, "Node: %s,  value: %s\n", node->name, value);
            }
            else {
                fprintf(stdout, "Node: %s\n", node->name);
            }

        }
        else {
        }
        node = node->next;
        xmlFree(value);
    }
    return 0;
}

int parse_site(xmlDocPtr docptr, xmlNodePtr sitenode) {
    
    xmlNodePtr node = sitenode->xmlChildrenNode;
    while(NULL != node) {
        xmlChar * value = NULL;
        value = xmlNodeListGetString(docptr, node->xmlChildrenNode, 1);
        if(!xmlStrcmp(node->name, (const xmlChar *)"ip")) {
            fprintf(stdout, "Node: %s,  value: %s\n", node->name, value);
        }
        else if(!xmlStrcmp(node->name, (const xmlChar *)"port")) {
            fprintf(stdout, "Node: %s,  value: %s\n", node->name, value);
        }
        else if(!xmlStrcmp(node->name, (const xmlChar *)"user")) {
            fprintf(stdout, "Node: %s,  value: %s\n", node->name, value);
        }
        else {
        }
        node = node->next;
        xmlFree(value);
    }
    return 0;
}

int parseFile(const char * const filename ) {

    xmlDocPtr xmldoc;
    xmlNodePtr xmlnode;


    xmldoc = xmlParseFile(filename);
    if(NULL == xmldoc) {
        fprintf(stdout, "Error in parsing xml file: %s\n", filename);
        return 1;
    }

    xmlnode = xmlDocGetRootElement(xmldoc);
    if(NULL == xmlnode) {
        fprintf(stdout, "Xml file %s is empty\n", filename);
        xmlFreeDoc(xmldoc);
        return 1;
    }
    else {
        fprintf(stdout, "Xml node: %s\n", xmlnode->name);
    }

    xmlNodePtr node = xmlnode->xmlChildrenNode;
    while(NULL != node) {
        //fprintf(stdout, "Node is: %s\n", node->name);
        if(!xmlStrcmp(node->name, (const xmlChar *)"site")) {
            xmlChar * location  = xmlGetProp(node, (const xmlChar *)"location");
            xmlChar * clusterid = xmlGetProp(node, (const xmlChar *)"cluster-id");
            if((NULL != location) && (NULL != clusterid)) {
                fprintf(stdout, "location: %s, cluster-id: %s\n", location, clusterid);
                xmlFree(location);
                xmlFree(clusterid);
            }
            parse_site(xmldoc, node);
        }
        else if(!xmlStrcmp(node->name, (const xmlChar *)"config")) {
            parse_config(xmldoc, node);
        }
        node = node->next;
    }

    xmlFreeDoc(xmldoc);

    return 0;
}

int myStrEqual(const xmlChar *str1, const xmlChar *str2) {
    if (str1 == str2) return(1);
    if (str1 == NULL) return(0);
    if (str2 == NULL) return(0);

    do {
        if (*str1++ != *str2) return(0);
    } while (*str2++);

    return(1);
}


int main(int argc, char * argv[]) {
    /*
    if(2 != argc) {
        fprintf(stdout, "Usage: %s <xmlfilename>\n", argv[0]);
        return 1;
    }
    else {
        fprintf(stdout, "File name is %s\n", argv[1]);
    }

    parseFile(argv[1]);
    */
    const xmlChar * c1 = "abc";
    const xmlChar * c2 = "abcdef";
    int res = myStrEqual(c1, c2);
    fprintf(stdout, "Result is %d\n", res);
    res = myStrEqual(c2, c1);
    fprintf(stdout, "Result is %d\n", res);
    res = myStrEqual(c1, c1);
    fprintf(stdout, "Result is %d\n", res);
    res = myStrEqual(NULL, c2);
    fprintf(stdout, "Result is %d\n", res);
    res = myStrEqual(c1, NULL);
    fprintf(stdout, "Result is %d\n", res);

    return 0;
}

/*********
    END OF FILE
 **********/
