#include "TrkChargeReco/inc/FitModelRoot.hh"
#include "TMath.h"
#include "TrkChargeReco/inc/FitModel.hh"

namespace mu2e
{
namespace TrkChargeReco
{
namespace FitModelRoot
{
	ConfigStruct fitInitParams; // THIS NEEDS TO EVENTUALLY BE DELETED

	// Par0 - Q
	// The dynamic pedestal is of the form Q e^(-t / tau). 
	//Note that normalized it is Q / tau rather than Q 
	Float_t earlyPeakTrunc(Double_t *x, Double_t *par)
	{
	  EarlyPeakParamStruct parStruct(par[0]);	
	  return FitModel::earlyPeakTrunc(x[0],parStruct, fitInitParams);
	}

	Float_t earlyPeak(Double_t *x, Double_t *par)
	{
	 	EarlyPeakParamStruct parStruct(par[0]);
		return FitModel::earlyPeak(x[0],parStruct, fitInitParams);
	}	

	//Fitting function for current Function2
	//par[0] is shifted time 1st peak
	//par[1] is scalingfactor 1st peak
	//par[2] is sigma 1st peak
	Float_t convolutionSinglePeakTrunc(Double_t *x, Double_t *par)
	{
	  SinglePeakParamStruct parStruct(par[0],par[1],par[2]);

	  return FitModel::singlePeakTrunc(x[0],parStruct,fitInitParams);
	}

        //Fitting function for current Function2
        //par[0] is shifted time 1st peak
        //par[1] is scalingfactor 1st peak
        //par[2] is sigma 1st peak
        Float_t convolutionSinglePeak(Double_t *x, Double_t *par)
        {
          SinglePeakParamStruct parStruct(par[0],par[1],par[2]);

          return FitModel::singlePeak(x[0],parStruct,fitInitParams);
        }
				
	//Fitting function for current Function
	//par[0] is shifted time 1st peak
	//par[1] is scalingfactor 1st peak
	//par[2] is vertical shift 1st peak
	//par[3] is sigma 1st peak

	Float_t convolutionSinglePeakFloatingPedestalTrunc(Double_t *x, Double_t *par)
	{
	  SinglePeakFloatingPedestalParamStruct parStruct(par[0],par[1],par[2],par[3]);

	  return FitModel::singlePeakFloatingPedestalTrunc(x[0],parStruct,fitInitParams);
	}

        //Fitting function for current Function
        //par[0] is shifted time 1st peak
        //par[1] is scalingfactor 1st peak
        //par[2] is vertical shift 1st peak
        //par[3] is sigma 1st peak

        Float_t convolutionSinglePeakFloatingPedestal(Double_t *x, Double_t *par)
        {
          SinglePeakFloatingPedestalParamStruct parStruct(par[0],par[1],par[2],par[3]);

          return FitModel::singlePeakFloatingPedestal(x[0],parStruct,fitInitParams);
        }

	// This is a truncating fitting function with a dynamical pedestal
	// par[0] is shifted time
	// par[1] is scaling factor
	// par[2] is Q
	// par[3] is sigma

	// This should inherit from convolutionSinglePeak not FitModelBase
	Float_t convolutionSinglePeakWithDynamicPedestalTrunc(Double_t *x, Double_t *par)
	{

		EXPeakParamStruct parStruct(par[0],par[1],par[2],par[3]);

  		return FitModel::EXPeakTrunc(x[0],parStruct,fitInitParams);
  	}
	
	// Par0 - shift in X 1st peak
    // Par1 - scalingFactor 1st peak
    // Par2 - shift in 2nd peak minus shift in 1st peak
    // Par3 - scaling factor 2nd peak
	Float_t LXPeakTrunc(Double_t *x, Double_t *par)
	{
	LXPeakParamStruct parStruct(par[0],par[1],par[2],par[3]);

      	return FitModel::LXPeakTrunc(x[0],parStruct,fitInitParams);
	}
	 
    // Par0 - shift in X 1st peak
    // Par1 - scalingFactor 1st peak
    // Par2 - vertical shift
    // Par3 - shift in 2nd peak minus shift in 1st peak
    // Par4 - scaling factor 2nd peak
	Float_t LXPeakFloatingPedestalTrunc(Double_t *x, Double_t *par)
	{
		LXPeakFloatingPedestalParamStruct parStruct(par[0],par[1],par[2],par[3],par[4]);

      		return FitModel::LXPeakFloatingPedestalTrunc(x[0],parStruct,fitInitParams);
	}

	// Par0 - shift in X 1st peak
	// Par1 - scalingFactor 1st peak
	// Par2 - Q
	// Par3 - shift in 2nd peak minus shift in 1st peak
	// Par4 - scaling factor 2nd peak
	Float_t ELXPeakTrunc(Double_t *x, Double_t *par)
	{

		DoublePeakWithEarlyPeakParamStruct parStruct(par[0],par[1],par[2],par[3],par[4]);

  		return FitModel::ELXPeakTrunc(x[0],parStruct,fitInitParams);
	}

}
}
}
