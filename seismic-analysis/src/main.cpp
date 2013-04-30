#include "SignalAnalyser.h"
#include "data_listener.h"
#include <iostream>
#define SAMPLERATE 400
#define PSHORTWINDOW 0.2
#define PSLRATIO 50
#define PDELAY 1.0
#define PGAMMA 6
#define PCUTOFF 5.0
#define SSHORTWINDOW 0.6
#define SCUTOFF 100.0

int main () {
	DataListener dl(PIPE_NAME);
	es_signal_analysing::SignalAnalyser signalAnalyser (
						SAMPLERATE,
						PSHORTWINDOW,
						PSLRATIO,
						PDELAY,
						PGAMMA,
						PCUTOFF,
						SSHORTWINDOW,
						SCUTOFF
						);

	while (true) {
		RSDPSensorPacket sp = dl.getNextSP();
		signalAnalyser.processNextRecord(sp.timestamp, sp.chan1, sp.chan2, sp.chan3);
		std::cout << sp.timestamp << ": stalta: " <<  signalAnalyser.getStaLtaValue() << std::endl;
		if (signalAnalyser.isPTriggered()) {
			std::cout << "TRIGGER" << std::endl;
		}
	}

	return 0;
}
