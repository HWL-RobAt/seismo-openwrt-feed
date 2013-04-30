TARGET := els
CFILES   := $(wildcard *.c)
CPPFILES := $(wildcard *.cpp)
HFILES   := $(wildcard *.h) $(wildcard *.hpp)

CFLAGS += -I ../ -I . -DNODETARGET -DBOOST -DDEBUG -g
LDFLAGS += -lpthread -lboost_regex-mt -lboost_serialization-mt -lboost_thread-mt -lboost_system-mt

all: boost

%.o: %.c $(HFILES)
	$(CC) $(CFLAGS) $< -c
%.o: %.cpp $(HFILES)
	$(CXX) $(CFLAGS) $< -c

boost: $(CFILES:%.c=%.o) $(CPPFILES:%.cpp=%.o)
	$(CXX) $(LDFLAGS) $^ -o $(TARGET) $(LDFLAGS)

clean:
	$(RM) $(RMFLAGS) $(TARGET) *.o
