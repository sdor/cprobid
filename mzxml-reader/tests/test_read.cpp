#include <cstring>
#include <iostream>
#include <catch.hpp>
#include <vector>
#include <algorithm>
#include <MzXMLEvent.h>
#include <MzXmlReader.h>
void cb(const MzXML::Event &event) {
  switch(event.getEventType()) {
    case MzXML::MzXML_ION_EVENT:
      MzXML::MzXmlIon * ion = (MzXML::MzXmlIon *) event.getPayload();
      break;
    // default:
    //   break;
  }
  // std::cout<< event.getEventType() << std::endl;
}
TEST_CASE( "read mzxml", "[MzXmlReader]" ) {
    MzXML::MzXmlReader reader("/home/sergey/Downloads/raftapr_mzXML/raft1213.mzXML");
    reader.read(cb);
    REQUIRE(1 == 1);
    // REQUIRE(ri.id.id == 1)
    // REQUIRE(ri.pos, 0);
}