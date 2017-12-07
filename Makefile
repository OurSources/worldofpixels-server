OBJS    = $(wildcard *.cpp)

ALLOBJS = $(OBJS)

COMPILER_FLAGS = -Wall -std=gnu++0x -O2

LIBS = -I ./ -I ./lib/sol2/ -I ./lib/uWebSockets/src/ -L ./lib/uWebSockets/ -luWS -lssl -lz -lcrypto

TARGET = out

all: uWS $(ALLOBJS)
	$(CXX) $(ALLOBJS) $(COMPILER_FLAGS) $(LIBS) -o $(TARGET)

g: uWS $(ALLOBJS)
	$(CXX) $(ALLOBJS) -Wall -std=gnu++0x -Og -g $(LIBS) -o $(TARGET)

uWS:
	$(MAKE) -C uWebSockets
