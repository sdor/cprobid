#ifndef MzXmlIon_H
#define MzXmlIon_H
#include <string>
#include <vector>
#include <optional>
#include <MzXmlPrecursorIon.h>

typedef struct {
    long num;
    int msLevel;
    int peaksCount;
    std::string retentionTime;
	double startMz;
	double endMz;
    double lowMz;
    double highMz;
	double basePeakMz;
	double basePeakIntensity;
	double totIonCurrent;
    std::optional<MzXmlPrecursorIon> precursorIon;
    std::vector<int64_t> peaks;
} MzXmlIon;

#endif