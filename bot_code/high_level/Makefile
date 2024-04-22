# Compiler settings - Can be customized.
CXX = g++
CXXFLAGS = -Wall -g -std=c++11


# Target executable name
TARGET = test.cpp

# Files and directories - Exclude specific files
SRCS = $(filter-out Communication.cpp hashing.cpp main.cpp MoreCommunicationmodules.cpp sender.cpp statespacesearch.cpp AStar_alternate.cpp, $(wildcard *.cpp))
OBJS = $(SRCS:.cpp=.o)

# Build executable
$(TARGET): $(OBJS)
	$(CXX) -o $@ $^

# Build object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c "$<"

# Phony targets
.PHONY: clean all

all: $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
