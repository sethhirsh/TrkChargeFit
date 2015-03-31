#ifndef FindMultiplePeak_hh
#define FindMultiplePeak_hh

#include "TrkChargeReco/inc/FindPeakBaseRoot.hh"

namespace mu2e{

namespace TrkChargeReco{

class SumADC : public FindPeakBaseRoot{
	public:
		SumADC(const ConfigStruct &initParams) : FindPeakBaseRoot(initParams){};

		virtual void process(const adcWaveform adcData, const resultantHitData &initialGuess, resultantHitData &result);
};


class FindSinglePeak : public FindPeakBaseRoot{
	public:
		// FindSinglePeak normal constructor with ConfigStruct initilization parameters
		FindSinglePeak(const ConfigStruct &initParams);

		// Fills result using adc waveform data using by fitting with the convolutionSinglePeakWithDynamicPedestal model
		// NOTE : This function may begin with peak data provided in result which is replaced
		virtual void process(const adcWaveform adcData, const resultantHitData &initialGuess, resultantHitData &result);

	protected:
		void fitParams2ResultantData(const Double_t *fitParameters, resultantHitData &result);
};

class FindSinglePeakWithConstantPedestal : public FindPeakBaseRoot{
	public:
		// FindSinglePeak normal constructor with ConfigStruct initilization parameters
		FindSinglePeakWithConstantPedestal(const ConfigStruct &initParams);

		// Fills result using adc waveform data using by fitting with the convolutionSinglePeakWithDynamicPedestal model
		// NOTE : This function may begin with peak data provided in result which is replaced
		virtual void process(const adcWaveform adcData, const resultantHitData &initialGuess, resultantHitData &result);

	protected:
		void fitParams2ResultantData(const Double_t *fitParameters, resultantHitData &result);
};


class FindSinglePeakWithDynamicPedestal : public FindPeakBaseRoot{
	public:

		// FindSinglePeakWithDynamicPedestal normal constructor with ConfigStruct initilization parameters
		FindSinglePeakWithDynamicPedestal(const ConfigStruct &initParams);

		// Fills result using adc waveform data using by fitting with the convolutionSinglePeakWithDynamicPedestal model
		// NOTE : This function may begin with peak data provided in result which is replaced
		virtual void process(const adcWaveform adcData, const resultantHitData &initialGuess, resultantHitData &result);

	protected:

		void fitParams2ResultantData(const Double_t *fitParameters, resultantHitData &result);

};

class FindDoublePeak : public FindPeakBaseRoot{
	public:
		FindDoublePeak(const ConfigStruct &initParams);

		// Fills result using adc waveform data using by fitting with the convolutionSinglePeakWithDynamicPedestal model
		// NOTE : This function may begin with peak data provided in result which is replaced
		virtual void process(const adcWaveform adcData, const resultantHitData &initialGuess, resultantHitData &result);

	protected:

		void fitParams2ResultantData(const Double_t *fitParameters, resultantHitData &result);
};

class FindDoublePeakWithDynamicPedestal : public FindPeakBaseRoot{
	public:
		// FindDoublePeakWithDynamicPedestal normal constructor with ConfigStruct initilization parameters
		FindDoublePeakWithDynamicPedestal(const ConfigStruct &initParams);

		// Fills result using adc waveform data using by fitting with the convolutionSinglePeakWithDynamicPedestal model
		// NOTE : This function may begin with peak data provided in result which is replaced
		virtual void process(const adcWaveform adcData, const resultantHitData &initialGuess, resultantHitData &result);

	protected:

		void fitParams2ResultantData(const Double_t *fitParameters, resultantHitData &result);
};

class FindMultiplePeaks : public FindPeakBaseRoot{
	public:

		// FindMultiplePeaks normal constructor with ConfigStruct initilization parameters
		FindMultiplePeaks(const ConfigStruct &initParams) : FindPeakBaseRoot(initParams){};
		
		// Fills result using adc waveform data using by fitting with the convolutionSinglePeakWithDynamicPedestal model
		// NOTE : This function may begin with peak data provided in result which is replaced
		virtual void process(const adcWaveform adcData, const resultantHitData &initialGuess, resultantHitData &result); 

};
}
}
#endif
