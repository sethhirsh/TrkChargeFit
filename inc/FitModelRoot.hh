#ifndef FitModelRoot_hh
#define FitModelRoot_hh

#include "TMath.h"
#include "TrkChargeReco/inc/ConfigStruct.hh" // PROBABLY GET RID OF THIS INCLUDE STATEMENT EVENTUALLY


namespace mu2e{

namespace TrkChargeReco{

namespace FitModelRoot{

	Float_t earlyPeakTrunc(Double_t *x, Double_t *par);

	Float_t earlyPeak(Double_t *x, Double_t *par);

	//Fitting function for current Function2
	//par[0] is shifted time 1st peak
	//par[1] is scalingfactor 1st peak
	//par[2] is sigma 1st peak
	Float_t convolutionSinglePeakTrunc(Double_t *x, Double_t *par);
			
	Float_t convolutionSinglePeak(Double_t *x, Double_t *par);
	
	//Fitting function for current Function2
	//par[0] is shifted time 1st peak
	//par[1] is scalingfactor 1st peak
	//par[2] is vertical shift 1st peak
	//par[3] is sigma 1st peak

	Float_t convolutionSinglePeakFloatingPedestalTrunc(Double_t *x, Double_t *par);

	Float_t convolutionSinglePeakFloatingPedestal(Double_t *x, Double_t *par);

	// This is a truncating fitting function with a dynamical pedestal
	// par[0] is shifted time
	// par[1] is scaling factor
	// par[2] is Q
	// par[3] is sigma

	// This should inherit from convolutionSinglePeak not FitModelBase
	Float_t convolutionSinglePeakWithDynamicPedestalTrunc(Double_t *x, Double_t *par);

	// PUT THE DOUBLE_t PEAK FUNCTIONS HERE

    // Par0 - shift in X 1st peak
    // Par1 - scalingFactor 1st peak
    // Par2 - shift in 2nd peak minus shift in 1st peak
    // Par3 - scaling factor 2nd peak
	Float_t LXPeakTrunc(Double_t *x, Double_t *par);
	 
	  // Par0 - shift in X 1st peak
	  // Par1 - scalingFactor 1st peak
	  // Par2 - vertical shift
	  // Par3 - shift in 2nd peak minus shift in 1st peak
	  // Par4 - scaling factor 2nd peak
	Float_t LXPeakFloatingPedestalTrunc(Double_t *x, Double_t *par);

	// Par0 - shift in X 1st peak
	// Par1 - scalingFactor 1st peak
	// Par2 - Q
	// Par3 - shift in 2nd peak minus shift in 1st peak
	// Par4 - scaling factor 2nd peak
	Float_t ELXPeakTrunc(Double_t *x, Double_t *par);
}
}
}
#endif
