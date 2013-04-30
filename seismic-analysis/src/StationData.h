#ifndef __STATIONDATA_H__
#define __STATIONDATA_H__


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>

/**
 * provide streaming like data for one station from a file
 * 
 * <br>ALL member functions are inline to enable maximal substitution 
 * 
 */
class StationData {
	std::string dataFile, stationName;
	std::string stationCode;
	float Rate;
	std::string Date;
	std::string Time;

	std::ifstream file;
	char line[80];
	bool eof;
public:
	/**
	 * open the station dat file
	 * 
	 * @param fileName file containing the data fully qualified name relatively to the current directory
	 */
	StationData(const char* fileName): file(fileName), eof(false) {
		if (!file) {
			std::cerr<<"cannot open "<<fileName<<std::endl;
			eof=true;
		}
	
/* Header structure
Station_code    R00
Sampling_rate   200.0000
Start_date      29.09.2004
Start_time      15:42:03.755
Time:sec   Long. E, g    Lat. N, g    Vert., g
.... data ....
*/
		// skip header
		char code[20];
		char date[20];
		char time[20];
		file.getline(line, 80);
		std::sscanf(line, "Station_code %s", code);
		stationCode = code;
		file.getline(line, 80);
		std::sscanf(line, "Sampling_rate %f", &Rate);
		file.getline(line, 80);
		std::sscanf(line, "Start_date %s", date);
		Date = date;
		file.getline(line, 80);
		std::sscanf(line, "Start_time %s", time);
		Time = time;
		file.getline(line, 80); // skip
	}	
	/**
	 * simulate streaming data provision
	 * 
	 * @param t current time
	 * @param e current (raw) east/west acceleration
	 * @param n current (raw) north/south acceleration
	 * @param z current (raw) vertical acceleration
	 * 
	 */
	void getData(float& t, float& e, float& n, float& z) {
		if (file.eof()) { eof=true; return; }
		file.getline(line, 80);	
		std::sscanf(line, "%f %f %f %f", &t, &e, &n, &z);
	}

	/**
	 * station meta data from the file: 
	 * @return station code
	 */
	std::string code() { return stationCode; }
	/**
	 * station meta data from the file: 
	 * @return station sampling rate
	 */
	float       rate() { return Rate; }
	
	/**
	 * station meta data from the file: 
	 * @return start date of recording
	 */
	std::string date() { return Date; }
	
	/**
	 * station meta data from the file: 
	 * @return start time of recording
	 */
	std::string time() { return Time; }
	
	/**
	 * no more data from file
	 * 
	 * @return data source exhausted
	 */
	bool        end()  { return eof; }
};
#endif

