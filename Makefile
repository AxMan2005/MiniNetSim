CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:.cpp=.o)

TARGET = netsim

all: $(TARGET)

$(TARGET): main.cpp $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ main.cpp $(SRCS)

clean:
	rm -f $(TARGET) src/*.o
