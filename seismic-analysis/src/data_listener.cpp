#include "data_listener.h"

DataListener::DataListener(std::string pipeName) {
	int ret_val;
	this->pipeName = pipeName;
	//creating named pipe
	std::cout << "DL: started. listening at " << pipeName << std::endl;
	ret_val = mkfifo(pipeName.c_str(), 0666);
	if ((ret_val == -1) && (errno != EEXIST)) {
		perror("Error creating the named pipe");
	}
	//open pipe
	fd = open(pipeName.c_str(), O_RDONLY);
	fs = fdopen(fd, "r");
	//open pipe as write process too
	fd_w = open(pipeName.c_str(), O_WRONLY);
	std::cout << "DL: initialized" << std::endl;
}

DataListener::~DataListener() {
	fclose(fs);
	close(fd);
	close(fd_w);
}

const RSDPSensorPacket& DataListener::getNextSP() {
	for (unsigned int i = 0; i < sizeof(RSDPSensorPacket); ++i)
		reinterpret_cast<char*>(&buf)[i] = fgetc(fs);
	
	return buf;
}
