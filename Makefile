CXX = g++
CXXFLAGS = -std=c++11 -Iinclude
LDFLAGS = -lssl -lcrypto

SRCS = src/main.cpp src/client.cpp src/server.cpp src/utils.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = guit

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
