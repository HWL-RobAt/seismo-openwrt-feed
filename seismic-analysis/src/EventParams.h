#ifndef __EVENTPARAMS_H__
#define __EVENTPARAMS_H__

#include <utility>


#define Pi_2g 0.160121949724250 
// the constant pi/(2*g)

/**
 * P event parameter class
 * 
 * collect event parameters<br>
 * <br>
 * maximal values recorded so far:<br>
 * Pam, Pvm, Pdm of vertival data<br>
 * <br>
 * integral values of values recorded so far:<br>
 * CAVpz, CAVpn, CAVpe of all directions<br>
 * ARIpz, ARIpn, ARIpe of all directions<br>
 * 
 * <br>ALL member functions are inline to enable maximal substitution 
 */
  											
class Pparams {
	float Pam_, Pvm_, Pdm_;
	float tPam_, tPvm_, tPdm_;
	float CAVpz_, CAVpn_, CAVpe_;
	float aripz_, aripn_, aripe_;
public:
	/**
	 * construct a new parameter set: all values are zero
	 */
	Pparams(){ reset(); }
	
	/** reset a parameter set to initial state
	 */
	void reset() {
        	Pam_=Pvm_=Pdm_=0;
        	tPam_=tPvm_=tPdm_=0;
                CAVpz_=CAVpn_=CAVpe_=0;
                aripz_=aripn_=aripe_=0;
	}

	/**
	 * update maximal parameters with VERTICAL values at a time
	 * 
	 * @param time absolute time of this sample
	 * @param a the acceleration 
	 * @param v the velocity
	 * @param d the distance
	 */
	void updateAVD(float time, float a, float v, float d) {
		if (a<0) a=-a;
		if (v<0) v=-v;
		if (d<0) d=-d;

		if (a>Pam_) { Pam_=a; tPam_=time; } 
		if (v>Pvm_) { Pvm_=v; tPvm_=time; } 
		if (d>Pdm_) { Pdm_=d; tPdm_=time; } 
	}
	
	/**
	 * the peak acceleration value so far and the time where it occured
	 * 
	 * @return a std::pair with both time(first) and value(second) of the actual maximum
	 */
	std::pair<float, float> Pam() { return std::pair<float, float>(tPam_, Pam_); }
	
	/**
	 * the peak velocity value so far and the time where it occured
	 * 
	 * @return a std::pair with both time(first) and value(second) of the actual maximum
	 */
	std::pair<float, float> Pvm() { return std::pair<float, float>(tPvm_, Pvm_); }
	
	/**
	 * the peak distance value so far and the time where it occured
	 * 
	 * @return a std::pair with both time(first) and value(second) of the actual maximum
	 */
	std::pair<float, float> Pdm() { return std::pair<float, float>(tPdm_, Pdm_); }

	/**
	 * update integral parameters with values in all directions at a time
	 * 
	 * @param dt the sampling interval
	 * @param Z the vertical component
	 * @param N the north/south component
	 * @param E the east/west component
	 */	
	void updateZNE(float dt, float Z, float N, float E) {
		if (Z<0) Z=-Z;
		float Zdt=Z*dt;
		CAVpz_ += Zdt;

		if (N<0) N=-N;
		float Ndt=N*dt;
		CAVpn_ += Ndt;

		if (E<0) E=-E;
		float Edt=E*dt;
		CAVpe_ += Edt;

		aripz_ += Z*Zdt;
		aripn_ += N*Ndt;
		aripe_ += E*Edt;
	}

	/**
	 * Cumulative absolute vertical acceleration 
	 * 
	 * @return CAVpz
	 */
	float CAVpz() { return CAVpz_; }
	
	/**
	 * Cumulative absolute vertical acceleration north/south
	 * 
	 * @return CAVpn
	 */
	float CAVpn() { return CAVpn_; }
	
	/**
	 * Cumulative absolute vertical acceleration east/west
	 * 
	 * @return CAVpe
	 */
	float CAVpe() { return CAVpe_; }
	
	/**
	 * ARIAS (Cumulative squared vertical acceleration)
	 * 
	 * @return ARIpz
	 */
	float ARIpz() { return aripz_*Pi_2g; }
	
	/**
	 * ARIAS (Cumulative squared north/south acceleration)
	 * 
	 * @return ARIpn
	 */
	float ARIpn() { return aripn_*Pi_2g; }
	
	/**
	 * ARIAS (Cumulative squared east/west acceleration)
	 * 
	 * @return ARIpe
	 */
	float ARIpe() { return aripe_*Pi_2g; }
};

/**
 * S event parameter class
 * 
 * collect event parameters<br>
 * <br>
 * maximal values recorded so far:<br>
 * PGAm, PGVm, PGDm of vertival data<br>
 * PGAn, PGVn, PGDn of north/south data<br>
 * PGAe, PGVe, PGDe of east/west data<br>
 * <br>
 * integral values of values recorded so far:<br>
 * CAVsz, CAVsn, CAVse of all directions<br>
 * ARIsz, ARIsn, ARIse of all directions<br>
 * 
 * <br>ALL member functions are inline to enable maximal substitution
 */
class Sparams {
	float PGAm_, PGAn_, PGAe_;
	float PGVm_, PGVn_, PGVe_;
	float PGDm_, PGDn_, PGDe_;
	float tPGAm_, tPGAn_, tPGAe_;
	float tPGVm_, tPGVn_, tPGVe_;
	float tPGDm_, tPGDn_, tPGDe_;
	float CAVsz_, CAVsn_, CAVse_;
	float arisz_, arisn_, arise_;
public:
	/**
	 * construct a new parameter set: all values are zero
	 */
	Sparams(){ reset(); }
	/** reset a parameter set to initial state
	 */
	void reset() {
		PGAm_=PGAn_=PGAe_=0;
        	PGVm_=PGVn_=PGVe_=0;
        	PGDm_=PGDn_=PGDe_=0;
        	tPGAm_=tPGAn_=tPGAe_=0;
        	tPGVm_=tPGVn_=tPGVe_=0;
       		tPGDm_=tPGDn_=tPGDe_=0;
       		CAVsz_=CAVsn_=CAVse_=0;
        	arisz_=arisn_=arise_=0;
	}

	/**
	 * update maximal parameters with VERTICAL values at a time
	 * 
	 * @param time absolute time of this sample
	 * @param a the acceleration 
	 * @param v the velocity
	 * @param d the distance
	 */
	void updateAVDvertical(float time, float a, float v, float d) {
		if (a<0) a=-a;
		if (v<0) v=-v;
		if (d<0) d=-d;

		if (a>PGAm_) { PGAm_=a; tPGAm_=time; } 
		if (v>PGVm_) { PGVm_=v; tPGVm_=time; } 
		if (d>PGDm_) { PGDm_=d; tPGDm_=time; } 
	}

	/**
	 * update maximal parameters with north/south values at a time
	 * 
	 * @param time absolute time of this sample
	 * @param a the acceleration 
	 * @param v the velocity
	 * @param d the distance
	 */
    void updateAVDnorth(float time, float a, float v, float d) {
                if (a<0) a=-a;
                if (v<0) v=-v;
                if (d<0) d=-d;

                if (a>PGAn_) { PGAn_=a; tPGAn_=time; }
                if (v>PGVn_) { PGVn_=v; tPGVn_=time; }
                if (d>PGDn_) { PGDn_=d; tPGDn_=time; }
        }
	/**
	 * update maximal parameters with east/west values at a time
	 * 
	 * @param time absolute time of this sample
	 * @param a the acceleration 
	 * @param v the velocity
	 * @param d the distance
	 */
    void updateAVDeast(float time, float a, float v, float d) {
                if (a<0) a=-a;
                if (v<0) v=-v;
                if (d<0) d=-d;

                if (a>PGAe_) { PGAe_=a; tPGAe_=time; }
                if (v>PGVe_) { PGVe_=v; tPGVe_=time; }
                if (d>PGDe_) { PGDe_=d; tPGDe_=time; }
        }
	/**
	 * the peak ground acceleration value (vertically) so far and the time where it occured
	 * 
	 * @return a std::pair with both time(first) and value(second) of the actual maximum
	 */
	std::pair<float, float> PGAm() { return std::pair<float, float>(tPGAm_, PGAm_); }
	
	/**
	 * the peak ground velocity value (vertically) so far and the time where it occured
	 * 
	 * @return a std::pair with both time(first) and value(second) of the actual maximum
	 */
	std::pair<float, float> PGVm() { return std::pair<float, float>(tPGVm_, PGVm_); }
	
	/**
	 * the peak ground distance value (vertically) so far and the time where it occured
	 * 
	 * @return a std::pair with both time(first) and value(second) of the actual maximum
	 */
	std::pair<float, float> PGDm() { return std::pair<float, float>(tPGDm_, PGDm_); }

	/**
	 * the peak ground acceleration value (north/south) so far and the time where it occured
	 * 
	 * @return a std::pair with both time(first) and value(second) of the actual maximum
	 */
	std::pair<float, float> PGAn() { return std::pair<float, float>(tPGAn_, PGAn_); }

	/**
	 * the peak ground velocity value (north/south) so far and the time where it occured
	 * 
	 * @return a std::pair with both time(first) and value(second) of the actual maximum
	 */
    std::pair<float, float> PGVn() { return std::pair<float, float>(tPGVn_, PGVn_); }
	
	/**
	 * the peak ground distance value (north/south) so far and the time where it occured
	 * 
	 * @return a std::pair with both time(first) and value(second) of the actual maximum
	 */
    std::pair<float, float> PGDn() { return std::pair<float, float>(tPGDn_, PGDn_); }

    /**
     *  the peak ground acceleration value (east/west) so far and the time where it occured
     * 
     * @return a std::pair with both time(first) and value(second) of the actual maximum
     */
    std::pair<float, float> PGAe() { return std::pair<float, float>(tPGAe_, PGAe_); }
   
	/**
	 * the peak ground velocity value (east/west) so far and the time where it occured
	 * 
	 * @return a std::pair with both time(first) and value(second) of the actual maximum
	 */
    std::pair<float, float> PGVe() { return std::pair<float, float>(tPGVe_, PGVe_); }
    
	
	/**
	 * the peak ground distance value (east/west) so far and the time where it occured
	 * 
	 * @return a std::pair with both time(first) and value(second) of the actual maximum
	 */
    std::pair<float, float> PGDe() { return std::pair<float, float>(tPGDe_, PGDe_); }

	/**
	 * update integral parameters with values in all directions at a time
	 * 
	 * @param dt the sampling interval
	 * @param Z the vertical component
	 * @param N the north/south component
	 * @param E the east/west component
	 */	
	void updateZNE(float dt, float Z, float N, float E) {
		if (Z<0) Z=-Z;
		float Zdt=Z*dt;
		CAVsz_ += Zdt;

		if (N<0) N=-N;
		float Ndt=N*dt;
		CAVsn_ += Ndt;

		if (E<0) E=-E;
		float Edt=E*dt;
		CAVse_ += Edt;

		arisz_ += Z*Zdt;
		arisn_ += N*Ndt;
		arise_ += E*Edt;
	}

	/**
	 * Cumulative absolute vertical acceleration 
	 * 
	 * @return CAVsz
	 */
	float CAVsz() { return CAVsz_; }

	/**
	 * Cumulative absolute north/south acceleration 
	 * 
	 * @return CAVsn
	 */
	float CAVsn() { return CAVsn_; }
	
	/**
	 * Cumulative absolute east/west acceleration 
	 * 
	 * @return CAVse
	 */
	float CAVse() { return CAVse_; }

	/**
	 * ARIAS (Cumulative squared vertical acceleration)
	 * 
	 * @return ARIsz
	 */
	float ARIsz() { return arisz_*Pi_2g; }
	
	/**
	 * ARIAS (Cumulative squared north/south acceleration)
	 * 
	 * @return ARIsn
	 */
	float ARIsn() { return arisn_*Pi_2g; }
	
	/**
	 * ARIAS (Cumulative squared east/west acceleration)
	 * 
	 * @return ARIse
	 */
	float ARIse() { return arise_*Pi_2g; }
};
#endif

