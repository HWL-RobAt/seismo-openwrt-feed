#ifndef __STATIONOUTPUT_H__
#define __STATIONOUTPUT_H__

#include <fstream>
#include <string>

/**
 * Analysis output per station in separate directories
 * 
 * <br>ALL member functions are inline to enable maximal substitution 
 * 
 */
class StationOutput {
	std::string name_;
        std::ofstream aE_;
        std::ofstream aN_;
        std::ofstream aZ_;
        std::ofstream vE_;
        std::ofstream vN_;
        std::ofstream vZ_;
        std::ofstream dE_;
        std::ofstream dN_;
        std::ofstream dZ_;
        std::ofstream En_;
        std::ofstream PSNR_;
        std::ofstream SSNR_;
public:
	/**
	 * open files for data output relatively to
	 * 
	 * @param outDir root directory for all output for one station
	 */
	StationOutput(std::string outDir): name_(outDir),
		aE_((outDir+"/aE").c_str()), // acceleration east/west 
		aN_((outDir+"/aN").c_str()), // acceleration north/south
		aZ_((outDir+"/aZ").c_str()), // acceleration vertically
		vE_((outDir+"/vE").c_str()), // velocity east/west
		vN_((outDir+"/vN").c_str()), // velocity north/south
		vZ_((outDir+"/vZ").c_str()), // velocity vertically
		dE_((outDir+"/dE").c_str()), // distance east/west 
		dN_((outDir+"/dN").c_str()), // distance north/south
		dZ_((outDir+"/dZ").c_str()), // distance vertically
		En_((outDir+"/Energy").c_str()), // Energy
		PSNR_((outDir+"/PSNR").c_str()), // P signal/nois ratio
		SSNR_((outDir+"/SSNR").c_str())  // S signal/nois ratio
	{}
	/** 
	 * short file handle for the client
	 */
	std::ofstream& aE() { return aE_; }
	
	/** 
	 * short file handle for the client
	 */
	std::ofstream& aN() { return aN_; }
	
	/** 
	 * short file handle for the client
	 */
	std::ofstream& aZ() { return aZ_; }
	
	/** 
	 * short file handle for the client
	 */
	std::ofstream& vE() { return vE_; }
	
	/** 
	 * short file handle for the client
	 */
	std::ofstream& vN() { return vN_; }
	
	/** 
	 * short file handle for the client
	 */
	std::ofstream& vZ() { return vZ_; }
	
	/** 
	 * short file handle for the client
	 */
	std::ofstream& dE() { return dE_; }

	/** 
	 * short file handle for the client
	 */
    std::ofstream& dN() { return dN_; }
    
	/** 
	 * short file handle for the client
	 */
    
    std::ofstream& dZ() { return dZ_; }
	/** 
	 * short file handle for the client
	 */
    
    std::ofstream& En() { return En_; }
	/** 
	 * short file handle for the client
	 */
    std::ofstream& PSNR() { return PSNR_; }
    
	/** 
	 * short file handle for the client
	 */
    std::ofstream& SSNR() { return SSNR_; }

    /**
     * directory name for the ouput root
     */
	std::string name() {return name_;}

};
#endif

