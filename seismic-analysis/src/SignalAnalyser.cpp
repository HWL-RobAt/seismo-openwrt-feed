#include "SignalAnalyser.h"

namespace es_signal_analysing
{

SignalAnalyser::SignalAnalyser (
                                int sampleRate, 
                                float pShortWindow, 
                                int pSLRatio, 
                                float pDelay,
                                int pGamma,
                                float pCutOff, 
                                float sShortWindow, 
                                float sCutOff
                               ): 
		sampleRate(sampleRate), pCutOff(pCutOff), sCutOff(sCutOff), 
        sWindowLength(sShortWindow),
        pTriggered(false), sTriggered(false)
{
	dt = 1.0 / sampleRate;
	
	detector = new Detector(
		sampleRate,				// int sampleRate        
		pShortWindow,	// float shortWindow
		pSLRatio,		// int SLratio             
		pDelay,			// float delay         
		pGamma,			// int gamma
        sWindowLength   // float sWindowLength
	);
	
	energy = new Energy(dt);
	energyIntervall = sampleRate;
	energyCount = 0;
	
	eFilter = new BW4();
	nFilter = new BW4();
	zFilter = new BW4();
	
	P = new Pparams();
	S = new Sparams();
	
	fStaLtaPWave = 0.0;
	fStaLtaSWave = 0.0;
}

SignalAnalyser::~SignalAnalyser()
{
}

void
SignalAnalyser::processNextRecord(long long timeIndex, float xValue, float yValue, float zValue) 
{
    //std::cout << "xValue " << xValue << "yValue " << yValue << "zValue " << zValue << std::endl;
	/* no more multiplikation with 9.81 because sensor data is already in m/s*s
		float eFiltered = eFilter->filter(xValue * 9.81);    // the test data are in g - units
		float nFiltered = nFilter->filter(yValue * 9.81);    // IIR filtering the raw data 
		float zFiltered = zFilter->filter(zValue * 9.81);
	*/
	float eFiltered = eFilter->filter(xValue);    // the test data are in g - units
	float nFiltered = nFilter->filter(yValue);    // IIR filtering the raw data 
	float zFiltered = zFilter->filter(zValue);
    
    VD kE(dt), kN(dt), kZ(dt);  // Kanamori filter objects

    std::pair<float,float> vdE;
    std::pair<float,float> vdN;
    std::pair<float,float> vdZ;

    vdE = kE(eFiltered);
    vdN = kN(nFiltered);
    vdZ = kZ(zFiltered);
    
	P->updateAVD(timeIndex, zFiltered, vdZ.first, vdZ.second);  // watch for vertical peaks
    
	float SH2 = (eFiltered*eFiltered + nFiltered*nFiltered)/2; // a combination of horizontal components 
	                     // for energy collection AND S detection

	if (!pTriggered) {
        fStaLtaPWave = detector->Psignal(zFiltered, std::sqrt(SH2));  
        // P signal/noise ratio with current sample
        //std::cout << "fStaLtaPWave " << fStaLtaPWave << std::endl;
        if (fStaLtaPWave > pCutOff) { // trigger found
            pTriggered = true;
        }
	}


	if (pTriggered  && !sTriggered) {
        fStaLtaSWave = detector->Ssignal(std::sqrt(SH2));	// signal/noise ratio with current (horizontal) samples
		S->updateAVDeast    (timeIndex, eFiltered, vdE.first, vdE.second); // watch for S parameters
		S->updateAVDnorth   (timeIndex, nFiltered, vdN.first, vdN.second);
		S->updateAVDvertical(timeIndex, zFiltered, vdZ.first, vdZ.second);
		if (fStaLtaSWave > sCutOff) { // trigger found
			sTriggered = true;
		}
	}

	energy->sample(SH2);
	if (++energyCount > energyIntervall) { // cyclic reset at the callers site
		energyCount=1;
		energy->resetEnergy();
	}
		
	// there should be similar cyclic reports on wave parameters at he callers site
    // for now i have only a final report on them:

}

void
SignalAnalyser::reset() 
{
	//reset p/s trigger algorithm
	detector->reset();
	
	energy->reset();
	energy->resetEnergy();
	
	P->reset();
	S->reset();
	
	//reset the trigger
	pTriggered = false;
	sTriggered = false;
}

bool
SignalAnalyser::isPTriggered()
{
	return pTriggered;
}

bool
SignalAnalyser::isSTriggered()
{
	return sTriggered;
}

float
SignalAnalyser::getStaLtaValue()
{
	return (fStaLtaPWave);
}

}
