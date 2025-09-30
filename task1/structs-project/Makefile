CXX := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -Wpedantic

TARGET := structs
SOURCES := main.cpp func.cpp
HEADERS := structs.h func.h

$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) main.cpp func.cpp -o $(TARGET)

clean:
	rm -f $(TARGET)
