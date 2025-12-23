CXX := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -Wpedantic

TARGET := template_array
SOURCES := main.cpp
HEADERS := array.h

$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET) *.exe

