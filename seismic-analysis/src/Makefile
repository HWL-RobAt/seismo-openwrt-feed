seismic-analysis : main.cpp Butterworth.cpp Butterworth.h Kanamori.h Detector.h Energy.h\
   StationData.h StationOutput.h EventParams.h SignalAnalyser.cpp SignalAnalyser.h
	$(CXX) $(CXXFLAGS) -c -O2 -Wall -o Butterworth.o Butterworth.cpp
	$(CXX) $(CXXFLAGS) -c -O2 -Wall -o SignalAnalyser.o SignalAnalyser.cpp
	$(CXX) $(CXXFLAGS) -c -O2 -Wall -o data_listener.o data_listener.cpp
	$(CXX) $(CXXFLAGS) -c -O2 -Wall -o main.o main.cpp
	$(CXX) $(LDFLAGS) -o $@ *.o
		
clean:
	rm -rf *.o
	rm -rf seismic-analysis
