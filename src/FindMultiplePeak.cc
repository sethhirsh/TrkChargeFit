// MAKE SURE THAT initParams is getting passed everywhere correctly 

#include "TrkChargeReco/inc/FindMultiplePeak.hh"
#include "TrkChargeReco/inc/FitModelRoot.hh"

// TODO : ADD CLASS FindDoublePeakWithConstantPedestal

//SumADC::SumADC(const ConfigStruct &initParams) : FindPeakBaseRoot(initParams){}
namespace mu2e{
namespace TrkChargeReco{
void SumADC::process(const adcWaveform adcData, const resultantHitData &initialGuess, resultantHitData &result)
{
 	int sum = 0;
	for (auto i = 0;  i < _initParams._numSamplesPerHit; ++i)
	{
		sum += adcData[i];
	}

	// Subtract the pedestal
	sum -= 2 * _initParams._defaultPedestal;
	
	// Unlike the other Find Peak Methods Sum ADC return the sum in result._peakHeight and does not alter the peak time 	
	
	resultantPeakData peakData;
	peakData._peakHeight = sum; 
	result[0] = peakData;
}




// FindSinglePeak normal constructor with ConfigStruct initilization parameters
FindSinglePeak::FindSinglePeak(const ConfigStruct &initParams) : FindPeakBaseRoot(initParams)
{
  _fitModel = TF1("fitModel",FitModelRoot::convolutionSinglePeakTrunc,0.0,_initParams._hitPeriod,3);
}


// Fills result using adc waveform data using by fitting with the convolutionSinglePeakWithDynamicPedestal model
// NOTE : This function may begin with peak data provided in result which is replaced
void FindSinglePeak::process(const adcWaveform adcData, const resultantHitData &initialGuess, resultantHitData &result)
{

	// Set initial fit parameters
	const double timeshift = 30.0;
	const double scalingFactor = TMath::Max((initialGuess[0]._peakHeight - _initParams._defaultPedestal) * _initParams._bits2scalingFactor, 1000.0);
	const double sigma = 10.0;
	const Double_t initialParameters[3] = {timeshift, scalingFactor, sigma};

	Double_t finalParameters[3];

	FindPeakBaseRoot::adcWaveform2TGraphErrors(adcData, _fitData);
	FindPeakBaseRoot::fitModel2NormalizedWaveform(_fitModel, _fitData, initialParameters, finalParameters); 
	fitParams2ResultantData(finalParameters, result);
}


void FindSinglePeak::fitParams2ResultantData(const Double_t *fitParameters, resultantHitData &result)
{
	resultantPeakData peakData;

	// If there's time maybe make timeshift,scaling factor enumerated like true anomaly and eccentricity
	peakData._peakTime = fitParameters[0];
	peakData._peakHeight = fitParameters[1] * _initParams._scalingFactor2bits;

	result[0] = peakData;
}	


// FindSinglePeakWithConstantPedestal normal constructor with ConfigStruct initilization parameters
FindSinglePeakWithConstantPedestal::FindSinglePeakWithConstantPedestal(const ConfigStruct &initParams) : FindPeakBaseRoot(initParams)
{
  _fitModel = TF1("fitModel",FitModelRoot::convolutionSinglePeakWithConstantPedestalTrunc,0.0,_initParams._hitPeriod,4);
}


// Fills result using adc waveform data using by fitting with the convolutionSinglePeakWithDynamicPedestal model
// NOTE : This function may begin with peak data provided in result which is replaced
void FindSinglePeakWithConstantPedestal::process(const adcWaveform adcData, const resultantHitData &initialGuess, resultantHitData &result)
{	
	// Set initial fit parameters
	const double timeshift = 30.0;
	const double scalingFactor = TMath::Max((initialGuess[0]._peakHeight - _initParams._defaultPedestal) * _initParams._bits2scalingFactor, 1000.0);
	const double sigma = 10.0;
	const double verticalShift = (adcData[0] + adcData[1]) * 0.5;
	const Double_t initialParameters[4] = {timeshift, scalingFactor , verticalShift, sigma};

	Double_t finalParameters[4];

	FindPeakBaseRoot::adcWaveform2TGraphErrors(adcData, _fitData);
	FindPeakBaseRoot::fitModel2NormalizedWaveform(_fitModel, _fitData, initialParameters, finalParameters); 
	fitParams2ResultantData(finalParameters, result);
}


void FindSinglePeakWithConstantPedestal::fitParams2ResultantData(const Double_t *fitParameters, resultantHitData &result)
{
	resultantPeakData peakData;

	// If there's time maybe make timeshift,scaling factor enumerated like true anomaly and eccentricity
	peakData._peakTime = fitParameters[0];
	peakData._peakHeight = fitParameters[1] * _initParams._scalingFactor2bits;

	result[0] = peakData;
}	


// FindSinglePeakWithDynamicPedestal normal constructor with ConfigStruct initilization parameters
FindSinglePeakWithDynamicPedestal::FindSinglePeakWithDynamicPedestal(const ConfigStruct &initParams) : FindPeakBaseRoot(initParams)
{
	_fitModel = TF1("fitModel",FitModelRoot::convolutionSinglePeakWithDynamicPedestalTrunc,0.0,_initParams._hitPeriod,4);
}

// Fills result using adc waveform data using by fitting with the convolutionSinglePeakWithDynamicPedestal model
// NOTE : This function may begin with peak data provided in result which is replaced
void FindSinglePeakWithDynamicPedestal::process(const adcWaveform adcData, const resultantHitData &initialGuess, resultantHitData &result)
{

	// Set initial fit parameters
	const double timeshift = 30.0;
	const double scalingFactor = TMath::Max((initialGuess[1]._peakHeight - _initParams._defaultPedestal) * _initParams._bits2scalingFactor, 1000.0);
	const double Q = initialGuess[0]._peakHeight;
	const double sigma = 10.0;
	Double_t initialParameters[4] = {timeshift, scalingFactor, Q, sigma};

	Double_t finalParameters[4];

	FindPeakBaseRoot::adcWaveform2TGraphErrors(adcData, _fitData);
	FindPeakBaseRoot::fitModel2NormalizedWaveform(_fitModel, _fitData, initialParameters, finalParameters);
	fitParams2ResultantData(finalParameters, result);
}

void FindSinglePeakWithDynamicPedestal::fitParams2ResultantData(const Double_t *fitParameters, resultantHitData &result)
{

	// Dynamic Pedestal is treated as the first peak with a "peak time" of 0.0
	resultantPeakData dynamicPedestalData;

	dynamicPedestalData._peakTime = 0.0;
	dynamicPedestalData._peakHeight = fitParameters[2];

	resultantPeakData peakData;

	// If there's time maybe make timeshift,scaling factor enumerated like true anomaly and eccentricity
	peakData._peakTime = fitParameters[0];
	peakData._peakHeight = fitParameters[1] * _initParams._scalingFactor2bits;

	result[0] = dynamicPedestalData;
	result[1] = peakData;

}


FindDoublePeak::FindDoublePeak(const ConfigStruct &initParams) : FindPeakBaseRoot(initParams)
{
	_fitModel = TF1("fitModel",FitModelRoot::doublePeakTrunc,0.0,_initParams._hitPeriod,5);
}

// Fills result using adc waveform data using by fitting with the convolutionSinglePeakWithDynamicPedestal model
// NOTE : This function may begin with peak data provided in result which is replaced
void FindDoublePeak::process(const adcWaveform adcData, const resultantHitData &initialGuess, resultantHitData &result)
{
	// Set initial fit parameters
	const double timeShift0 = 30.0;
	const double scalingFactor0 = TMath::Max((initialGuess[0]._peakHeight - _initParams._defaultPedestal) * _initParams._bits2scalingFactor, 1000.0);
	const double timeshift1 = initialGuess[1]._peakTime - initialGuess[0]._peakTime;
	const double verticalShift = 0.0; // CHANGE EVENTUALLY
	const double scalingFactor1 = TMath::Max((initialGuess[1]._peakHeight - _initParams._defaultPedestal) * _initParams._bits2scalingFactor, 1000.0);
	const Double_t initialParameters[5] = {timeShift0, scalingFactor0, verticalShift, timeshift1, scalingFactor1};

	Double_t finalParameters[5];

	FindPeakBaseRoot::adcWaveform2TGraphErrors(adcData, _fitData);
	FindPeakBaseRoot::fitModel2NormalizedWaveform(_fitModel, _fitData, initialParameters, finalParameters);
	fitParams2ResultantData(finalParameters, result);
}

void FindDoublePeak::fitParams2ResultantData(const Double_t *fitParameters, resultantHitData &result)
{
	resultantPeakData firstPeakData;

	// If there's time maybe make timeshift,scaling factor enumerated like true anomaly and eccentricity
	firstPeakData._peakTime = fitParameters[0];
	firstPeakData._peakHeight = fitParameters[1] * _initParams._scalingFactor2bits;

	resultantPeakData secondPeakData;
	secondPeakData._peakTime = fitParameters[3];
	secondPeakData._peakHeight = fitParameters[4] * _initParams._scalingFactor2bits;

	result[0] = firstPeakData;
	result[1] = secondPeakData;
}

/**
FindDoublePeakWithConstantPedestal::FindDoublePeakWithConstantPedestal(const ConfigStruct &initParams) : FindPeakBaseRoot(initParams)
{
	_fitModel = TF1("fitModel",FitModelRoot::doublePeakTrunc,0.0,_initParams._hitPeriod,5);
}

// Fills result using adc waveform data using by fitting with the convolutionSinglePeakWithDynamicPedestal model
// NOTE : This function may begin with peak data provided in result which is replaced
void FindDoublePeakWithConstantPedestal::process(const adcWaveform adcData, resultantHitData &result)
{
	// Set initial fit parameters
	const double timeShift0 = 30.0;
	const double scalingFactor0 = TMath::Max((result[0]._peakHeight - _initParams._defaultPedestal) * _initParams._bits2scalingFactor, 1000.0);
	const double verticalShift = (adcData[0] + adcData[1]) * 0.5; // This has implicit casting
	const double timeshift1 = result[1]._peakTime - result[0]._peakTime;
	const double scalingFactor1 = TMath::Max((result[1]._peakHeight - _initParams._defaultPedestal) * _initParams._bits2scalingFactor, 1000.0);
	const Double_t initialParameters[5] = {timeShift0, scalingFactor0, verticalShift, timeshift1, scalingFactor1};

	Double_t finalParameters[5];

	FindPeakBaseRoot::adcWaveform2TGraphErrors(adcData, _fitData);
	FindPeakBaseRoot::fitModel2NormalizedWaveform(_fitModel, _fitData, initialParameters, finalParameters);
	fitParams2ResultantData(finalParameters, result);
}

void FindDoublePeakWithConstantPedestal::fitParams2ResultantData(const Double_t *fitParameters, resultantHitData &result)
{
	resultantPeakData firstPeakData;

	// If there's time maybe make timeshift,scaling factor enumerated like true anomaly and eccentricity
	firstPeakData._peakTime = fitParameters[0];
	firstPeakData._peakHeight = fitParameters[1] * _initParams._scalingFactor2bits;

	resultantPeakData secondPeakData;
	secondPeakData._peakTime = fitParameters[3];
	secondPeakData._peakHeight = fitParameters[4] * _initParams._scalingFactor2bits;

	result[0] = firstPeakData;
	result[1] = secondPeakData;
}
**/


// FindDoublePeakWithDynamicPedestal normal constructor with ConfigStruct initilization parameters
FindDoublePeakWithDynamicPedestal::FindDoublePeakWithDynamicPedestal(const ConfigStruct &initParams) : FindPeakBaseRoot(initParams)
{
	_fitModel = TF1("fitModel",FitModelRoot::doublePeakWithDynamicPedestalTrunc,0.0,_initParams._hitPeriod,5);
}

// Fills result using adc waveform data using by fitting with the convolutionSinglePeakWithDynamicPedestal model
// NOTE : This function may begin with peak data provided in result which is replaced
void FindDoublePeakWithDynamicPedestal::process(const adcWaveform adcData, const resultantHitData &initialGuess, resultantHitData &result)
{
	const double timeShift0 = 30.0;
	const double scalingFactor0 = TMath::Max((initialGuess[1]._peakHeight - _initParams._defaultPedestal) * _initParams._bits2scalingFactor, 1000.0);
	const double Q = initialGuess[0]._peakHeight;
	const double timeshift1 = initialGuess[2]._peakTime - initialGuess[1]._peakTime;
	const double scalingFactor1 = TMath::Max((initialGuess[2]._peakHeight - _initParams._defaultPedestal) * _initParams._bits2scalingFactor, 1000.0);

	Double_t initialParameters[5] = {timeShift0, scalingFactor0, Q, timeshift1, scalingFactor1};
	Double_t finalParameters[5];

	FindPeakBaseRoot::adcWaveform2TGraphErrors(adcData, _fitData);
	FindPeakBaseRoot::fitModel2NormalizedWaveform(_fitModel, _fitData, initialParameters, finalParameters);
	fitParams2ResultantData(finalParameters, result);
}

void FindDoublePeakWithDynamicPedestal::fitParams2ResultantData(const Double_t *fitParameters, resultantHitData &result)
{
	// First peak is dynamic pedestal with a "peak time" of 0.0
	resultantPeakData dynamicPedestalData;

	dynamicPedestalData._peakTime = 0.0;
	dynamicPedestalData._peakHeight = fitParameters[2];


	resultantPeakData firstPeakData;

	// If there's time maybe make timeshift,scaling factor enumerated like true anomaly and eccentricity
	firstPeakData._peakTime = fitParameters[0];
	firstPeakData._peakHeight = fitParameters[1] * _initParams._scalingFactor2bits;

	resultantPeakData secondPeakData;
	secondPeakData._peakTime = fitParameters[3];
	secondPeakData._peakHeight = fitParameters[4] * _initParams._scalingFactor2bits;

	result[0] = dynamicPedestalData;
	result[1] = firstPeakData;
	result[2] = secondPeakData;
}

// Fills result using adc waveform data using by fitting with the convolutionSinglePeakWithDynamicPedestal model
// NOTE : This function may begin with peak data provided in result which is replaced
void FindMultiplePeaks::process(const adcWaveform adcData, const resultantHitData &initialGuess, resultantHitData &result)
{
	const int numPeaks = result.size();
	if (initialGuess[0]._peakTime == 0.0) // If there is a dynamic pedestal
	{	
		// There are always going to be two peaks (guaranteed by initialPeakGuess)
		if (numPeaks == 2)
		{
			FindSinglePeakWithDynamicPedestal singlePeak(_initParams);
			singlePeak.process(adcData, initialGuess, result);
		}
		else if (numPeaks == 3)
		{
			FindDoublePeakWithDynamicPedestal doublePeak(_initParams);
			doublePeak.process(adcData, initialGuess, result);
		}
	}
	// If there is no dynamic pedestal
	// TODO : Finish implementing thie possibility of nonzero pedestal
	else
	{
		const bool nonZeroPedestal = (adcData[0] + adcData[1])*0.5 > 4.0 / TMath::Sqrt2() * 3.0;
		if (numPeaks == 1)
		{
			if (nonZeroPedestal)
			{
				FindSinglePeak singlePeak(_initParams);
				singlePeak.process(adcData, initialGuess, result);
			}
			else
			{
				FindSinglePeak singlePeak(_initParams);
				singlePeak.process(adcData, initialGuess, result);
			}
		}
		if (numPeaks == 2)
		{
			FindDoublePeak doublePeak(_initParams);
			doublePeak.process(adcData, initialGuess, result);
		}

	}	
}
}
}
