CXX := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -Wpedantic

TARGET := statsarr
SOURCES := main.cpp statsarr.cpp ../task2/dynarr-project/dynarr.cpp
HEADERS := statsarr.h

$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET) *.exe

