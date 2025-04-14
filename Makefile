CXX = g++
CXXFLAGS = -O2 -Wall -march=native
LDFLAGS = 
INCLUDES = -Iincludes

SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = runme

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)