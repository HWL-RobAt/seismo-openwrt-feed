#ifndef __ENERGY_H__
#define __ENERGY_H__
/**
 *   Energy measurement 
 *
 *   horizontal accelerations (aE, aN) are to be combined by
 *
 *        <tt>float SH2 = (aE*aE + aN*aN)/2;</tt>
 * 
 *   and passed to 
 *	
 *        <tt>e.sample(SH2);</tt>
 *
 *   of an Energy - object (initialized with the sample rate)
 *
 *        <tt>Energy e(dt);</tt>
 *
 * 
 *  <br>ALL member functions are inline to enable maximal substitution
 * 
 */

/** Energy measurement class
 * use a separate Energy - object for each independent data source
 */
class Energy {
	float lastSH2, SH2;
	float maxEnergy_;
	float energy_;
	const float dt;
public:
	/**
	 * constructs a new Energy measuring object
	 * 
	 * @param sampleInterval the sampling intervall in seconds
	 */
	Energy(float sampleInterval): 
		dt(sampleInterval)
		{ reset(); }
	/**
	 * reset the energy measurment to initial state: all
	 * values reset to zero
	 */
	void reset() {	
		lastSH2=0; 
		SH2=0; 
		energy_=0; 
		maxEnergy_=0; 
	}
	/**
	 * because the energy is monotonous increasing it has to be reset
	 * after aequidistant periods by the client
	 * 
	 * sample code:
	 * <pre>
	 *      Energy energ
	 *      energ.sample(SH2);
	 *      if (++eN > energyIntervall) {
	 *          eN=1;
	 *          lastPeriodEnergy = energ.energy()
	 *          energ.resetEnergy();
	 *      }
	 * </pre>
	 * reset the actual energy (only) to zero
	 * maximal energy and last value kept
	 */
	void resetEnergy() { energy_=0; }
	
	/**
	 * maximal Energy value since last reset
	 * 
	 * @return the collected energy amount
	 */
	float maxEnergy() { return maxEnergy_; }
	
	/**
	 * the current energy
	 * 
	 * @return the current collected energy amount
	 */
	float energy() { return energy_; }
	
	/**
	 * collect a new sample for energy contribution
	 * 
	 * the samples are to be constructed form horizontal components
	 * in form of<br><br>
	 * 				SH2 = (e*e + n*n)/2; // east and north components<br>
	 * 
	 * DO NOT call with sqrt((e*e + n * n)/2) as in the original matlab code 
	 * because that had to be squared again in the first place
	 * 
	 * NOTE: if SH values are needed somewhere else (e.g. S-Trigger detection)
	 *       they can be easily provided from SH2 values by
	 *       SH = std::sqrt(SH2);
	 *
	 */
	void sample (float SH2)  // only horiz. components
	{
		energy_+=(SH2+lastSH2)*dt/2;
		if (energy_>maxEnergy_) maxEnergy_=energy_;
		lastSH2 =SH2;
	}
};
#endif

