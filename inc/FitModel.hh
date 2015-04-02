#ifndef FitModel_hh
#define FitModel_hh

#include "TMath.h"
#include "TrkChargeReco/inc/ParamStructs.hh"
#include "TrkChargeReco/inc/ConfigStruct.hh"

namespace mu2e {

namespace TrkChargeReco {

namespace FitModel {

  Float_t earlyPeak(const Double_t t, const EarlyPeakParamStruct &fitParams, const ConfigStruct &initParams);
  
  Float_t fixedTruncation(const Float_t currentFunctionValue, const ConfigStruct &initParams);

  // Shaping power set to 1
  Float_t unConvolvedSinglePeak(const Double_t t, const ConfigStruct &initParams);

  // Note that this is a convolution with a uniform distribution
  //2 Parameters (shaping power set to 1.0)
  //par[0] - sigma
  Float_t convolvedSinglePeak(const Double_t t, const Double_t sigma, const ConfigStruct &initParams);

  //Fitting function for current Function2
  //par[0] is shifted time 1st peak
  //par[1] is scalingfactor 1st peak
  //par[2] is sigma 1st peak
  Float_t singlePeak(const Double_t t, const SinglePeakParamStruct &fitParams, const ConfigStruct &initParams);
  			
  //Fitting function for current Function2
  //par[0] is shifted time 1st peak
  //par[1] is scalingfactor 1st peak
  //par[2] is vertical shift 1st peak
  //par[3] is sigma 1st peak

  Float_t singlePeakFloatingPedestal(const Double_t t, const SinglePeakFloatingPedestalParamStruct &fitParams, const ConfigStruct &initParams);

  // This is a truncating fitting function with a dynamical pedestal
  // par[0] is shifted time
  // par[1] is scaling factor
  // par[2] is Q
  // par[3] is sigma

  // This should inherit from convolutionSinglePeak not FitModelBase
  Float_t EXPeak(const Double_t t, const EXPeakParamStruct &fitParams, const ConfigStruct &initParams);

  // PUT THE DOUBLE_t PEAK FUNCTIONS HERE

      // Par0 - shift in X 1st peak
      // Par1 - scalingFactor 1st peak
      // Par2 - shift in 2nd peak minus shift in 1st peak
      // Par3 - scaling factor 2nd peak
  Float_t LXPeak(const Double_t t, const LXPeakParamStruct &fitParams, const ConfigStruct &initParams);
   
    // Par0 - shift in X 1st peak
    // Par1 - scalingFactor 1st peak
    // Par2 - vertical shift
    // Par3 - shift in 2nd peak minus shift in 1st peak
    // Par4 - scaling factor 2nd peak
  Float_t LXPeakFloatingPedestal(const Double_t t, const LXPeakFloatingPedestalParamStruct &fitParams, const ConfigStruct &initParams);

  // Par0 - shift in X 1st peak
  // Par1 - scalingFactor 1st peak
  // Par2 - Q
  // Par3 - shift in 2nd peak minus shift in 1st peak
  // Par4 - scaling factor 2nd peak
  Float_t ELXPeak(const Double_t t, const DoublePeakWithEarlyPeakParamStruct &fitParams, const ConfigStruct &initParams);

  // Apply truncation to necessary fit models

  Float_t earlyPeakTrunc(const Double_t t, const EarlyPeakParamStruct &fitParams, const ConfigStruct &initParams);

  Float_t singlePeakTrunc(const Double_t t, const SinglePeakParamStruct &fitParams, const ConfigStruct &initParams);

  Float_t singlePeakFloatingPedestalTrunc(const Double_t t, const SinglePeakFloatingPedestalParamStruct &fitParams, const ConfigStruct &initParams);

  Float_t EXPeakTrunc(const Double_t t, const EXPeakParamStruct &fitParams, const ConfigStruct &initParams);

  Float_t LXPeakTrunc(const Double_t t, const LXPeakParamStruct &fitParams, const ConfigStruct &initParams);

  Float_t LXPeakFloatingPedestalTrunc(const Double_t t, const LXPeakFloatingPedestalParamStruct &fitParams, const ConfigStruct &initParams);

  Float_t ELXPeakTrunc(const Double_t t, const DoublePeakWithEarlyPeakParamStruct &fitParams, const ConfigStruct &initParams);

}
}
}
#endif
