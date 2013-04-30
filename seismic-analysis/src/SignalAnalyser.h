#ifndef SIGNALANALYSER_H_
#define SIGNALANALYSER_H_

#include "Butterworth.h"
#include "Kanamori.h"
#include "Detector.h"
#include "Energy.h"
#include "StationData.h"
#include "StationOutput.h"
#include "EventParams.h"

#include <cmath>

namespace es_signal_analysing
{
    
    class SignalAnalyser
    {
    public:
        SignalAnalyser(
                       int sampleInterval, 
                       float pShortWindow,
                       int pSLRatio,
                       float pDelay,
                       int pGamma,
                       float pCutOff,
                       float sShortWindow,
                       float sCutOff
                       );
        
        virtual ~SignalAnalyser();
        
        /**
         * analyse te next SensorData object
         */
        void processNextRecord(long long timeIndex, float xValue, float yValue, float zValue);
        
        /**
         * reset the signal analyser for a fresh start
         */
        void reset();
        
        /**
         * returns true if pWave triggered
         */
        bool isPTriggered();
        
        /**
         * returns true if sWave triggered
         */
        bool isSTriggered();
        
        /**
         * returns STA/LTA TriggerValues
         */
        float getStaLtaValue();
        
        Pparams* P;
        Sparams* S;
        
        
    private:
        /**
         * samplerate
         */
        int sampleRate;
        
        /**
         * the threshold
         */
        float pCutOff;	
        float sCutOff;
        
        float sWindowLength;
        
        float dt;
        
        bool pTriggered;
        
        bool sTriggered;
        
        // trigger values
        float fStaLtaPWave;
        float fStaLtaSWave;
        
        // p/s Wave trigger algorithm
        Detector* detector;
        
        Energy* energy;
        int energyIntervall;
        int energyCount;
        
        //Butterworth filter
        BW4* nFilter;
        BW4* eFilter;
        BW4* zFilter;
        
        
    };
    
}

#endif /*SIGNALANALYSER_H_*/
