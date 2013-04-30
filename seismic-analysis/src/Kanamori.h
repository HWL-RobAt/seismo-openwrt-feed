#ifndef __KANAMORI_H__
#define __KANAMORI_H__

#include <utility>

#define q 0.99
#define q2 0.99
#define Q (1+q)/4
#define Q2 (1+q2)/4

/**
 * Kanamori filter class 
 * 
 * computes velocity and distance with a one-value history
 * 
 * use a separate Kanamori - object for each independent data source
 * 
 * <br>ALL member functions are inline to enable maximal substitution 
 */
class VD { // Velocity and Displacement a la Kanamori et. al. 1999
	const float dt;
	float lastAcc, lastVel, lastDis;
public:
	/**
	 * construct a Velocity/Distance filter object
	 * 
	 * @param sampleInterval sensor sample interval
	 */
	VD(float sampleInterval): 
		dt(sampleInterval),
		lastAcc(0),
		lastVel(0),
		lastDis(0)
	{}

	/**
	 * filter incoming acceleration to both velocity and distance output
	 * 
	 * use one a separate functional VD-object for each direction:
	 * 
	 * <pre>
	 *          VD kE(dt), kN(dt), kZ(dt);

                std::pair<float,float> vdE;
                std::pair<float,float> vdN;
                std::pair<float,float> vdZ;

                vdE = kE(e); // east/west acceleration e
                vdN = kN(n); // north/south acceleration n
                vdZ = kZ(z); // vertical acceleration z
                
                // vdE.first  - east/west velocity
                // vdE.second - east/west distance
                // vdN.first  - north/south velocity
                // vdN.second - north/south distance
                // vdZ.first  - vertical velocity
                // vdZ.second - vertical distance
	 * </pre>
	 * 
	 * @param acc current acceleration (typically already filtered by a Butterworth-Filter)
	 * 
	 * @return a std::pair with both velocity(first) and distance(second) of the actual maximum
	 */
	std::pair<float, float> operator() (float acc) {
		float vel = Q  * dt * (lastAcc + acc) + q  * lastVel;
		float dis = Q2 * dt * (lastVel + vel) + q2 * lastDis;
		lastAcc = acc;
		lastVel = vel;
		lastDis = dis;
		return std::pair<float, float>(vel, dis);
	}
};
#endif

