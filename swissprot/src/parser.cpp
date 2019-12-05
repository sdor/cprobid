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

   auto namePath = xmlXPathCompile((const xmlChar*)"/entry/name");
   auto proteinRecommendedNamePath = xmlXPathCompile((const xmlChar*)"/entry/protein/recommendedName/fullName");
   auto sequencePath = xmlXPathCompile((const xmlChar*)"/entry/sequence");

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

   element parseSequence(xmlXPathContextPtr ctx) {
       element sequence;
       auto obj = xmlXPathCompiledEval(sequencePath,ctx);
       string value = getContent(obj,ctx);
       sequence.name = "sequence";
       sequence.content = value;
       sequence.attributes = getAttributes(obj,ctx);
       xmlXPathFreeObject(obj);

       return sequence;
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