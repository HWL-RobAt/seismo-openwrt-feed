#ifndef DATA_LISTENER
#define DATA_LISTENER

/*
 * main.c
 *
 *  Created on: 03.10.2008
 *      Author: ingmar
 */
#include <stdio.h>
#include <iostream>
#include <errno.h>
#include <ctype.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string>

#define PIPE_NAME "/tmp/seismic_analysis_pipe"

struct RSDPSensorPacket {
	uint64_t timestamp; 	// timestamp in usecs

	float chan1;
	float chan2;
	float chan3;
	float chan4;
};

class DataListener {
private:
	int fd, fd_w;
	FILE* fs;
	RSDPSensorPacket buf;
	std::string pipeName;

public:
	DataListener(std::string pipeName);

	~DataListener();

	const RSDPSensorPacket& getNextSP();
};


#endif /*DATA_LISTENER*/
