#include "Mu2e3/inc/FindMultiplePeak.hh"
#include <iostream>
#include "Mu2e3/inc/FitModelRoot.hh" 
#include "TF1.h"
 

int testit(const int num)
{
	adcWaveform adcData;
	unsigned int adc[8] = {64, 60, 103, 125, 116, 108, 93, 92};
	adcData = adc;

	resultantHitData result;
	const ConfigStruct initParams;
	FindSinglePeak peak(initParams);
	for (int i = 0; i < num; ++i)
	{peak.process(adcData, result);
	}

	//std::cout << "result[0]._peakTime" << result[0]._peakTime << std::endl;
	//std::cout << "result[0]._peakHeight" << result[0]._peakHeight << std::endl;
	return 0;
}

void testit2(Double_t timeShift)
{
	TF1 *func = new TF1("func",FitModelRoot::convolutionSinglePeakTrunc,0.0,140.0,3);
	func->SetParameters(timeShift,108494.0,10.0);
	Double_t adc[8] = {64, 60, 103, 125, 116, 108, 93, 92};
	Double_t times[8] = {0.0, 20.0, 40.0, 60.0, 80.0, 100.0, 120.0, 140.0};
	TGraph * gr = new TGraph(8, times, adc);
	gr->Fit(func);
	gr->Draw("A*");
	func->Draw("same");
}
void testit3()
{
	/**TF1 *func1 =new TF1("func1",FitModelRoot::convolutionSinglePeakWithConstantPedestal,0.0,140.0,4);
	TF1 *func2 = new TF1("func2", FitModelRoot::fixedTruncation,0.0,2000.0,0);
	TF1 *func3 = new TF1("func3",func1*func2, 0.0, 140.0,4);
	func3->SetParameters(20.0,8494,0.0,10.0);
	func3->Draw();**/
}




