# Compiler
CXX = g++
CXXFLAGS = -std=c++11 -Wall -O2 -m64

# Files
TARGET = FunctionPlotter.exe
OBJS = main.o FunctionPlotter.o

# Build target
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp FunctionPlotter.h
	$(CXX) $(CXXFLAGS) -c main.cpp

FunctionPlotter.o: FunctionPlotter.cpp FunctionPlotter.h
	$(CXX) $(CXXFLAGS) -c FunctionPlotter.cpp

clean:
	del /Q *.o $(TARGET) output_2d.svg output_3d.obj 2>nul || echo.

run: $(TARGET)
	.\$(TARGET)

.PHONY: all clean run