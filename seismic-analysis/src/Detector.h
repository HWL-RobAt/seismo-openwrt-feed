#ifndef __DETECTOR_H__
#define __DETECTOR_H__


#include <cmath>
#include <deque>
#include <cfloat>
#include <cassert>

/**
 * rekursive STA/LTA algorithm for P wave detection AND
 * rekursive signal/noise algorithm for S wave detection
 * 
 * <br>ALL member functions are inline to enable maximal substitution 
 */
class Detector {
//sample rate    
    int sps;
    
// P detector parameters:
	const float asta, alta;
	const float g;
	const float g1;
    
// P detector cached data:
	std::deque<float> samplesS;
	std::deque<float> samplesL;
	std::deque<float> vstas;
    float vlta;

// P detector derived values:
	const int nsta;  // short window length
	const int nlta;  // long window length
	float sumsta, sumlta;
    
// P detector sample counting
	int Psample_;
    
// S detector parameters:  
    const int nstas; // sta window length

// S detector cached data:
    std::deque<float> Ssample; // last nstas horizontal averages

// S detector derived values:
    float Ssum;
    float vstax;
    float lastVstax;

// S detector sample counting
    int Ssample_;
    bool staWindowOK;
    bool firstScall;

public:
	/**
	 * construct a P/S wave detector object
	 * 
	 * @param sampleInterval the sensor sampling interval in seconds
	 * @param shortWindow number of samples in the short P-window
	 * @param SLratio short long P-ratio: longWindow=SLratio*shortWindow
	 * @param delay recursion delay in seconds: use influence of old P-values at now-delay
	 * @param gamma P-steering parameter
	 * 
	 * P wave detection uses history of longWindow past values (including the shortWindow)
	 * for calculation running means on long & short window
     * 
     * it also collects horizontal accelerations in a window of length nstas for 
     * S wave detection
     *
     * S wave detection uses VLTA (calculated during P wave detetion) to scale its signal/noise ratio
     * based on a (sWindowLength * sps) windowed average 
	 * 
	 * At the beginning all windows are zero initialized
	 */
	Detector(
		int sps, 
		float shortWindow,
		int SLratio,
		float delay,
		int gamma,
        float sWindowLength
		):
			sps(sps),
			asta(shortWindow),
			alta(shortWindow*SLratio),
			g(float(std::pow(2.0, -gamma))),
			g1(1-g),
			samplesS(int(shortWindow * sps)),
			samplesL(int((shortWindow*(SLratio-1) * sps))),
			vstas(int(delay * sps)),
			vlta(0.0f),
			nsta(int(shortWindow * sps)),
			nlta(int(shortWindow*SLratio * sps)),
			sumsta(0.0f), sumlta(0.0f),
                        Psample_(0),  
                        nstas(sWindowLength * sps), 
                        Ssample(sWindowLength * sps), 
                        Ssum(0.0f), vstax(0.0f), 
                        lastVstax(0.0f), Ssample_(0), 
            		staWindowOK(false),
                        firstScall(true)
	{ }
	
	/**
	 * reset all
         * no reuse possible   
	 */
	void reset(float = 0) { 
		sumsta = sumlta = Ssum = 0.0f; 
		vstax = lastVstax = 0.0f;
		Psample_ = Ssample_ = 0;
		samplesS.clear();
		samplesS.resize(int(asta*sps));
		samplesL.clear();
		float ratio = alta/asta;
		samplesL.resize(int((asta*(ratio-1)*sps)));
                Ssample.clear();
                Ssample.resize(nstas);
                staWindowOK = false;
                firstScall = true;
	}


	/**
	 * calculate the actual P signal/noise ratio
	 * 
	 * and put the current sample into the history window
	 * update the running means
	 * 
	 * @param sampleZ vertical acceleration
     * @param sampleNE horizontal acceleration vector length [sqtr(sampleN ^ 2 + sampleE ^ 2)]
	 * @return the actual P signal/noise ratio - caller has to compare to cutoff value!
	 */
	float Psignal(float sampleZ, float sampleNE)  {
		if (sampleZ < 0) sampleZ=-sampleZ; 

		samplesS.push_back(sampleZ);
		float vL = samplesL.front();
		samplesL.pop_front();
		sumlta+=sampleZ-vL;
		float vS = samplesS.front();
		samplesS.pop_front();
		samplesL.push_back(vS);
		sumsta+=sampleZ-vS;

                // horizontal samples:
                Ssample.push_back(sampleNE);
                float front = Ssample.front();
                Ssample.pop_front();
		Ssum+=sampleNE-front;

                if (!staWindowOK && ++Ssample_ > nstas) staWindowOK = true;     

		float vsta = sumsta/nsta;
		float vlta0 = sumlta/nlta;
		
		vstas.push_back(vsta);	
		float steering = vstas.front();	
		vstas.pop_front();	

		vlta = g * steering + g1 * vlta0;

		float snr = vsta/vlta;
        
		if (++Psample_ <= nlta) return 0.f; // not enough Z samples yet

	    if ((snr == snr) && (snr <= DBL_MAX && snr >= -DBL_MAX))
		  return snr;
		else {
		  //std::cout << "NaN error" << std::endl;
		  return 0.f;
		}
	}
        
	/**
	 * calculate the actual S signal/noise ratio
     * 
     * @param sampleNE horizontal acceleration vector length [sqtr(sampleN ^ 2 + sampleE ^ 2)]
	 * @return the actual S signal/noise ratio - caller has to compare to cutoff value!
	 */
	float Ssignal(float sampleNE)  {
        static float VLTA = 0.0f;
        if (firstScall) {
            firstScall = false;
            VLTA = vlta;
            assert(VLTA!= 0.0f);
            if(!staWindowOK) {
                std::cerr<<"small S window: "<< Ssample_ << "\n";
            }
            lastVstax = Ssum/nstas;	    
        }
        float delta = sampleNE - lastVstax;
        vstax = lastVstax + delta/nstas;
        lastVstax = vstax;
        return vstax/VLTA;
	}
};
#endif

