#ifndef __BUTTERWORTH_H__
#define __BUTTERWORTH_H__

#include "Ring.h"

/**
 * 	An IIR passband filter with fixed parameters
 *      for 
 *	<pre>
 *      f low  = 0.075 Hz
 *      f high = 12 Hz
 *      f nyq  = 100 Hz (for sampling rate 200 Hz)
 *      Rp =  3 dB max. loss in passband
 *      Rs = 20 dB min. attenuation in stopband
 *
 *      +-----------------------------------------------------------+
 *      | ATTENTION                                                 |
 *      | ALL arithmetic in filter MUST BE DONE in double precision |
 *      | to avoid instability !!!                                  |
 *      +-----------------------------------------------------------+
 * 
 *  USAGE:
 *
 *  call 
 *
 *        float filtered = bw4.filter(sample)
 *
 *  on each raw acceleration 'sample' and use 'filtered' afterwards 
 *  with a unique BW4-object (e.g. bw4) for each individual data sequence
 * </pre>
 * 
 * <br>ALL member functions are inline to enable maximal substitution
 */

class BW4 {
	Ring<8, double> xv, yv;
	struct Coefficient { static double a[9], b[9]; };
	const double* const a;
	const double* const b;
public:
	BW4():a(Coefficient::a), b(Coefficient::b) {}

	/**
	 * put x into the filter pipeline
	 * 
	 * @param x the next input value to be filtered
	 * @return the new filter output
	 */
	double filter(float x) {
		
		double ma = 
                          a[1]*yv[1]
                         +a[2]*yv[2]
                         +a[3]*yv[3]
                         +a[4]*yv[4]
                         +a[5]*yv[5]
                         +a[6]*yv[6]
                         +a[7]*yv[7]
                         +a[8]*yv[8];

		double mb = b[0]* x
                         +b[2]*xv[2]
                         +b[4]*xv[4]
                         +b[6]*xv[6]
                         +b[8]*xv[8];
/* unrolled now to avoid zero terms
		for (int i=1; i < 9; ++i) {	
			mb += b[i]*xv[i];
			ma += a[i]*yv[i];
		}
*/
		double y = mb - ma;	
		xv.put(x); // feed the chain
		yv.put(y); // dito
		return y;
	}
};
#endif


