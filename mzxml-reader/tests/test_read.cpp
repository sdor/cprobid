#include <iostream>
#include <catch.hpp>
#include <MzXMLEvent.h>
#include <MzXmlReader.h>
void cb(const MzXML::Event &event) {
  std::cout<< event.getEventType() << std::endl;
}
TEST_CASE( "read mzxml", "[MzXmlReader]" ) {
    MzXML::MzXmlReader reader("/Users/sergey/Downloads/raftapr_mzXML/raft1213.mzXM");
    reader.read(cb);
    REQUIRE(1 == 1);
    // REQUIRE(ri.id.id == 1)
    // REQUIRE(ri.pos, 0);
}