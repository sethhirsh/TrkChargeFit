#include "Mu2e3/inc/FindPeakBaseRoot.hh"


namespace Mu2e{
// Fits a model function to a waveform
// Note: It is assumed that the waveform being fitted is normalized. 
// Thus, the scaling factor parameter which is passed in must be not in units of bits but scaled to this normaliztion
// This can be done by multiplying by the _bits2scalingfactor conversion factor
void FindPeakBaseRoot::fitModel2NormalizedWaveform(TF1 &fitModel, TGraphErrors &fitData, const Double_t *initialParameters, Double_t *fitParameters)
{
	// These lines will be replaced with the chi-square minimization
	TF1 *fitModelPtr = &fitModel; 
	TGraphErrors *fitDataPtr = &fitData;
	fitModel.SetParameters(initialParameters);

	fitDataPtr->Fit(fitModelPtr,"QN");
	
	const Int_t numParameters = fitModel.GetNumberFreeParameters();

	for (int i = 0; i < numParameters; ++i)
	{
		fitParameters[i] = fitModel.GetParameter(i);
	}
}



// Converts adcWaveform object to TGraphErrors object for easier manipulation in ROOT
void FindPeakBaseRoot::adcWaveform2TGraphErrors(const adcWaveform adcData, TGraphErrors &fitData)
{
	Double_t adcDataTemp[_initParams._numSamplesPerHit];
	Double_t measurementTimes[_initParams._numSamplesPerHit];
	Double_t measurementTimesErrors[_initParams._numSamplesPerHit];
	Double_t adcDataErrors[_initParams._numSamplesPerHit];

	for (int i = 0; i < _initParams._numSamplesPerHit; ++i)
	{
		adcDataTemp[i] = (Double_t) adcData[i];
		measurementTimes[i] = (Double_t) i * _initParams._measurementFrequency; 
		measurementTimesErrors[i] = 0.0;
		adcDataErrors[i] = _initParams._adcError;
	}

	fitData = TGraphErrors(_initParams._numSamplesPerHit,measurementTimes,adcDataTemp,measurementTimesErrors,adcDataErrors);
}

void FindPeakBaseRoot::initialPeakGuess(const adcWaveform adcData, resultantHitData &initialGuess)
{
	adcWaveform2TGraphErrors(adcData, _fitData);
	findPeaks(_fitData,_initParams, initialGuess);
	const unsigned int numPeaks = initialGuess.size();
	// If there is only one peak and it is a dynamic pedestal
	// search for and add another peak
	if (numPeaks == 1 && initialGuess[0]._peakTime == 0.0){
		dynamicPedestalAddPeak(_fitData, initialGuess);}
}


// This function searches for another peak in the waveform data by subtracting out a dynamic pedestal 
// from the adc waveform and finding the maximum adc value in the "subtracted data".
// This function is applied when no peak is found in the explicit peak search (findPeaks).
void FindPeakBaseRoot::dynamicPedestalAddPeak(const TGraphErrors &gr, resultantHitData &initialGuess)
{	
	// This maybe could be done using linear algebra vectors
	// instead of arrays
	const Double_t *adcValues = gr.GetY();
	const Double_t *measurementTimes = gr.GetX();
	Double_t subtractedValues[FindPeakBase::_initParams._numSamplesPerHit];

	Double_t dynamicPedestalParam[1] = {adcValues[0]};
	Double_t dynamicPedestalX[1];

	for (int i = 0; i < FindPeakBase::_initParams._numSamplesPerHit; ++i)
	{
		dynamicPedestalX[0] = measurementTimes[i];
		subtractedValues[i] = adcValues[i] - FitModelRoot::dynamicPedestalTrunc(dynamicPedestalX, dynamicPedestalParam);
	}

	// New peak is max value of difference between of adc values and dynamic pedestal
	const Float_t newAdcPeak = TMath::MaxElement(FindPeakBase::_initParams._numSamplesPerHit, subtractedValues);
	const Float_t newTPeak = TMath::LocMax(FindPeakBase::_initParams._numSamplesPerHit, subtractedValues);

	resultantPeakData newPeakData(newTPeak, newAdcPeak);
	initialGuess.push_back(newPeakData);
}


// Performs explicit peak search on adc waveform data
void FindPeakBaseRoot::findPeaks(const TGraphErrors &gr, const ConfigStruct &initParams, resultantHitData &initialGuess, const double sigma)
{
		int ientry = 0; // Start time at 0
		const double *measurementTimes = gr.GetX();
		const double *adcValues = gr.GetY();

		while(ientry < initParams._numSamplesPerHit)
		{
		double adcValue = adcValues[ientry];
		double tMax = measurementTimes[ientry];
		double adcMax = adcValue;
		double adcPrev = adcValue;

		int jentry = ientry + 1;
		bool descending = false;
		while (jentry < initParams._numSamplesPerHit)
		{
			adcValue = adcValues[jentry];
			descending |= ((adcPrev-adcValue) > (TMath::Sqrt2()*initParams._adcError*sigma));

			if (descending && (adcValue-adcPrev > (TMath::Sqrt2()*initParams._adcError*sigma)))
			{
			break;
			}
			else
			{
			if (adcValue > adcMax)
			{
  			adcMax  = adcValue;
  			tMax = measurementTimes[jentry];
				}
			adcPrev = adcValue;
			ientry = jentry;
			++jentry;
			}
			}
		resultantPeakData peakData(tMax, adcMax - initParams._defaultPedestal);
		initialGuess.push_back(peakData);
		++ientry;
		}
}
}
