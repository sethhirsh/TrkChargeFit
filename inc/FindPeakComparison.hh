#ifndef FindPeakComparison_hh
#define FindPeakComparison_hh

#include "TrkChargeReco/inc/FindMultiplePeak.hh"

namespace mu2e{

namespace TrkChargeReco{

class FindSinglePeakWithoutTrunc : public FindSinglePeak{
	public:
		// FindSinglePeak normal constructor with ConfigStruct initilization parameters
		FindSinglePeakWithoutTrunc(const ConfigStruct &initParams);
};

class FindSinglePeakWithConstantPedestalWithoutTrunc : public FindSinglePeakWithConstantPedestal{
	public:
		// FindSinglePeak normal constructor with ConfigStruct initilization parameters
		FindSinglePeakWithConstantPedestalWithoutTrunc(const ConfigStruct &initParams);
};

class  FindDoublePeakVsSinglePeak : public FindPeakBaseRoot{
	public:
		FindDoublePeakVsSinglePeak(const ConfigStruct &initParams) : FindPeakBaseRoot(initParams){};

		virtual void process(const adcWaveform adcData, const resultantHitData &initialGuess, resultantHitData &result);
};
}
}
#endif
