# Set compiler and flags
CXX	= g++
CXXFLAGS= -std=c++23 -Wall -Wextra -pedantic -O2
LDFLAGS	=

# Project settings
TARGET	= demo
SRCS	= Test3.cpp MatMul.cpp common.cpp
OBJS	= $(SRCS:.cpp=.o)

# Build
.PHONY: all
all: $(TARGET)

# Build the executable
$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $@

# Build the object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean
.PHONY: clean
clean:
	rm -rf $(OBJS) $(TARGET)
