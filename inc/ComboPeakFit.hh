#ifndef ComboPeakFit_hh
#define ComboPeakFit_hh

#include "TrkChargeReco/inc/PeakFitRootBase.hh"

namespace mu2e {

namespace TrkChargeReco {

class SumADC : public PeakFitRootBase{
	public:
		SumADC(const ConfigStruct &initParams) : PeakFitRootBase(initParams){};

		virtual void process(const adcWaveform adcData, const resultantHitData &initialGuess, resultantHitData &result);
};


class SinglePeakFit : public PeakFitRootBase{
	public:
		// SinglePeakFit normal constructor with ConfigStruct initilization parameters
		SinglePeakFit(const ConfigStruct &initParams);

		// Fills result using adc waveform data using by fitting with the convolutionSinglePeakWithDynamicPedestal model
		// NOTE : This function may begin with peak data provided in result which is replaced
		virtual void process(const adcWaveform adcData, const resultantHitData &initialGuess, resultantHitData &result);

	protected:
		void fitParams2ResultantData(const Double_t *fitParameters, resultantHitData &result);
};

class SinglePeakFloatingPedestalFit : public PeakFitRootBase{
	public:
		// SinglePeakFit normal constructor with ConfigStruct initilization parameters
		SinglePeakFloatingPedestalFit(const ConfigStruct &initParams);

		// Fills result using adc waveform data using by fitting with the convolutionSinglePeakWithDynamicPedestal model
		// NOTE : This function may begin with peak data provided in result which is replaced
		virtual void process(const adcWaveform adcData, const resultantHitData &initialGuess, resultantHitData &result);

	protected:
		void fitParams2ResultantData(const Double_t *fitParameters, resultantHitData &result);
};


class EXPeakFit : public PeakFitRootBase{
	public:

		// EXPeakFit normal constructor with ConfigStruct initilization parameters
		EXPeakFit(const ConfigStruct &initParams);

		// Fills result using adc waveform data using by fitting with the convolutionSinglePeakWithDynamicPedestal model
		// NOTE : This function may begin with peak data provided in result which is replaced
		virtual void process(const adcWaveform adcData, const resultantHitData &initialGuess, resultantHitData &result);

	protected:

		void fitParams2ResultantData(const Double_t *fitParameters, resultantHitData &result);

};

class LXPeakFit : public PeakFitRootBase{
	public:
		LXPeakFit(const ConfigStruct &initParams);

		// Fills result using adc waveform data using by fitting with the convolutionSinglePeakWithDynamicPedestal model
		// NOTE : This function may begin with peak data provided in result which is replaced
		virtual void process(const adcWaveform adcData, const resultantHitData &initialGuess, resultantHitData &result);

	protected:

		void fitParams2ResultantData(const Double_t *fitParameters, resultantHitData &result);
};

class ELXPeakFit : public PeakFitRootBase{
	public:
		// ELXPeakFit normal constructor with ConfigStruct initilization parameters
		ELXPeakFit(const ConfigStruct &initParams);

		// Fills result using adc waveform data using by fitting with the convolutionSinglePeakWithDynamicPedestal model
		// NOTE : This function may begin with peak data provided in result which is replaced
		virtual void process(const adcWaveform adcData, const resultantHitData &initialGuess, resultantHitData &result);

	protected:

		void fitParams2ResultantData(const Double_t *fitParameters, resultantHitData &result);
};

class ComboPeakFit : public PeakFitRootBase{
	public:

		// ComboPeakFit normal constructor with ConfigStruct initilization parameters
		ComboPeakFit(const ConfigStruct &initParams) : PeakFitRootBase(initParams){};
		
		// Fills result using adc waveform data using by fitting with the convolutionSinglePeakWithDynamicPedestal model
		// NOTE : This function may begin with peak data provided in result which is replaced
		virtual void process(const adcWaveform adcData, const resultantHitData &initialGuess, resultantHitData &result); 

};
}
}
#endif
