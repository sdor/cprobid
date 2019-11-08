#include <MzXmlReader.h>
#include <base64.h>
#include <algorithm>
#include <future>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xmlreader.h>
#include <MzXmlPrecursorIon.h>

void MzXmlReader::read(void (*cb)(const MzXmlIon* ion)) {
  MzXmlIon* ion;
    
  if (this->reader == nullptr) { return; }
  
  while (xmlTextReaderRead(this->reader) == 1) {
      if( xmlTextReaderNodeType(this->reader) == XML_READER_TYPE_ELEMENT && xmlStrEqual(xmlTextReaderConstLocalName(this->reader), (const xmlChar *) "scan") == 1) {
        ion = new MzXmlIon;
        auto num                = xmlTextReaderGetAttribute(reader,(xmlChar*)"num");
        auto msLevel            = xmlTextReaderGetAttribute(reader,(xmlChar*)"msLevel");
        auto peaksCount         = xmlTextReaderGetAttribute(reader,(xmlChar*)"peaksCount");
        auto retentionTime      = xmlTextReaderGetAttribute(reader,(xmlChar*)"retentionTime");    
	      auto startMz            = xmlTextReaderGetAttribute(reader,(xmlChar*)"startMz");          
	      auto endMz              = xmlTextReaderGetAttribute(reader,(xmlChar*)"endMz");            
        auto lowMz              = xmlTextReaderGetAttribute(reader,(xmlChar*)"lowMz");            
        auto highMz             = xmlTextReaderGetAttribute(reader,(xmlChar*)"highMz");           
	      auto basePeakMz         = xmlTextReaderGetAttribute(reader,(xmlChar*)"basePeakMz");       
	      auto basePeakIntensity  = xmlTextReaderGetAttribute(reader,(xmlChar*)"basePeakIntensity");
	      auto totIonCurrent      = xmlTextReaderGetAttribute(reader,(xmlChar*)"totIonCurrent");    
        if(num != nullptr) ion->num              = std::atoi((const char*)num              );                
        if(msLevel != nullptr) ion->msLevel          = std::atoi((const char*)msLevel          );            
        if(peaksCount != nullptr) ion->peaksCount       = std::atoi((const char*)peaksCount       );         
        if(retentionTime != nullptr) ion->retentionTime    = (const char*)retentionTime;      
        if(startMz != nullptr) ion->startMz          = std::atof((const char*)startMz          );            
        if(endMz != nullptr) ion->endMz            = std::atof((const char*)endMz            );              
        if(lowMz != nullptr) ion->lowMz            = std::atof((const char*)lowMz            );              
        if(highMz != nullptr) ion->highMz           = std::atof((const char*)highMz           );             
        if(basePeakMz != nullptr) ion->basePeakMz       = std::atof((const char*)basePeakMz       );         
        if(basePeakIntensity != nullptr) ion->basePeakIntensity = std::atof((const char*)basePeakIntensity);  
        if(totIonCurrent != nullptr) ion->totIonCurrent    = std::atof((const char*)totIonCurrent    );      
        xmlFree(peaksCount);
        xmlFree(num);
        xmlFree(retentionTime);
	      xmlFree(startMz); 
	      xmlFree(endMz);
        xmlFree(lowMz);
        xmlFree(highMz); 
	      xmlFree(basePeakMz); 
	      xmlFree(basePeakIntensity);
	      xmlFree(totIonCurrent);         
      } else if(xmlTextReaderNodeType(this->reader) == XML_READER_TYPE_ELEMENT && xmlStrEqual(xmlTextReaderConstLocalName(this->reader), (const xmlChar *) "precursorMz") == 1) {
        auto precursorIntensity = xmlTextReaderGetAttribute(reader,(xmlChar*)"precursorIntensity");
        auto collisionEnergy = xmlTextReaderGetAttribute(reader,(xmlChar*)"collisionEnergy");
        auto mz = xmlTextReaderReadInnerXml(this->reader);
        MzXmlPrecursorIon precursorIon;
        if(precursorIntensity != nullptr) precursorIon.intensity = std::atof((char*) precursorIntensity);
        if(collisionEnergy != nullptr) precursorIon.collisionEnergy = std::atof((char *)collisionEnergy);
        if(mz != nullptr) precursorIon.mz = std::atof((char*)mz);
        ion->precursorIon = precursorIon;
        xmlFree(mz);
        xmlFree(precursorIntensity);
        xmlFree(collisionEnergy);
      } else if(xmlTextReaderNodeType(this->reader) == XML_READER_TYPE_ELEMENT && xmlStrEqual(xmlTextReaderConstLocalName(this->reader), (const xmlChar *) "peaks") == 1) {        
        auto _precision =  xmlTextReaderGetAttribute(reader,(xmlChar*)"precision");
        auto peaksValue =  xmlTextReaderReadInnerXml(reader);
        int precision = std::atoi((const char*)_precision);
        auto peaksSize = 2*ion->peaksCount;
        if(precision == 32){
          auto peaks = new uint32_t[peaksSize];
          b64_decode_mio ((char *)peaks, (char *)peaksValue);
          std::transform(peaks,peaks+peaksSize,peaks,[](uint32_t v) {
            return ntohl(v);
          });
          ion->peaks.resize(peaksSize);
          std::transform(peaks, peaks+peaksSize, begin(ion->peaks), [](uint32_t v) {
            uint64_t _v = v;
            return _v;
          }); 
          delete[] peaks;
        } else if(precision == 64) {
          auto peaks = new uint64_t[peaksSize];
          b64_decode_mio ((char *)peaks, (char *)peaksValue);
          std::transform((uint32_t*) peaks,((uint32_t*)peaks)+2*peaksSize,peaks,[](uint32_t v) {
            return ntohl(v);
          });
          ion->peaks.resize(peaksSize);
          std::copy(peaks, peaks+peaksSize, begin(ion->peaks)); 
          delete[] peaks;
        }
        xmlFree(peaksValue);
        xmlFree(_precision);
      } else if(xmlTextReaderNodeType(reader) == XML_READER_TYPE_END_ELEMENT && xmlStrEqual(xmlTextReaderConstLocalName(reader), (const xmlChar *) "scan") == 1) {
        auto f = std::async(cb,ion);
        f.wait();
        delete ion;
      }
  }
};