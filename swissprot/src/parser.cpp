#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <iostream>
#include <cstring>
#include <string>
#include <map>
#include <vector>
#include <optional>
#include <parser.h>

using namespace std;
namespace swissprot {

   auto namePath = xmlXPathCompile((const xmlChar*)"/sw:entry/sw:name");
   auto proteinRecommendedNamePath = xmlXPathCompile((const xmlChar*)"/sw:entry/sw:protein/sw:recommendedName/sw:fullName");
   auto sequencePath = xmlXPathCompile((const xmlChar*)"/sw:entry/sw:sequence");
   auto organismPath = xmlXPathCompile((const xmlChar*)"/sw:entry/sw:organism");
   auto organismScientificName = xmlXPathCompile((const xmlChar*)"/sw:entry/sw:organism/sw:name[@type=\"scientific\"]");
   auto organismCommonName = xmlXPathCompile((const xmlChar*)"/sw:entry/sw:organism/sw:name[@type=\"common\"]");
   auto organismTaxonName = xmlXPathCompile((const xmlChar*)"/sw:entry/sw:organism/sw:dbReference[@type=\"NCBI Taxonomy\"]");

   string getContent(xmlXPathObjectPtr obj,xmlXPathContextPtr ctx) {
        string content;
        if(obj != nullptr && obj->nodesetval != nullptr && obj->nodesetval->nodeNr > 0){
           auto value = xmlNodeGetContent(obj->nodesetval->nodeTab[0]);           
           if(value != nullptr) {
               content = (const char*)value;
           }
           xmlFree(value);
        }
        return content;
   }

   

   map<string,string> getAttributes(xmlXPathObjectPtr obj,xmlXPathContextPtr ctx) {
       map<string,string> map;
       if(obj != nullptr && obj->nodesetval != nullptr && obj->nodesetval->nodeNr > 0) {
           auto node = obj->nodesetval->nodeTab[0];
           auto property = node->properties;
           if(property != nullptr) {
               if(property->children != nullptr){
                   string value;
                   auto _value = xmlNodeGetContent(property->children);
                   if(_value != nullptr) {
                       value = (const char *)_value;
                   }
                   xmlFree(_value);
                   if(property->name != nullptr) {
                       map[(const char*)property->name]=value;
                   }
               }
               property = property->next;
               while(property != nullptr) {
                   string value;
                   auto _value = xmlNodeGetContent(property->children);
                   if(_value != nullptr) {
                       value = (const char *)_value;
                   }
                   xmlFree(_value);
                   if(property->name != nullptr) {
                       map[(const char*)property->name]=value;
                   }
                   property = property->next;                   
               }
           }
       }
       return map;
   }

   string getAttribute(const char* name,xmlXPathObjectPtr obj,xmlXPathContextPtr ctx) {
       string attribute_value;
       auto attributes = getAttributes(obj,ctx);
       auto found = attributes.find(name);
       if(found != attributes.end()) {
           attribute_value = found->second;
       }
       return attribute_value;
   }

   string parseName(xmlXPathContextPtr ctx) {
       auto obj = xmlXPathCompiledEval(namePath,ctx);
       string value = getContent(obj,ctx);
       xmlXPathFreeObject(obj);
       return value;
   }
   string parseProteinRecommendedName(xmlXPathContextPtr ctx) {
       auto obj = xmlXPathCompiledEval(proteinRecommendedNamePath,ctx);
       string value = getContent(obj,ctx);
       xmlXPathFreeObject(obj);
       return value;
   }

   sequence parseSequence(xmlXPathContextPtr ctx) {
    //    element el;
       sequence sequence;
       auto obj = xmlXPathCompiledEval(sequencePath,ctx);
       string value = getContent(obj,ctx);
    //    el.name = "sequence";
    //    el.content = value;
       auto attributes = getAttributes(obj,ctx);
       xmlXPathFreeObject(obj);
       sequence.checksum = attributes["checksum"];
       sequence.version = atoi(attributes["version"].c_str());
       sequence.modified = attributes["modified"];
       sequence.sequence = value;
       return sequence;
   }

   organism parseOrganism(xmlXPathContextPtr ctx) {
        organism organism;
        auto obj = xmlXPathCompiledEval(organismScientificName,ctx);
        organism.scientific_name = getContent(obj,ctx);
        xmlXPathFreeObject(obj);
        obj = xmlXPathCompiledEval(organismCommonName,ctx);
        organism.common_name = getContent(obj,ctx);
        xmlXPathFreeObject(obj);
        obj = xmlXPathCompiledEval(organismTaxonName,ctx);
        organism.taxon = getAttribute("id",obj,ctx);
        xmlXPathFreeObject(obj);
        return organism;
   }


   void parse(void *data) {
       auto doc = xmlReadMemory((const char*)data,strlen((const char*)data),NULL,NULL,XML_PARSE_NOBLANKS);
       if(doc == nullptr) {
           cerr << "Unable to parse swissprot entry document" << endl;
           xmlFreeDoc(doc);
           return;
       }
       auto xpathCtx = xmlXPathNewContext(doc);
       if(xpathCtx ==nullptr) {
           cerr << "Unable to create new XPath context" << endl;
           xmlFreeDoc(doc);
           return;
       }

       xmlFreeDoc(doc);
   }
}