#ifndef MzXmlPrecursorIon_H
#define MzXmlPrecursorIon_H
namespace MzXML {
    typedef struct {
        double mz;
        double intensity;
        double collisionEnergy;
    } MzXmlPrecursorIon;
}
#endif