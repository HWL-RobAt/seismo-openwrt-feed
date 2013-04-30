#ifndef __RING_H__
#define __RING_H__
/**
 * 
 *	A cyclic (ring:-) buffer for storing 
 *  a history of 'N' values of type 'Type'  
 * 
 * 
 */
 #include <iostream>
 

template <int N, class Type = float>
class Ring {
	Type buf [N];
	int in;
public:
	/**
	 * constructs a new ringbuffer
	 * filled with a fulle history of 0 values
	 */
	Ring():in(0) {
	    for(int i=0; i<N; ++i)
	        buf[i]=0;
	}

	/**
	 * places value at the end of the buffer, thus overwriting 
	 * the oldest value in the history
	 * 
	 * \param value - to be added to the ring buffer
	 */	
	void put(Type value) {
		buf[in++]=value;
		in%=N;
	}
	
	/**
	 * returns an value from the history
	 * 
	 * \param idx into the ring buffer
	 * 
	 * 1 - the last saved value (the most previous)
	 * ...
	 * N - the oldest value in the history
	 */	
	Type operator[] (int idx) {
		int out = (in-idx+N)%N;
		return buf[out];
	}
	/**
	 * for debugging purposes:
	 * output the current state of the ring
	 */ 
	friend std::ostream& operator<<(std::ostream& o, Ring r) {
		o<<"ring[\t";
		for (int i=0; i<N; ++i)
			o<<r[i]<<'\t';
		o<<"]\n";
		return o;
	}

			
	
	
};
#endif

